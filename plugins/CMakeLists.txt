add_library(plugin STATIC 
    inc/plugin.hpp
    inc/specServerProxy.hpp 
    src/plugin.cpp 
    src/specServerProxy.cpp)
target_include_directories(plugin PUBLIC "${PROJECT_SOURCE_DIR}/plugins/inc")
target_link_libraries(
    plugin)