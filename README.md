# 目录

- [一. CMake 使用流程](#一-cmake-使用流程-cmaketset)
- [二. 程序构建过程与CMake命令行介绍](#二-程序构建过程与cmake命令行介绍-cmaketools)
    - [(1) 生成构建系统](#1-生成构建系统)
    - [(2) 编译链接](#2-编译链接)
    - [(3) 测试](#3-测试)
    - [(4) 本地安装](#4-本地安装)

# 一. CMake 使用流程 CMakeTest/

1. cmake_minimum_required() 设置运行CMake的最低版本，确保使用的CMake版本支持所需的功能和语法。
2. 设置项目名称
   project(CMakeManual) 定义了项目的名称，这个名称可以在构建过程中使用，例如生成的可执行文件或库的名称。
3. 设置构建目标,第一个参数是目标的名称，第二个参数是源文件列表，这里只有一个源文件 server.cpp。CMake会根据这个信息生成构建系统所需的文件，例如 Makefile 或 Visual Studio 项目文件，以便编译和链接生成可执行文件 ServerDemo。
   add_executable(ServerDemo server.cpp)
4. cmake + CMakeList.txt 路径 命令生成makefile文件
5. make 命令使用makefile编译生成可执行文件 ServerDemo

# 二. 程序构建过程与CMake命令行介绍 CMakeTools/

1. cmake -> ctest -> cpack

2. cmake:
    - 生成构建系统
    - 编译链接
    - 本地安装
    - 脚本模式
    - 命令行模式
3. ctest: 集成测试
4. cpack: 打包

## (1) 生成构建系统

1. 源内构建和源外构建
    - 源内构建：在源代码目录中直接运行 cmake 命令，生成构建文件和编译结果都在同一目录下。
    - 源外构建：在源代码目录之外创建一个单独的构建目录，在该目录中运行 cmake 命令，生成的构建文件和编译结果都在这个独立的目录中。这种方式可以保持源代码目录的整洁，并且允许多个不同的构建配置（例如 Debug 和 Release）共存。
        - cmake -S <cmakelist_dir> -B <build_dir>
        - cmake <path_to_existing_build_dir>
        - cmake <cmakelist_dir> (默认在当前目录生成构建文件)

2. CMakeLists.txt: 源代码目录根<cmakelist_dir>; CMakeCache.txt: 记录构建目录根<build_dir>;

## (2) 编译链接

1. cmake --build <build_dir>
2. make

## (3) 测试

1. ctest
2. make test
3. ctest路径保存在CTestTestfile.cmake中

## (4) 本地安装

1. cmake --install <build_dir>
2. make install
3. -- Installing: /usr/local/bin/CMakeToos (安装路径保存在CMakeCache.txt中)
4. 注意: 安装之前,CMakeTools这个程序在自己账户的构建目录下,这是个临时目录.安装之后,CMakeTools这个程序被复制到/usr/local/bin目录下,这是个公共目录,所有用户都可以访问.因此,安装之后,CMakeTools这个程序不再是临时的,而是永久的,可以在任何时候使用.
5. GNUInstallDirs: CMake内置模块,定义了不同平台的安装路径
6. install_manifest.txt: 资源清单,记录已经安装文件列表
