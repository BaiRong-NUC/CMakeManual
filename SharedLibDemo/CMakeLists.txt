cmake_minimum_required(VERSION 3.18)

project(SharedLibDemo
    VERSION 1.0.0
    DESCRIPTION "A demo for CMake shared library"
    LANGUAGES CXX
)

# 添加目录层级
add_subdirectory(math_lib) # 添加math_lib子目录,该目录下必须有CMakeLists.txt文件,会在该目录下执行CMakeLists.txt中的命令
add_subdirectory(app)