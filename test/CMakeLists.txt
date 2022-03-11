cmake_minimum_required(VERSION 3.1)

project(tests)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

enable_testing()

find_package(Qt5Widgets REQUIRED)

set(COMPILE_OPTIONS -std=c++11)



add_executable(tests test.cpp)
target_link_libraries(tests PRIVATE Qt5::Widgets)
target_link_libraries(tests
                      PRIVATE gtest_main
                      gtest
                      -lpthread
                      )   
target_compile_options(tests PRIVATE ${COMPILE_OPTIONS})

include(GoogleTest)
gtest_discover_tests(tests)

