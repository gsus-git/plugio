#ifndef SPECSERVERPROXY_HPP
#define SPECSERVERPROXY_HPP

#include "plugin.hpp"

namespace plugio::framework::core {

class SpecServer
{
public:
    SpecServer();
    virtual ~SpecServer() {}

    void readInSignal(int signal, char * value) const;
    void writeOutSignal(int signal, const char * value);
};

}

#endif // SPECSERVERPROXY_HPP