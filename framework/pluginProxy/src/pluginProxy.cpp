#include "signal.hpp"
#include "pluginProxy.hpp"
#include "plugin.hpp"

#include <iostream>

extern "C"
{
    uint32_t p_api_getApiVersion(void * pluginProxyContext_)
    {
        return 1;
    }

    // signals
    bool readInSignalB(void * specServerProxyContext, int signal, bool & value)
    {
        return static_cast<SpecServerProxy*>(specServerProxyContext)->readIn(signal, value);
    }

    bool readInSignalN(void * specServerProxyContext, int signal, double & value)
    {
        return static_cast<SpecServerProxy*>(specServerProxyContext)->readIn(signal, value);
    }

    bool readInSignalS(void * specServerProxyContext, int signal, const char * value)
    {
        return static_cast<SpecServerProxy*>(specServerProxyContext)->readIn(signal, value);
    }

    bool writeSignalB(void * specServerProxyContext, int signal, bool value)
    {
        return static_cast<SpecServerProxy*>(specServerProxyContext)->writeOut(signal, value);
    }

    bool writeSignalN(void * specServerProxyContext, int signal, double value)
    {
        return static_cast<SpecServerProxy*>(specServerProxyContext)->writeOut(signal, value);
    }

    bool writeSignalS(void * specServerProxyContext, int signal, const char * value)
    {
        return static_cast<SpecServerProxy*>(specServerProxyContext)->writeOut(signal, value);
    }
}

namespace plugio::framework::core {

PluginApi::PluginApi() :
    constructor(nullptr),
    destructor(nullptr),
    readInSignalB(nullptr),
    readInSignalN(nullptr),
    readInSignalS(nullptr),
    writeOutSignalB(nullptr),
    writeOutSignalN(nullptr),
    writeOutSignalS(nullptr)
 {}

PluginProxy::PluginProxy(const PluginApi & pluginApi) :
    pluginApi_(pluginApi)
{
    std::cout << "VERBOSE: Constructing PluginProxy" << std::endl;
    // signal's setters
    pluginApi_.setReadInSignalB(&readInSignalB);
    pluginApi_.setReadInSignalN(&readInSignalN);
    pluginApi_.setReadInSignalS(&readInSignalS);
    // signal's getters
    pluginApi_.setWriteOutSignalB(&writeOutSignalB);
    pluginApi_.setWriteOutSignalN(&swriteOutSignalN);
    pluginApi_.setWriteOutSignalS(&writeOutSignalS);

    plugin_ = pluginApi_.constructor();
}

PluginProxy::~PluginProxy() 
{
    std::cout << "VERBOSE: Destructing PluginProxy" << std::endl;
    pluginApi_.destructor(plugin_);
    plugin_ = nullptr;
}

void PluginProxy::initialize()
{

}

bool PluginProxy::start()
{
    std::cout << "Start!" << std::endl;
    return true;
}

bool PluginProxy::stop()
{
    std::cout << "Stop!" << std::endl;
    return true;
}

}

