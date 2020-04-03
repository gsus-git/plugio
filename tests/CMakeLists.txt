macro(package_add_test TESTNAME)
    add_executable(${TESTNAME} ${ARGN})
    target_link_libraries(${TESTNAME} gtest gmock gtest_main)
    add_test(NAME ${TESTNAME} COMMAND ${TESTNAME})
    set_target_properties(${TESTNAME} PROPERTIES FOLDER tests)
endmacro()

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

package_add_test(signalGtest signalGtest.cpp)
target_link_libraries(signalGtest signal)

#package_add_test(signalManagerTest signalManagerTest.cpp)
#target_link_libraries(signalManagerTest signals)
#target_link_libraries(signalManagerTest signalManager)
