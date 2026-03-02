cmake_minimum_required(VERSION 3.18)

project(CPackDemo
    VERSION 1.0.0
    DESCRIPTION "A demo for CPack packaging"
    LANGUAGES CXX
)

# 添加目录层级
add_subdirectory(math_lib) # 添加math_lib子目录,该目录下必须有CMakeLists.txt文件,会在该目录下执行CMakeLists.txt中的命令
add_subdirectory(app)

# 开启打包功能
include(CPack)
set(CPACK_PACKAGE_NAME "CPackDemo")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "your_email@example.com")
set(CPACK_GENERATOR "TGZ;ZIP") # 指定生成的安装包格式,可以是TGZ、ZIP、DEB、RPM等多种格式,根据需要选择
