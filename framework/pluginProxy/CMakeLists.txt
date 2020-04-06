add_library(pluginProxy STATIC inc/pluginProxy.hpp
                               inc/specServer.hpp
                               src/pluginProxy.cpp
                               src/specServer.cpp)
target_include_directories(pluginProxy PUBLIC "${PROJECT_SOURCE_DIR}/framework/pluginProxy/inc")
target_link_libraries(
    pluginProxy 
    ${CMAKE_DL_LIBS}
    plugin)
