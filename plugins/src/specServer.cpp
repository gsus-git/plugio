#include "specServer.hpp"

namespace plugio::plugin
{
    SpecServer::SpecServer(void * specContext) :
        specContext_(specContext) 
    { }
    
    SpecServer::~SpecServer() 
    { }

    bool SpecServer::readInSignal(int signal, bool & value) const
    {
        Plugin::readInSignalB(specContext_, signal, value);
    }

    bool SpecServer::readInSignal(int signal, double & value) const
    {
        Plugin::readInSignalN(specContext_, signal, value);
    }

    bool SpecServer::readInSignal(int signal, const char * value) const
    {
        Plugin::readInSignalS(specContext_, signal, value);
    }

    bool SpecServer::writeOutSignal(int signal, bool value)
    {
        Plugin::writeOutSignalB(specContext_, signal, value);
    }

    bool SpecServer::writeOutSignal(int signal, double value)
    {
        Plugin::writeOutSignalN(specContext_, signal, value);
    }
    
    bool SpecServer::writeOutSignal(int signal, const char * value)
    {
        Plugin::writeOutSignalS(specContext_, signal, value);
    }

    void SpecServer::subscribe(IInChangeSubscriber * subscriber);
    {
        subscribers_.push_back(subscriber);
    }

    void onInChange(int signal, bool value)
    {
        for (auto subscriber : subscribers_)
        {
            subscriber->onInChange(signal, value);
        }
    }

    void onInChange(int signal, double value)
    {
        for (auto subscriber : subscribers_)
        {
            subscriber->onInChange(signal, value);
        }
    }

    void onInChange(int signal, const char * value)
    {
        for (auto subscriber : subscribers_)
        {
            subscriber->onInChange(signal, value);
        }
    }
}