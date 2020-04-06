#ifndef PLUGINLIBLOADER_HPP
#define PLUGINLIBLOADER_HPP

#include "pluginProxy.hpp"
#include "plugin.hpp"

#include <string>
#include <map>
#include <utility>
#include <memory>
#include <iostream>
#include <dlfcn.h>

namespace plugio::framework::core {

class PluginLibLoader
{
public:
    using PluginLibId = size_t;
    
    PluginLibLoader();
    virtual ~PluginLibLoader();

    /**
     * Add a type of plugin into the system. Once the plugin has been added, this type 
     * of plugin can be instantiated by calling \p createPlugin.
     *
     * @param path to the library file.
     * @return the plugin id or 0 if there was an error adding the library. This id uniquely 
     *         identifies a plugin library. It is not persistant and might change 
     *         during power cycles.
     */
    PluginLibId addPluginLib(const std::string & path);

    /**
     * By removing a library, it will be no longer available to create plugins of that
     * type. In order to remove it, all the instances of this type must have been
     * destroyed.
     *
     * @param type of the plugin to be removed
     */
    bool removePluginLib(PluginLibId id);

    /**
     * Create an instance of a specific type of plugin.
     *
     * @param id indicates the type of plugin
     * @return a pointer to the instance of this plugin
     */
    std::shared_ptr<PluginProxy> createInstance(PluginLibId id);

private:
    class LibDescriptor
    {
    public:
        void * handle;
        PluginApi pluginApi;
        std::vector<std::weak_ptr<PluginProxy>> instances;
    };

    template<typename T>
    bool loadSymbol(const std::string & name, void * handle, T * symbol)
    {
        // reset erros
        dlerror();
        symbol = (T*) dlsym(handle, name.c_str());
        const char* dlsym_error = dlerror();
        if (dlsym_error)
        {   
            std::cout << "ERROR: cannot load symbol \"" << symbol << "\": " << dlsym_error << std::endl;
            return false;
        }
        return true;
    }

    PluginLibId pluginLibIdCounter_;
    std::map<PluginLibId, LibDescriptor> libDescriptorsMap_;

    bool isPluginLibInUse(PluginLibId id);
};

}

#endif // PLUGINLIBLOADER_HPP
