

InConnectorStub::InConnectorStub(void * cConstructor, void * cDestructor) :
    cDestructor_(cDestructor)
{
    inConnector_ = cConstructor();
}

InConnectorStub::~InConnectorStub()
{
    cDestructor_();
}