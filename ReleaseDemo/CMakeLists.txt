cmake_minimum_required(VERSION 3.18...4.0)

project(ReleaseDemo
    VERSION 1.0
    DESCRIPTION "A demo for CMake install"
    LANGUAGES CXX
)

add_executable(ReleaseDemo main.cpp)

include(GNUInstallDirs)
install(TARGETS ReleaseDemo)

message(STATUS "PROJECT_NAME 内置变量: ${PROJECT_NAME}")