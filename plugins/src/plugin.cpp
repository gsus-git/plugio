#include <iostream>

#include "plugin.hpp"

namespace plugio::plugin
{

Plugin::Plugin()
{
    std::cout << "VERBOSE: Plugin constructor" << std::endl;
}

Plugin::~Plugin()
{
    std::cout << "VERBOSE: Plugin destructor" << std::endl;
}

}

extern "C" 
{

void destroy(Plugin* p)
{
    delete p;
}

void setReadInSignalB(readSignalBFn)
{
    Plugin::readInSignalB = readSignalBFn;
}

void setReadInSignalN(readSignalNFn)
{
    Plugin::readInSignalN = readSignalNFn;
}

void setReadInSignalS(readSignalSFn)
{
    Plugin::readInSignalS = readSignalSFn;
}

void setwriteOutSignalB(writeOutSignalBFn)
{
    Plugin::writeOutSignalB = writeOutSignalBFn;
}

void setwriteOutSignalN(writeOutSignalNFn)
{
    Plugin::writeOutSignalN = writeOutSignalNFn;
}

void setwriteOutSignalS(writeOutSignalSFn)
{
    Plugin::writeOutSignalS = writeOutSignalSFn;
}

void onInBChange(void * specServerContext, int signal, bool value)
{
    static_cast<plugio::plugin::SpecServer *>(specServerContext)->onInChange(signal, value);
}

void onInNChange(void * specServerContext, int signal, double value)
{
    static_cast<plugio::plugin::SpecServer *>(specServerContext)->onInChange(signal, value);
}

void onInSChange(void * specServerContext, int signal, const char * value)
{
    static_cast<plugio::plugin::SpecServer *>(specServerContext)->onInChange(signal, value);
}

}
