#ifndef INCONNECTORSTUB_HPP
#define INCONNECTORSTUB_HPP

#include "plugin.hpp"

namespace plugio::framework::core {

class InConnectorStub
{
public:
    InConnectorStub(void * cConstructor, void * cDestructor);
    ~InConnectorStub();

private:
    InConnectorStub() = delete;
    void * cDestructor_;
    void * inConnector_;
};

}

#endif // INCONNECTORSTUB_HPP