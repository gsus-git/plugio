#ifndef SPECSERVER_HPP
#define SPECSERVER_HPP

#include <functional>
#include <vector>

namespace plugio::plugin
{

class SignalValue
{
public:
    SignalValue(bool value);
    SignalValue(double value);
    SignalValue(const std::string value);

    bool asBool() const;
    double asNumber() const;
    const std::string & asStr() const;

private:
    SignalValue() = delete;
    const std::string value_;
};

class SpecServerProxy
{
public:

    class IInChangeSubscriber
    {
    public:
        virtual void onInChange(int signal, SignalValue value) = 0;
    };

    SpecServerProxy(void * specContext);
    virtual ~SpecServerProxy();

    SignalValue readInSignal(int signal) const;

    void writeOutSignal(int signal, bool value);
    void writeOutSignal(int signal, double value);
    void writeOutSignal(int signal, const std::string & value);
    
    void subscribe(IInChangeSubscriber * subscriber);

    void onInChange(int signal, SignalValue value);

private:
    SpecServerProxy() = delete;
    void * specContext_;
    std::vector<IInChangeSubscriber*> subscribers_;
};

}

#endif // SPECSERVER_HPP