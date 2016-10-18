cmake_minimum_required(VERSION 3.6)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

find_package(Boost 1.61.0)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(BoostTest1 keyTest.cpp)
target_link_libraries(BoostTest1 ${Boost_LIBRARIES})

add_executable(runBasicTests
        basic_check.cpp
        keyTest.cpp)

target_link_libraries(runBasicTests gtest gtest_main)
target_link_libraries(runBasicTests gmock gmock_main)
#target_link_libraries(runBasicTests src)