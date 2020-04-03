add_library(simonSays SHARED
    ${PROJECT_SOURCE_DIR}/plugins/inc/plugin.hpp
    ${PROJECT_SOURCE_DIR}/plugins/src/plugin.cpp
    lib/inc/simonSays.hpp
    lib/src/simonSays.cpp)
set_target_properties(simonSays PROPERTIES SOVERSION 1)
target_include_directories(simonSays PUBLIC
    "${PROJECT_SOURCE_DIR}/plugins/inc"
    "${PROJECT_SOURCE_DIR}/plugins/apps/simonSays/lib/inc")
target_link_libraries(
    simonSays
    plugin)
