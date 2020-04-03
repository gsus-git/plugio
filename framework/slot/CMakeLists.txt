add_library(slot STATIC inc/slot.hpp src/slot.cpp)
target_include_directories(slot PUBLIC "${PROJECT_SOURCE_DIR}/framework/slot/inc")
target_link_libraries(
    slot
    signal 
    pluginProxy)
