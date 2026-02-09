cmake_minimum_required(VERSION 3.18)

project(SetTargetProperties
    VERSION 1.0.0
    DESCRIPTION "A demo for CMake set_target_properties"
    LANGUAGES CXX
)

add_subdirectory(src)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE add)