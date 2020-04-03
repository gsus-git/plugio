#include "packageManager.hpp"
#include "packageManifest.hpp"

#include <iostream>
#include <filesystem>

namespace plugio::framework::core {

const std::string PackageManager::PACKAGE_LOCATION_PATH = "/home/pi/packages";
const std::string PackageManager::MANIFEST_FILE_NAME = "manifest.xml";

PackageManager::PackageManager(PluginLoader * pluginLoader) : 
    pluginLoader_(pluginLoader)
{ }

PackageManager::~PackageManager()
{ }

void PackageManager::initialize()
{
    const std::filesystem::path packageLocationPathFs = PACKAGE_LOCATION_PATH;
    if (!std::filesystem::exists(packageLocationPathFs))
    {
        std::cout << "ERROR: package folder does not exist, creating it..." << std::endl;
        if (!std::filesystem::create_directories(packageLocationPathFs))
        {
            std::cout << "ERROR: failed to create packages folder in location " <<  packageLocationPathFs.string() << std::endl;
        }
    }

    std::cout << "INFO: loading up intalled packages..." << std::endl; 
    for (const auto & folder : std::filesystem::directory_iterator(packageLocationPathFs))
    {
        std::cout << "INFO: loading package " << folder << std::endl;
        PackageInfo packageInfo;
        if (!getPackageInfo(folder.path().string(), packageInfo))
        {
            std::cout << "ERROR: initialize plugin " << folder << " failed" << std::endl;
            continue;
        }

        std::cout << "VERBOSE: loading package " << packageInfo.packageId << std::endl;

        // make plugin available in the plugin manager
        auto pluginId = pluginLoader_->addPluginLib(packageInfo.libPath);
        if (!pluginId)
        {
            std::cout << "ERROR: adding plugin library" << std::endl;
            continue;
        }

        packagesMap_.insert(std::make_pair(packageInfo.packageId, std::make_pair(pluginId, packageInfo)));
        std::cout << "INFO: package " << packageInfo.name << " successfully loaded" << std::endl;
    }
    std::cout << "INFO: done loading plugins" << std::endl;
}

PackageInfo::PackageId PackageManager::installPackage(const std::string & path)
{
    std::scoped_lock(mutex_);

    // check the package exists
    const std::filesystem::path pathFs = path;
    if (!std::filesystem::exists(pathFs))
    {
        std::cout << "ERROR: package does not exist in location " << path << std::endl;
        return "";
    }

    std::cout << "VERBOSE: installing package in " << pathFs << std::endl;
    
    if (!hasTarGzExtension(pathFs))
    {
        std::cout << "ERROR: wrong package extension" << std::endl;
        return "";
    }

    // cleanup before start
    std::filesystem::path tempFolderPathFs = std::filesystem::temp_directory_path() / "temp_package_container";
    if (std::filesystem::exists(tempFolderPathFs))
    {
        std::cout << "INFO: removing temp folder before installing new package" << std::endl;
        std::filesystem::remove_all(tempFolderPathFs);
    }
    if (!std::filesystem::create_directory(tempFolderPathFs))
    {
        std::cout << "ERROR: failed to create temp installation folder, aborting installation" << std::endl;
        return "";
    }

    // check if it's already installed
    const std::string packageFileName = getPackageName(pathFs);
    if (isPackageInstalled(packageFileName))
    {
        std::cout << "ERROR: package " << packageFileName << " already installed, aborting installation" << std::endl;
        std::filesystem::remove_all(tempFolderPathFs);
        return "";
    }

    // untar archive
    std::cout << "VERBOSE: extracting folder " << pathFs << " in " << tempFolderPathFs << std::endl;
    const std::string commandExtract = "tar -C " + tempFolderPathFs.string() + " -zxvf " + path;
    if (system(commandExtract.c_str()))
    {
        std::cout << "ERROR: cannot untar package, aborting installation" << std::endl;
        return "";
    }
    
    const std::filesystem::path tempPluginFolderPathFs = tempFolderPathFs / packageFileName;
    if (!std::filesystem::directory_entry(tempPluginFolderPathFs).is_directory())
    {
        std::cout << "ERROR: archive does not contain a directory named " << packageFileName << std::endl;
        return "";
    }

    // get plugin manifest
    PackageInfo packageInfo;
    if (!getPackageInfo(tempPluginFolderPathFs.string(), packageInfo))
    {
        std::cout << "ERROR: could not get package info: " << packageFileName << std::endl;
        std::filesystem::remove_all(tempFolderPathFs);
        return "";
    }

    // create the plugin folder
    const std::filesystem::path pluginPackageFolderPathFs = PACKAGE_LOCATION_PATH + "/" + packageInfo.packageId;
    if (!std::filesystem::create_directory(pluginPackageFolderPathFs))
    {
        std::cout << "ERROR: failed to create plugin folder, aborting installation" << std::endl;
        std::filesystem::remove_all(tempFolderPathFs);
        return "";
    }

    // copy files from container to plugin folder
    std::filesystem::copy(tempPluginFolderPathFs, pluginPackageFolderPathFs, std::filesystem::copy_options::recursive);
    // remover temp folder
    std::filesystem::remove_all(tempFolderPathFs);

    // make plugin available in the plugin manager
    auto pluginId = pluginLoader_->addPluginLib(packageInfo.libPath);
    if (!pluginId)
    {
        std::cout << "ERROR: could not add plugin library" << std::endl;
        std::filesystem::remove_all(pluginPackageFolderPathFs);
        return "";
    }
    packagesMap_.insert(std::make_pair(packageInfo.packageId, std::make_pair(pluginId, packageInfo)));
    std::cout << "INFO: package " << packageInfo.name << " successfully installed" << std::endl;

    return packageInfo.packageId;
}

bool PackageManager::getPackageInfo(const std::string & packagePath, PackageInfo & packageInfo)
{
    // get plugin manifest
    const std::string manifestPath = packagePath + "/" + MANIFEST_FILE_NAME;
    utils::PackageManifest packageManifest(manifestPath);
    if (!packageManifest.parse())
    {
        std::cout << "ERROR: couldn't parse manifest.xml" << std::endl;
        return false;
    }

    packageInfo.packageId = packageManifest.getPackageId();
    std::filesystem::path libPath = PACKAGE_LOCATION_PATH + "/" + packageManifest.getPackageId() + "/" +  packageManifest.getAppId() + ".so." + std::to_string(packageManifest.getLibVersionMajor());
    packageInfo.libPath = libPath.string();
    return true;
}

bool PackageManager::uninstallPackage(PackageInfo::PackageId id)
{
    return true;
}

bool PackageManager::hasTarGzExtension(const std::filesystem::path & pathFs)
{
    for (std::filesystem::path p = pathFs; !p.extension().empty(); p = p.stem())
    {
        if (p.extension() != ".gz" && p.extension() != ".tar")
        {
            return false;
        }
    }

    return true;
}

std::string PackageManager::getPackageName(const std::filesystem::path & pathFs)
{
    std::filesystem::path p = pathFs;
    for (; !p.extension().empty(); p = p.stem());
    return p.stem();
}

bool PackageManager::isPackageInstalled(const PackageInfo::PackageId & packageId)
{
    return packagesMap_.find(packageId) != packagesMap_.end();
}

}
