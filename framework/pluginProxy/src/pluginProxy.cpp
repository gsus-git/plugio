#include "specServer.hpp"
#include "pluginProxy.hpp"
#include "plugin.hpp"

#include <iostream>

extern "C"
{
    // signals
    void readInSignal(void * specServerContext, int signal, char * value)
    {
        static_cast<plugio::framework::core::SpecServer*>(specServerContext)->readInSignal(signal, value);
    }

    void writeOutSignal(void * specServerContext, int signal, const char * value)
    {
        static_cast<plugio::framework::core::SpecServer*>(specServerContext)->writeOutSignal(signal, value);
    }
}

namespace plugio::framework::core {

PluginApi::PluginApi() :
    constructor(nullptr),
    destructor(nullptr)
 {}

PluginProxy::PluginProxy(const PluginApi & pluginApi) :
    pluginApi_(pluginApi)
{
    std::cout << "VERBOSE: Constructing PluginProxy" << std::endl;
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