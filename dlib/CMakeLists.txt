project(dlib)
cmake_minimum_required(VERSION 3.2.0)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)

set(COMPILE_OPTIONS -std=c++11)

add_library(dlib SHARED test-plugin.cpp)
set_target_properties(dlib PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../Libs/)

target_link_libraries(dlib PRIVATE Qt5::Widgets)
target_compile_options(dlib PRIVATE ${COMPILE_OPTIONS})