project(test)

set(gtest_disable_pthreads on)

add_subdirectory(lib/gtest)
add_subdirectory(basic_tests)