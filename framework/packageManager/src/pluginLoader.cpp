#include "pluginLoader.hpp"
#include "plugin.hpp"

#include <filesystem>

namespace plugio::framework::core {

PluginLoader::PluginLoader() :
    pluginLibIdCounter_(0)
{ }

PluginLoader::~PluginLoader() 
{
}

PluginLoader::PluginLibId PluginLoader::addPluginLib(const std::string & path)
{
    if (!std::filesystem::exists(path))
    {
        std::cout << "ERROR: library not found in " << path << std::endl;
        return 0;
    }

    LibDescriptor libDescriptor;
    // load library
    libDescriptor.handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!libDescriptor.handle)
    {
        std::cout << "Cannot load library: " << dlerror() << std::endl;
        return 0;
    }

    // load constructor and destructor symbols
    loadSymbol("create",  libDescriptor.handle, libDescriptor.pluginApi.constructor);
    loadSymbol("destroy", libDescriptor.handle, libDescriptor.pluginApi.destructor);

    // notify signal changes
    loadSymbol("onInChange", libDescriptor.handle, libDescriptor.pluginApi.specApi.onInChange);

    pluginLibIdCounter_++;
    libDescriptorsMap_.insert(std::make_pair(pluginLibIdCounter_, libDescriptor));
    std::cout << "INFO: library successfully added, id: " << pluginLibIdCounter_ << std::endl;
    
    return pluginLibIdCounter_;
}

bool PluginLoader::removePluginLib(PluginLibId id)
{
    auto libDescriptorIt = libDescriptorsMap_.find(id);
    if (libDescriptorIt == libDescriptorsMap_.end())
    {
        std::cout << "ERROR: couldn't find library with id " << id << std::endl;
        return false;
    }

    if (isPluginLibInUse(id))
    {
        std::cout << "ERROR: library with id " << id << " is still in use" << std::endl;
        return false;
    }

    dlclose(libDescriptorIt->second.handle);
    libDescriptorsMap_.erase(libDescriptorIt);
    std::cout << "INFO: lib successfully removed" << std::endl;
    
    return true;
}

std::shared_ptr<PluginProxy> PluginLoader::createInstance(PluginLibId id)
{
    auto libDescriptorIt = libDescriptorsMap_.find(id);
    if (libDescriptorIt == libDescriptorsMap_.end())
    {
        std::cout << "ERROR: couldn't create instance, wrong library id " << id << std::endl;
        return nullptr;
    }

    auto pluginProxy = std::make_shared<PluginProxy>(libDescriptorIt->second.pluginApi);
    libDescriptorIt->second.instances.push_back(pluginProxy);
    return pluginProxy;
}

bool PluginLoader::isPluginLibInUse(PluginLoader::PluginLibId id)
{
    auto libDescriptorIt = libDescriptorsMap_.find(id);
    if (libDescriptorIt == libDescriptorsMap_.end())
    {
        return false;
    }

    auto instanceIt = libDescriptorIt->second.instances.begin();
    while (instanceIt != libDescriptorIt->second.instances.end())
    {
        if(!instanceIt->lock())
        {
             instanceIt= libDescriptorIt->second.instances.erase(instanceIt);
        }
        else
        {
            return true;
        }
    }
    return false;
}

}
