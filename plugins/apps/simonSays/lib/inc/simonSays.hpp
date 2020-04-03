#ifndef SIMONSAYS_HPP
#define SIMONSAYS_HPP

#include "plugin.hpp"
#include "logger.hpp"

#include <iostream>

namespace lsls {

class SimonSays : public plugio::plugin::Plugin
{
public:
    SimonSays();
    virtual ~SimonSays();
};

extern "C" plugio::plugin::Plugin * create()
{
    SimonSays * simonSays = new SimonSays();
    plugio::plugin::Plugin * plugin = static_cast<plugio::plugin::Plugin *>(simonSays);
    std::cout << "create function simonsays=" << (void*)simonSays << " plugin=" << (void*)plugin << std::endl;
    return plugin;
}

}

#endif // SIMONSAYS_HPP
