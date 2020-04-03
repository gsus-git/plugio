add_library(signal INTERFACE)
target_sources(signal INTERFACE inc/signal.hpp)
target_include_directories(signal INTERFACE
  "${PROJECT_SOURCE_DIR}/framework/signal/inc")
