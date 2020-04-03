cmake_minimum_required(VERSION 3.1...3.15)

project(Plugio 
    VERSION 1.0
    DESCRIPTION "Plug it right in"
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
# enable testing for this directory and below
#enable_testing()

# add subdirectories to build
add_subdirectory(framework/signal)
add_subdirectory(framework/pluginProxy)
add_subdirectory(framework/slot)
add_subdirectory(framework/packageManager)

# plugins
add_subdirectory(plugins)
add_subdirectory(plugins/apps/simonSays)

add_subdirectory(extern/pugixml)

add_subdirectory(apps/mainApp)
# directory where the unit tests are located
add_subdirectory(tests)
