add_library(pluginProxy STATIC inc/pluginProxy.hpp src/pluginProxy.cpp)
target_include_directories(pluginProxy PUBLIC "${PROJECT_SOURCE_DIR}/framework/pluginProxy/inc")
target_link_libraries(
    pluginProxy 
    ${CMAKE_DL_LIBS}
    plugin
    signal)
