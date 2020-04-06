#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include "signalTypes.hpp"

#include <map>
#include <mutex>
#include <functional>

// temporary
#include <iostream>

namespace plugio::framework::core {

/**
 * A signal holds a state and when it changes, the observers are notified.
 */
class Signal
{
public:
    using ConnectionId = uint32_t;
    using SignalId     = size_t;

    /**
     * Constructor.
     *
     * @param value is the initial value of the signal when it is created
     */
    Signal(SignalId id, const std::string & value) :
        value_(value),
        connectionIdCounter_(0),
        id_(id)
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
    void set(const std::string & value)
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
    std::string get() const
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
    ConnectionId connect(std::function<void(const std::string &)> slot)
    {
        std::scoped_lock<std::mutex> lock(mutex_);
        
        ConnectionId id = ++connectionIdCounter_;
        slots_.insert(std::pair<ConnectionId, std::function<void(const std::string &)>>(id, slot));
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
    std::string value_;
    // id assign to connections
    ConnectionId connectionIdCounter_;
    // this signal id
    SignalId id_;
    // list of slots called when the state of the signal changes
    std::map<ConnectionId, std::function<void(std::string)>> slots_;
};

}

#endif /* SIGNAL_HPP */
