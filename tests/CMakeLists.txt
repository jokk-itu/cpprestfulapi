cmake_minimum_required(VERSION 3.9)
set(This CPPTEMPLATE_TESTS)
project(${This})

set(Source ExampleTest.cpp)

add_executable(${This} ${Source})
target_link_libraries(${This} gtest gmock pthread gtest_main)
enable_testing()
add_test(${This} ${This})