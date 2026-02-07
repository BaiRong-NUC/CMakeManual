# 1. 设置最低的CMake版本
cmake_minimum_required(VERSION 3.18)
# 2. 设置项目名称
project(CMakeTools)
# 3. 添加构建目标
add_executable(CMakeTools CMakeToos.cpp)
# 4. 集成单元测试
include(CTest)
add_test(
    NAME TestAdd # 测试场景标识
    COMMAND CMakeTools
)
# 5. 本地安装
include(GNUInstallDirs) # 获取系统默认的安装路径 /user/local/bin
install(TARGETS CMakeTools)
# 6. 打包
include(CPack)