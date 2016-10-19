cmake_minimum_required(VERSION 3.6)
project(KeyDetection)

find_package(Boost 1.61.0)
include_directories(${Boost_INCLUDE_DIRS})
add_executable(BoostTest main.cpp)
target_link_libraries(BoostTest ${Boost_LIBRARIES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(src_run ${SOURCE_FILES})
#add_executable(libsndfile_run ${SOURCE_FILES})



include_directories(src)
include_directories(lib)

#link_directories(lib)
#link_libraries(libsndfile)

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

target_link_libraries(src_run src)
target_link_libraries(src_run libsndfile)

