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
    - [(3) CMake三大核心(目标Target/属性API Property/属性传递)](#3-CMake三大核心目标target属性api-property属性传递)
    - [(4) CMake属性传递机制案例](#4-CMake属性传递机制案例-targetlinklibrarys)
    - [(5) CMake通用属性设置函数](#5-CMake通用属性设置函数-settargetproperties)
    - [(6) include 与 add_subdirectory区别](#6-include-与-add_subdirectory区别-testinlude)
    - [(7) CMake基于目标的库发布与查找(静态库)](#7-CMake基于目标的库发布与查找静态库-installstaticlib-usestaticlib)
    - [(8) CMake链接动态库](#8-CMake链接动态库-sharedlibdemo)
    - [(9) CMake动态库安装](#9-CMake动态库安装-installsharedlib)
    - [(10) JsonCpp 库的使用](#10-JsonCpp-库的使用-jsoncppdemo)
    - [(11) CTest集成测试](#11-CTest集成测试-ctestdemo)
    - [(12) CPack打包](#12-CPack打包-cpackdemo)
- [四. CMake语法](#四-CMake语法-cmakelanguage)

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

## (3) CMake三大核心(目标Target/属性API Property/属性传递)

1. 目标(Target): CMake中的核心概念之一,表示构建系统中的一个构建产物,可以是可执行文件,静态库,动态库等.目标具有名称和类型,并且可以有各种属性和依赖关系.通过定义目标,可以指定如何编译和链接源代码文件,以及如何安装和使用生成的构建产物.
    - 类型:
        - EXECUTABLE(可执行文件):add_executable() 创建可执行文件目标
        - STATIC(静态库): add_library(... STATIC) 创建静态库目标
        - SHARED(动态库): add_library(... SHARED) 创建动态库目标
        - INTERFACE(接口库): add_library(... INTERFACE) 创建接口库目标
        - OBJECT(对象库): add_library(... OBJECT) 创建对象库目标
2. 属性:
    - Global属性: 影响整个构建系统的属性,例如CMAKE_CXX_STANDARD(指定C++标准版本)
    - 目录属性: 影响特定目录及其子目录的属性,例如INCLUDE_DIRECTORIES(指定包含目录)
    - 目标属性: 影响特定目标的属性,例如LINK_LIBRARIES(指定链接库)
3. 属性作用域与传播范围:
    - PRIVATE: 仅对当前目标有效,不会传播给依赖该目标的其他目标
    - PUBLIC: 对当前目标和依赖该目标的其他目标有效,会传播给依赖该目标的其他目标
    - INTERFACE: 仅对依赖该目标的其他目标有效,不会对当前目标本身产生影响
4. API:
    - 通用属性API: set_target_properties() 设置目标属性, get_target_property() 获取目标属性值
    - 编译阶段: target_compile_features() 指定目标所需的编译特性, target_compile_options() 指定目标的编译选项,target_include_directories() 指定目标的包含目录, target_sources() 指定目标的源文件
    - 链接阶段: target_link_libraries() 指定目标的链接库, target_link_options() 指定目标的链接选项, target_link_directories() 指定目标的链接目录
    - 安装阶段: install(TARGETS <target> DESTINATION <dir>) 将目标安装到指定目录, install(FILES <files> DESTINATION <dir>) 将资源文件安装到指定目录, install(DIRECTORY <dirs> DESTINATION <dir>) 将目录安装到指定目录

5. 流程:
    -   1. 配置期: 目标注册+属性写入
    -   2. 生成期: 属性转化
    -   3. 构建期: 编译链接
    -   4. 安装期: 使用属性生成cmake_install.cmake

## (4) CMake属性传递机制案例 TargetLinkLibrarys/

1. 使用cmake --build <build_dir> -v 查看构建过程,观察属性传递过程

## (5) CMake通用属性设置函数 SetTargetProperties/

1. 使用cmake --build <build_dir> -v 查看构建过程,观察属性设置

2. INTERFACE开头的属性是传播属性,主要指定使用库是需要的特性

## (6) include 与 add_subdirectory区别 TestInlude/

1. include不新建作用域,add_subdirectory会新建一个作用域,在新作用域中执行子目录的CMakeLists.txt

2. include CMAKE_CURRENT_SOURCE_DIR和CMAKE_CURRENT_BINARY_DIR指向父目录,add_subdirectory CMAKE_CURRENT_SOURCE_DIR和CMAKE_BINARY_LIST_DIR指向子目录

3. include与add_subdirectory的CMAKE_CURRENT_LIST_FILE与CMAKE_CURRENT_LIST_DIR指向子目录的CMAKELISTS.txt目录

## (7) CMake基于目标的库发布与查找(静态库) InstallStaticLib/ UseStaticLib/

1. 库安装使用流程
    - 安装头文件和库文件 InstallStaticLib/
        - /usr/local/include/.h
        - /usr/local/lib/.a/.so
    - 定义导入目标,设置头文件和库文件具体属性(set_target_properties): 指导用户如何使用库,包括库的名称,版本,依赖关系等信息
        - /usr/local/lib/cmake/xx/xxConfig.cmake(通过cmake.in模板生成,引用xxTargets.cmake文件)
        - /usr/local/lib/cmake/xx/xxTargets.cmake
    - 使用find_package() 查找库,使用库 UseStaticLib/
        - find_package(xx CONFIG REQUIRED) 查找库,CONFIG表示查找Config.cmake文件,REQUIRED表示如果没有找到库则报错
        - target_link_libraries(main PRIVATE xx::xx) 使用库,xx::xx是导入目标的名称,PRIVATE表示仅对当前目标有效
    - 读取目标属性构建编译链接参数

## (8) CMake链接动态库 SharedLibDemo/

1. 动态库路径机制: CMake(rpath机制) ->gcc -wl,rpath -> ELF的DT_RUNPATH段 -> ld-linux.so动态加载器去ELF中搜索库的搜索路径

## (9) CMake动态库安装 InstallSharedLib/

1. CMake作为库的发布方需要步骤: 发布头文件-> 发布库文件-> 发布导入目标定义CMake文件,这样使用find_package()查找库时才能正确找到库文件和头文件,并且正确设置编译链接参数

2. CMake使用方使用静态库和动态库的方式相同

3. find_package()模式:
    - module模式: 使用方自己编写查找脚本,find_package.cmake
    - config模式: 由库的发布者提供库文件定位与使用信息,使用方不需要手动编写脚本,使用上游定义好的目标完成使用.

## (10) JsonCpp 库的使用 JsonCppDemo/

1. 静态库,动态库导入目标名称在jsoncppConfigVersion.cmake定义

## (11) CTest集成测试 CTestDemo/

1. CTest是CMake集成测试框架,用于自动化执行项目测试,支持多种测试类型,并能生成测试报告

2. include(CTest) 加载CTest模块,启用CTest功能(顶级CMakeLists.txt)
    - add_test(NAME <test_name> COMMAND <command>) 定义测试,NAME指定测试名称,COMMAND指定测试命令
    - 在顶级构建目录下执行CTest命令,CTest会自动发现并执行所有定义的测试,生成测试报告

## (12) CPack打包 CPackDemo/

1. 使用: 在顶级构建目录下使用CPack命令,CPack会根据自动收集CMake install命令需要打包的文件,生成指定格式的安装包,并将安装包放在构建目录下

2. 所以使用CPack前需要写好install命令,指定需要安装的文件和安装路径,CPack会根据这些信息生成安装包

# 四. CMake语法 CMakeLanguage/

1. message函数:
    - message(<message_type> "message content") 输出消息,其中<message_type>可以是以下几种类型:
        - STATUS: 普通信息,默认类型
        - WARNING: 警告信息
        - ERROR: 错误信息,会导致配置失败,不会停止生成,不生成makefile
        - FATAL_ERROR: 致命错误,会立即终止配置过程,停止生成,不会生成makefile

2. 普通变量: CMake中的变量是字符串类型,保存一些值,可以在CMakeLists.txt中定义和使用变量,变量名通常使用大写字母和下划线分隔,例如: MY_VARIABLE(区分大小写)
    - set(<variable_name> <value>) 定义变量,例如: set(MY_VARIABLE "Hello World")
    - ${<variable_name>} 使用变量,例如: message(STATUS "The value of MY_VARIABLE is ${MY_VARIABLE}")
    - unset(<variable_name>) 删除变量,例如: unset(MY_VARIABLE)
    - 作用域:
        - Function scope: 在函数内部定义的变量仅在函数内部可见,函数外部无法访问(局部变量)
        - Directory scope: 在A/CMakeLists.txt中定义的变量在A/CMakeLists.txt及其子目录的CMakeLists.txt中可见,但在父目录的CMakeLists.txt中不可见(目录变量)
        - Persistent scope: 在顶级CMakeCache.txt中定义的变量在整个构建过程中都可见,可以在不同的CMakeLists.txt中访问(缓存变量 set(xxx CACHE <type> <docstring>))
    - 计算变量值: 首先在当前作用域查找变量,如果没有找到,则在父作用域中查找,直到顶级作用域,CMakeCache,如果仍然没有找到,则返回空字符串。
    - 使用${<variable_name>}访问变量时,会触发变量的计算过程,根据上述规则查找变量的值并返回。
    - if(${<variable_name>})==if(<variable_name>)$可以省略
    - 子目录定义的同名变量不会影响到父目录,父目录也拿不到子目录定义的变量(内存隔离)

3. 缓存变量:解决的是信息在多次cmake调用之间,以及在整个源码树各目录之间如何共享并持久化的问题
    - 全局,持久,可由用户交互修改
    - 第二次设置需要带force参数,第一次设置不需要,否则不会修改CMakeCache.txt中的值
    - 也可以使用cmake -D<variable_name>=<value>命令行参数设置缓存变量,例如: cmake -DMY_VARIABLE="Hello World" ../ (命令行优先级比force低)

4. 环境变量: 环境变量是操作系统级的变量,需要通过$ENV{VAR}语法访问
    - 作用域: 全局可见,但需要通过$ENV{VAR}显式引用,只存在CMake进程中,不会被持久化到系统中
    - 生命周期: 取决于操作系统与CMAKE运行会话无关
    - 用于获取系统配置

5. CMake if语句:
    - 1,ON,YES,TRUE,Y,非0数字或浮点数表示真;0,OFF,NO,FALSE,N,IGNORE,NOTFOUND,空字符串,以后缀-NOTFOUND结尾的字符串表示假(常量)
    - 变量的值不为上条假的即真,环境变量的值总为假,不能用if判断(变量类型)
    - 带引号的字符串除了真常量构成的字符串外,其余都是假(字符串类型)
    - if语句与endif成对使用
    - if对于CMAKE普通变量会自动求值,if(var)==if(${var}),if对于环境变量与缓存变量不会自动求值,需要使用$ENV{VAR}语法访问值,例如: if($ENV{MY_ENV_VAR})

6. CMake foreach语句:
    - 使用break(),continue()控制循环流程,使用endforeach()结束循环
    - 多个字符串空格分隔彼此
    - foreach ITEM 后面是字面值,直接作为元素,不当变量解析
    - foreach LISTS 后面是变量名,变量值按照;分隔成列表,每个元素当变量解析

7. CMake while语句:
    - 使用break(),continue()控制循环流程,使用endwhile()结束循环

8. CMake LIST 函数:
    - list是CMake中一组由分号分隔的值