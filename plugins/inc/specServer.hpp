#ifndef SPECSERVER_HPP
#define SPECSERVER_HPP

#include "plugin.hpp"

#include <functional>
#include <vector>

namespace plugio::plugin
{

class SpecServer
{
public:

    class IInChangeSubscriber
    {
        virtual void onInChange(int signal, bool value) { };
        virtual void onInChange(int signal, double value) { };
        virtual void onInChange(int signal, const char * value) { };
    };

    explicit SpecServer(void * specContext);
    virtual ~SpecServer() { }

    bool readInSignal(int signal, bool & value) const;
    bool readInSignal(int signal, double & value) const;
    bool readInSignal(int signal, const char * value) const;

    bool writeOutSignal(int signal, bool value);
    bool writeOutSignal(int signal, double value);
    bool writeOutSignal(int signal, const char * value);
    
    void subscribe(IInChangeSubscriber * subscriber);

    void onInChange(int signal, bool value);
    void onInChange(int signal, double value);
    void onInChange(int signal, const char * value);

private:
    SpecServer() = delete;
    void * specContext_;
    std::vector<IInChangeSubscriber*> subscribers_;
};

}

#endif // SPECSERVER_HPP