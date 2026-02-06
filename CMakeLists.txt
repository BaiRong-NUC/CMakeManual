# 1. 设置运行CMake的最低版本
cmake_minimum_required(VERSION 3.18)
# 2. 设置项目名称
project(CMakeManual)
# 3. 设置构建目标
add_executable(ServerDemo server.cpp)