#ifndef SPECSERVERPROXY_HPP
#define SPECSERVERPROXY_HPP

#include "plugin.hpp"

namespace plugio::framework::core {

class SpecServerProxy
{
public:
    SpecServerProxy();
    virtual ~SpecServerProxy() {}

    void readInSignal(int signal, char * value) const;

    void writeOutSignal(int signal, const char * value);

private:
};

}

#endif // SPECSERVERPROXY_HPP