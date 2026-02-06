# 一. CMake 使用流程

1. cmake_minimum_required() 设置运行CMake的最低版本，确保使用的CMake版本支持所需的功能和语法。
2. 设置项目名称
   project(CMakeManual) 定义了项目的名称，这个名称可以在构建过程中使用，例如生成的可执行文件或库的名称。
3. 设置构建目标,第一个参数是目标的名称，第二个参数是源文件列表，这里只有一个源文件 server.cpp。CMake会根据这个信息生成构建系统所需的文件，例如 Makefile 或 Visual Studio 项目文件，以便编译和链接生成可执行文件 ServerDemo。
   add_executable(ServerDemo server.cpp)
4. cmake + CMakeList.txt 路径 命令生成makefile文件
5. make 命令使用makefile编译生成可执行文件 ServerDemo
