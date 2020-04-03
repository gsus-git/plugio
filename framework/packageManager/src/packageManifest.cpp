#include "packageManifest.hpp"

#include "pugixml.hpp"

#include <iostream>

namespace plugio::framework::utils {

PackageManifest::PackageManifest(const std::string & path) :
    path_(path)
{ }

bool PackageManifest::parse()
{
    pugi::xml_document doc;
    std::cout << "VERBOSE: loading manifest file " << path_ << std::endl;
    pugi::xml_parse_result result = doc.load_file(path_.c_str());
    if (!result)
    {
        std::cout << "ERROR: could not load file to parse: " << result.description() << std::endl;
        return false;
    }

    auto manifestNode = doc.child("manifest");
    packageId_ = manifestNode.attribute("packageId").value();

    appId_ = doc.child("manifest").child_value("appId");
    appName_ = doc.child("manifest").child_value("appName");

    libVersionMajor_ = static_cast<uint32_t>(std::stoul(doc.child("manifest").child("libVersion").child_value("major")));
    libVersionMinor_ = static_cast<uint32_t>(std::stoul(doc.child("manifest").child("libVersion").child_value("minor")));

    return true;
}

const std::string & PackageManifest::getPackageId() const 
{
    return packageId_;
}

const std::string & PackageManifest::getAppId() const
{
    return appId_;
}

const std::string & PackageManifest::getAppName() const
{
    return appName_;
}

uint32_t PackageManifest::getLibVersionMajor() const
{
    return libVersionMajor_;
}

uint32_t PackageManifest::getLibVersionMinor() const
{
    return libVersionMinor_;
}

}
