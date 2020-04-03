#ifndef PACKAGEMANIFEST_HPP
#define PACKAGEMANIFEST_HPP

#include <string>

namespace plugio::framework::utils {

class PackageManifest
{
public:
    PackageManifest(const std::string & path);
    virtual ~PackageManifest() {}

    bool parse();

    const std::string & getPackageId() const;
    const std::string & getAppId() const;
    const std::string & getAppName() const;
    uint32_t getLibVersionMajor() const;
    uint32_t getLibVersionMinor() const;

private:
    const std::string path_;
    std::string packageId_;
    std::string appId_;
    std::string appName_;
    uint32_t libVersionMajor_;
    uint32_t libVersionMinor_;
};

}

#endif // MANIFESTFILE_HPP
