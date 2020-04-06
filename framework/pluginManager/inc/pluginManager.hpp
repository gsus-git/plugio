#ifndef PLUGINMANAGER_HPP
#define PLUGINMANAGER_HPP

#include <memory>

namespace plugio::framework::core {

class PluginManager
{
public:
    PluginManager(PluginLoader * pluginLoader);
    virtual ~PluginManager() {} 

    /**
     * Create a new instance of a plugin
     *
     * @param pluginId to indicate the type of plugin. The plugin must have
     *        been previously installed.
     * @param instanceId is the identification for this plugin. It must be unique
     *        among other plugins. If not provided then the system will automatically
     *        assign one.
     */
    bool createPlugin(PluginLoader::PluginId pluginId, PluginLoader::InstanceId & instanceId = 0);
  
    /**
     * Remove a plugin given its id.
     *
     * @param instanceId of the plugin
     */
    bool removePlugin(PluginLoader::InstanceId instanceId);

private:
    std::map<InstanceId, std::unique_ptr<PluginProxy>> pluginsMap_;
};

}

#endif // PLUGINMANAGER_HPP
