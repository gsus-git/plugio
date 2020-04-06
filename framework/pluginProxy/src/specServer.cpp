#include "specServer.hpp"

namespace plugio::framework::core {

extern "C"
{
    // signals
    void readInSignal(void * specServerContext, int signal, char * value)
    {
        if (specServerContext)
        {
            static_cast<plugio::framework::core::SpecServer*>(specServerContext)->readInSignal(signal, value);
        }
    }

    void writeOutSignal(void * specServerContext, int signal, const char * value)
    {
        if (specServerContext)
        {
            static_cast<plugio::framework::core::SpecServer*>(specServerContext)->writeOutSignal(signal, value);
        }
    }
}

SpecServer::SpecServer()
{
}

void SpecServer::readInSignal(int signal, char * value) const
{
}

void SpecServer::writeOutSignal(int signal, const char * value)
{
}

}