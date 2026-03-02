cmake_minimum_required(VERSION 3.18)

project(TestMyMath
    VERSION 1.0.0
    DESCRIPTION "A demo for using CTest in C++ project."
    LANGUAGES CXX
)

include(CTest)

add_executable(main main.cpp)

find_package(MyMath CONFIG REQUIRED)

target_link_libraries(main PRIVATE MyMath::MyMath)

# 添加测试Case到CTest
add_test(
    NAME TestMyMath # 任意测试名称
    COMMAND main
)