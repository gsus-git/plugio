#include <iostream>

#include "plugin.hpp"
#include "specServer.hpp"

namespace plugio::plugin
{

Plugin::Plugin()
{
    std::shared_ptr<SpecServer> specServer;

    std::cout << "VERBOSE: Plugin constructor" << std::endl;
}

Plugin::~Plugin()
{
    std::cout << "VERBOSE: Plugin destructor" << std::endl;
}

}

extern "C" 
{

void destroy(plugio::plugin::Plugin * p)
{
    delete p;
}

void onInBChange(void * specServerContext, int signal, const char * value)
{
    static_cast<plugio::plugin::SpecServer *>(specServerContext)->onInChange(signal, value);
}

}
