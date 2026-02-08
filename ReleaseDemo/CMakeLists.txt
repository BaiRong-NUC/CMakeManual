cmake_minimum_required(VERSION 3.18)

project(ReleaseDemo)

add_executable(ReleaseDemo main.cpp)

include(GNUInstallDirs)
install(TARGETS ReleaseDemo)