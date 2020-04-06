#ifndef PLUGIN_HPP
#define PLUGIN_HPP

#include <memory>

namespace plugio::plugin
{

// forward declaration
class Plugin;
class SpecServer;

// the types of the class factories                                          
typedef Plugin* createPluginFn();                                                 
typedef void destroyPluginFn(Plugin*);

// signals
typedef void onInChangeFn(void *, int, const char *);

class Plugin
{
public:
    Plugin();
    virtual ~Plugin();

    //virtual void onSpecConnected(std::shared_ptr<SpecServer> specServer) = 0;


private:

};

}

#endif // PLUGIN_HPP
