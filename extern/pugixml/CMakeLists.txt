add_library(extern_pugixml STATIC src/pugixml.hpp src/pugixml.cpp src/pugiconfig.hpp)
target_include_directories(extern_pugixml PUBLIC "${PROJECT_SOURCE_DIR}/extern/pugixml/src")
target_link_libraries(
    extern_pugixml)
