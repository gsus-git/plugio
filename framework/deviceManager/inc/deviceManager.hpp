#ifndef DEVICEMANAGER_HPP
#define DEVICEMANAGER_HPP

#include <memory>

namespace plugio::framework::core {

class Device
{
public:
    std::string instanceName;
    std::time_t creationTime;
    PackageManager::PackageId packageId;
};

class DeviceManager
{
public:
    DeviceManager(PluginLoader * pluginLoader);
    virtual ~DeviceManager() {} 

    /**
     * Create a new device
     *
     * @param pluginId to indicate the type of plugin. The plugin must have
     *        been previously installed.
     * @param instanceId is the identification for this device. It must be unique
     *        among other plugins. If not provided then the system will automatically
     *        assign one.
     */
    std::shared_ptr<Device> createDevice(PluginLoader::PluginId pluginId, PluginLoader::InstanceId & instanceId = 0);
  
    /**
     * Get a device by its instanceId
     *
     * @param instanceId is the id of the device.
     */ 
    std::shared_ptr<Device> getDevice(PluginLoader::InstanceId instanceId) const;

    /**
     * Remove a device by its id.
     *
     * @param instanceId of the device
     */
    bool removeDevice(DeviceId instanceId);
private:
    std::map<InstanceId, std::shared_ptr<Device>> devicesMap_;
};

}

#endif // DEVICEMANAGER_HPP
