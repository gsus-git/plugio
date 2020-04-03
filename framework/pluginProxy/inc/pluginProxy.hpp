#ifndef PLUGINPROXY_HPP
#define PLUGINPROXY_HPP

#include "plugin.hpp"

#include <string>
#include <vector>

namespace plugio::framework::core {

class PluginApi
{
public:
    PluginApi();
    plugin::createPluginFn * constructor;
    plugin::destroyPluginFn * destructor;
    
    // signals
    plugin::setReadInSignalBFn * setReadInSignalB;
    plugin::setReadInSignalNFn * setReadInSignalN;
    plugin::setReadInSignalSFn * setReadInSignalS;
    plugin::setWriteOutSignalBFn * setWriteOutSignalB;
    plugin::setWriteOutSignalNFn * setWriteOutSignalN;
    plugin::setWriteOutSignalSFn * setWriteOutSignalS;
};

class PluginProxy
{
public:
    using InstanceId = size_t;

    PluginProxy(const PluginApi & pluginApi);
    virtual ~PluginProxy();

    void initialize();
    bool start();
    bool stop();

private:
    plugin::Plugin * plugin_;
    const PluginApi pluginApi_;
};

}

#endif // PLUGINPROXY_HPP
