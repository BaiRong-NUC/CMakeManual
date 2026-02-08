# 目录

- [一. CMake 使用流程](#一-cmake-使用流程-cmaketset)
- [二. 程序构建过程与CMake命令行介绍](#二-程序构建过程与cmake命令行介绍-cmaketools)
    - [(1) 生成构建系统](#1-生成构建系统)
    - [(2) 编译链接](#2-编译链接)
    - [(3) 测试](#3-测试)
    - [(4) 本地安装](#4-本地安装)
    - [(5) 打包](#5-打包)
    - [(6) 脚本模式](#6-脚本模式)
    - [(7) 命令行模式](#7-命令行模式)
- [三. CMake工程实践场景](#三-CMake工程实践场景与常见命令)
    - [(1) 发布可执行程序](#1-发布可执行程序-releasedemo)
    - [(2) 链接静态库](#2-链接静态库-staticlibdemo)

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
3. CMAKE_MAKE_PROGRAM:FILEPATH=/usr/bin/gmake(生成构建系统时,cmake会自动检测系统上可用的构建工具,并将其路径保存在CMAKE_MAKE_PROGRAM变量中.在这个例子中,CMAKE_MAKE_PROGRAM的值是/usr/bin/gmake,表示使用GNU Make作为构建工具.当执行cmake --build命令时,CMake会调用CMAKE_MAKE_PROGRAM指定的构建工具来编译和链接项目. /usr/bin/gmake(软连接) -> make\*)

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

## (5) 打包

1. cpack
2. make package
3. cpack 默认收集install对应的目标,然后把收集到的目标打包在压缩包里
4. cpack 执行步骤
    - (1) 设置临时安装目录(<build_dir>/\_CPack_Packages/Linux/STGZ)
    - (2) 执行cmake --install (cmake_install.cmake) 把目标安装到临时安装目录
    - (3) 收集临时目录的文件列表
    - (4) 执行打包,拷贝压缩包到构建目录
5. CPackConfig.cmake: CPack配置文件,定义了打包的相关信息和选项(生成包格式,包名称,包版本)
    - set(CPACK_GENERATOR "STGZ;TGZ;TZ") 指定生成的包格式,这里指定了三种格式: STGZ, TGZ, TZ
    - set(CPACK_PACKAGE_FILE_NAME "CMakeTools-0.1.1-Linux") 指定生成的包名称,这里指定了包名称为 CMakeTools-0.1.1-Linux (包名称 = 包名称前缀+包版本+平台信息)

## (6) 脚本模式

1. cmake -P <script_file> -Process script mode (eg: cmake -P cmake_install.cmake)

2. cmake 脚本模式不会生成构建产物,也不会生成中间过程,适合处理各种与构建系统无关的自动化任务,例如环境检测,文件处理,部署打包等功能

## (7) 命令行模式

1. cmake -E <command> -Process command mode (eg: cmake -E copy <source> <destination> 拷贝文件)

# 三. CMake工程实践场景与常见命令

## (1) 发布可执行程序 ReleaseDemo/

1. 介绍: 编译链接生成本地运行的程序,将其安装到系统目录下,供所有用户使用

2. 流程: mkdir build -> cd build -> cmake ../(CMakeLists.txt) -> cmake --build(make) . -> cmake --install (make install).

3. cmake_minimum_required(VERSION 3.18...4.0) 指定版本范围,cmake_minimum_required必须在顶层,必须在Project命令之前,不推荐在函数中调用

4. project() 定义项目名称,LANGUAGE指定使用的编程语言(默认使用C/C++),VERSION指定项目版本,DESCRIPTION指定项目描述信息。

5. LANGUAGE指定使用的编程语言后CMake会自动检测系统是否安装编译器,生成CMakeFiles文件夹(简单的案例)检测编译器是否安装成功,如果没有安装编译器会报错,探测结果保存到CMakeFiles/3.26.5/CMakeCCompiler.cmake

6. message() 输出消息,可以在生成构建系统时显示一些信息 =printf,第一个参数为消息类型,第二个参数为消息内容,这里没有指定消息类型,默认是STATUS,表示普通信息

7. include() 加载指定脚本文件/模块到当前上下文 (TestInclude/)
    - 文件搜索路径: 如果指定相对路径,则相对于当前CMakeLists.txt所在目录,如果指定绝对路径,则直接加载该路径的文件
    - Module搜索路径: 现在当前目录查找,如果没有找到,则在CMAKE_MODULE_PATH指定的路径中查找,如果还没有找到,则在CMake安装目录的Modules子目录中查找
    - 当要真实获取正在执行cmake脚本路径时,需要使用CMAKE_CURRENT_LIST_DIR

8. install(): 将二进制,静态库,动态库,头文件部署到指定目录
    - 目标文件: install(TARGETS <target> DESTINATION <dir>) 将add_executable/add_library添加的目标安装到指定目录
    - 资源文件: install(FILES <files> DESTINATION <dir>) 将资源文件安装到指定目录
    - 目录: install(DIRECTORY <dirs> DESTINATION <dir>) 将目录安装到指定目录

9. add_executable() 定义可执行文件目标,第一个参数是目标名称(唯一),第二个参数是源文件列表,可以指定多个源文件
    - 可执行文件默认会生成在构建目录树中,位置对应于源代码树中调用命令的目录例如：源码在 src/app/main.cpp，构建目录是 build/，则可执行文件默认生成在 build/src/app/ 下

## (2) 链接静态库 StaticLibDemo/
