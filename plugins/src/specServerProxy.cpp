#include "specServerProxy.hpp"
#include "plugin.hpp"

extern void readSignal(void *, int, char *);
extern void writeSignal(void *, int, const char *);

namespace plugio::plugin
{

SignalValue::SignalValue(bool value) :
    value_(std::to_string(value))
{ }

SignalValue::SignalValue(double value) :
    value_(std::to_string(value))
{ }

SignalValue::SignalValue(const std::string value) :
    value_(value)
{ }

bool SignalValue::asBool() const
{
    return std::stoi(value_);
}

double SignalValue::asNumber() const
{
    return std::stod(value_);
}

const std::string & SignalValue::asStr() const
{
    return value_;
}

SpecServerProxy::SpecServerProxy(void * specContext) :
    specContext_(specContext) 
{ }

SpecServerProxy::~SpecServerProxy() 
{ }

SignalValue SpecServerProxy::readInSignal(int signal) const
{
    char data[128];
    readSignal(specContext_, signal, &data[0]);
    return SignalValue(&data[0]);
}

void SpecServerProxy::writeOutSignal(int signal, bool value)
{
    writeSignal(specContext_, signal, SignalValue(value).asStr().c_str());
}

void SpecServerProxy::writeOutSignal(int signal, double value)
{
    writeSignal(specContext_, signal, SignalValue(value).asStr().c_str());
}

void SpecServerProxy::writeOutSignal(int signal, const std::string & value)
{
    writeSignal(specContext_, signal, SignalValue(value).asStr().c_str());
}

void SpecServerProxy::subscribe(SpecServerProxy::IInChangeSubscriber * subscriber)
{
    subscribers_.push_back(subscriber);
}

void SpecServerProxy::onInChange(int signal, SignalValue value)
{
    for (auto subscriber : subscribers_)
    {
        subscriber->onInChange(signal, value);
    }
}

}