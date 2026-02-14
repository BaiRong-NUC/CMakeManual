cmake_minimum_required(VERSION 3.18)
project(UseStaticLib LANGUAGES CXX)
add_executable(main main.cpp)

# 查找MyMath库
find_package(MyMath CONFIG REQUIRED) 
# 查找MyMath库,CONFIG表示查找Config.cmake文件,REQUIRED表示如果没有找到库则报错

# 声明依赖
target_link_libraries(main PRIVATE MyMath::MyMath)

