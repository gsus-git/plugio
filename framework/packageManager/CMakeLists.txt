add_library(packageManager STATIC 
    inc/packageManager.hpp 
    inc/pluginLibLoader.hpp 
    inc/packageManifest.hpp
    src/packageManager.cpp 
    src/pluginLibLoader.cpp
    src/packageManifest.cpp)
target_include_directories(packageManager PUBLIC "${PROJECT_SOURCE_DIR}/framework/packageManager/inc")
target_link_libraries(
    packageManager
    pluginProxy
    plugin
    extern_pugixml
    "stdc++fs")
