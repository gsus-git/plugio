#include <iostream>
#include <vector>
#include <memory>

#include "packageManager.hpp"
#include "pluginLoader.hpp"

int main(int argc, char *argv[])
{
    plugio::framework::core::PluginLoader pl;
    plugio::framework::core::PackageManager pm(&pl);

    std::cout << "-----------initializing----------" << std::endl;
    pm.initialize();

    std::cout << "------------installing-----------" << std::endl;
    pm.installPackage("/tmp/simonSays.tar.gz");

    std::cout << "--------creating instance--------" << std::endl;
    auto dev = pl.createInstance(1);    
    
    return 0;
}
