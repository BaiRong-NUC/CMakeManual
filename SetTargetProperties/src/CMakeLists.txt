add_library(add SHARED add.cpp)

# 设置属性
set_target_properties(add PROPERTIES
    # 1. 编译类参数
    COMPILE_OPTIONS "-g"
    COMPILE_OPTIONS "-O3"
    COMPILE_OPTIONS "-fPIC"
    INCLUDE_DIRECTORIES "/public"
    INTERFACE_INCLUDE_DIRECTORIES "/interface"
    # 2. 链接类参数
    LINK_DIRECTORIES "/public"
    INTERFACE_LINK_DIRECTORIES "/interface"
    LINK_LIBRARIES "pthread" # 构建自己
    INTERFACE_LINK_LIBRARIES "jsoncpp" # 构建main时依赖
    # 3. 输出类参数
    RUNTILE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" # 二进制文件输出目录
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" # 静态库文件输出目录
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" # 共享库文件输出目录
    # 4. 安装类参数
    BUILD_RPATH "${CMAKE_BINARY_DIR}/lib" # 运行时库搜索路径列表
    INSTALL_RPATH "lib" # /usr/local/lib
    OUTPUT_NAME "add" # 动态库名称
    VERSION 1.0.0 # 动态库版本号
    SOVERSION "20"
)