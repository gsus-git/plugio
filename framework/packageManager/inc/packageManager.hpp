#ifndef PACKAGEMANAGER_HPP
#define PACKAGEMANAGER_HPP

#include "packageManager.hpp"
#include "pluginLoader.hpp"

#include <map>
#include <memory>
#include <mutex>
#include <filesystem>

namespace plugio::framework::core {

class PackageInfo
{
public:
    /**
     * Identifier of the package. This id is universal and does not vary even if 
     * the system is rebooted.
     */
    using PackageId = std::string;

    PackageId packageId;
    std::string appName;
    std::string appId;
    std::string libPath;
    std::string iconPath;
    std::string name;
    size_t sizeMb;
    uint32_t libVersionMajor;
    uint32_t libVersionMinor;
};

class PackageManager
{
public:
    /**
     * Constructor
     */
    PackageManager(PluginLoader * pluginLoader);

    virtual ~PackageManager();

    /**
     * Load up all the packages already installed if they have not been previously
     * loaded. It is advised to always call this method after instantiating the class.
     */
    void initialize();

    /**
     * Install device and component's packages. The package is expected to be in a 
     * .tar.gz archive.
     *
     * @param path with the location of the package to be installed.
     * @return the package info or nullptr if there was any issues installing it.
     */
    PackageInfo::PackageId installPackage(const std::string & path);

    /**
     * Uninstall a package. In oder to delete a package no instances of the plugin can
     * be running.
     *
     * @param id of the package.
     * @return true if the package was uninstalled successfully.
     */
    bool uninstallPackage(PackageInfo::PackageId id);

    /**
     * Get the info of the packages installed
     *
     * @return a collection with the info about the packages installed
     */
    std::map<PackageInfo::PackageId, std::pair<PluginLoader::PluginLibId, PackageInfo>> getPackages() const;

private:
    PackageManager() = delete;

    const static std::string PACKAGE_LOCATION_PATH;
    const static std::string MANIFEST_FILE_NAME;

    std::mutex mutex_;
    PluginLoader * pluginLoader_;
    std::map<PackageInfo::PackageId, std::pair<PluginLoader::PluginLibId, PackageInfo>> packagesMap_;

    bool getPackageInfo(const std::string & packagePath, PackageInfo & packageInfo);
    bool hasTarGzExtension(const std::filesystem::path & pathFs);
    std::string getPackageName(const std::filesystem::path & pathFs);
    bool isPackageInstalled(const PackageInfo::PackageId & packageId);
};

}

#endif // PACKAGEMANAGER_HPP
