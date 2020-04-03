#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "signalTypes.hpp"

#include <map>
#include <mutex>
#include <functional>

// temporary
#include <iostream>

namespace plugio::framework::core {

class SignalBase
{
public:
    using ConnectionId = uint32_t;
    using SignalId     = size_t;

    static const ConnectionId InvalidConnectionId = 0;

    SignalBase(SignalId id) : 
        id_(id) 
    {}

    virtual ~SignalBase()
    {
        std::cout << "Destroying SignalBase" << std::endl;
    }

    ConnectionId connect(std::function<void(Boolean)> slot)
    {
        std::cout << "Error: This signal does not support Boolean" << std::endl;
        return InvalidConnectionId;
    }

    ConnectionId connect(std::function<void(Number)> slot)
    {
        std::cout << "Error: This signal does not support Number" << std::endl;
        return InvalidConnectionId;
    }

protected:
    // signal id
    SignalId id_;
};

/**
 * A signal holds a state and when it changes, the observers are notified.
 */
template<typename T>
class Signal : public SignalBase
{
public:
    /**
     * Constructor.
     *
     * @param value is the initial value of the signal when it is created
     */
    Signal(SignalId id, T value) :
        value_(value),
        connectionIdCounter_(0),
        SignalBase(id)
    {}

    Signal() = delete;
    
    /**
     * Destructor.
     */
    ~Signal()
    {
        std::cout << "Destroying signal with id " << id_ << std::endl;
    } 

    /**
     * Changes the value of the signal. If the new value is different than the
     * previous one, then the signal will propagate to the slots.
     *
     * @param value is the new value of the signal.
     */
    void set(T value)
    {
        std::scoped_lock<std::mutex> lock(mutex_);
        
        if (value_ != value)
        {
            value_ = value;
            notifySlots();
        }
    }

    /**
     * Method to retrieve the current value of the signal. The value retrieved
     * is the last one that has been successfully propagated to all the slots 
     * connected.
     *
     * @return the current value.
     */
    T get() const
    {
        std::scoped_lock<std::mutex> lock(mutex_);

        return value_;
    }

    /**
     * Connect a signal to a slot
     *
     * @param callback.
     * @return the connection id. Needed to unsubscribe.
     */
    ConnectionId connect(std::function<void(T)> slot)
    {
        std::scoped_lock<std::mutex> lock(mutex_);
        
        ConnectionId id = ++connectionIdCounter_;
        slots_.insert(std::pair<ConnectionId, std::function<void(T)>>(id, slot));
        return id;
    }
    
    /**
     * Disconnect a signal from a slot.
     *
     * @param id that identifies the connection.
     */
    void disconnect(ConnectionId id)
    {
        std::scoped_lock<std::mutex> lock(mutex_);

        auto slot = slots_.find(id);
        if (slot != slots_.end())
        {
            slots_.erase(slot);
        }
    }

private:

    /**
     * Notify slots connected to this signal.
     */
    void notifySlots()
    {
        std::scoped_lock<std::mutex> lock(mutex_);

        for (const auto & slot : slots_)
        {
            slot.second(value_);
        }
    }
    
    // mutex
    mutable std::mutex mutex_;
    // variable holding the current value of the signal
    T value_;
    // id assign to connections
    ConnectionId connectionIdCounter_;
    // list of slots called when the state of the signal changes
    std::map<ConnectionId, std::function<void(T)>> slots_;
};

}

#endif /* SIGNAL_HPP */
