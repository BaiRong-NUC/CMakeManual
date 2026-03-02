cmake_minimum_required(VERSION 3.18)

project(JsonCppDemo
    VERSION 1.0.0
    DESCRIPTION "A demo for using JsonCpp library in C++ project."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 11) # 设置C++11标准

find_package(jsoncpp CONFIG REQUIRED)

add_executable(main main.cpp)

# 使用JsonCpp::JsonCpp优先使用静态库,没有静态库使用动态库
# target_link_libraries(main PRIVATE JsonCpp::JsonCpp)
# target_link_libraries(main PRIVATE jsoncpp_static) # 强制使用静态库
target_link_libraries(main PRIVATE jsoncpp_lib) # 强制使用动态库