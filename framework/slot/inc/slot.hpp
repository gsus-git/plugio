#ifndef SLOT_HPP
#define SLOT_HPP

#include "signal.hpp"
#include "signalTypes.hpp"

#include <string>
#include <memory>

namespace plugio::framework::core {

class SlotBase
{
public:
    SlotBase(const std::string & name);
    virtual ~SlotBase();

    virtual void signalChange(Boolean value);
    virtual void signalChange(Number value);

protected:
    const std::string name_;
};

template <typename T>
class Slot : public SlotBase
{
public:
    using SlotBase::signalChange;

    Slot(const std::string & name);
    virtual ~Slot();

    void connect(std::shared_ptr<Signal<T>> signal)
    {
        signal_ = signal;
        connectionId_ = signal_->connect(&signalChange);
    }

    void disconnect()
    {
        if (isConnected())
        {
            signal_->disconnect(connectionId_);
        }
        signal_ = nullptr;
    }

    bool isConnected()
    {
        return signal_;
    }

    void signalChange(T value) override
    {
        
    }

private:
    Signal<T> signal_;
    SignalBase::ConnectionId connectionId_;
};

}

#endif // SLOT_HPP
