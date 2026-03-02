# 库生产者
# 1. 收集库源代码
file(GLOB SRC_FILES "src/*.cpp") # 定义一个变量SRC_FILES,包含src目录下的所有cpp文件路径

# 2. 添加构建目标
add_library(MyMath SHARED ${SRC_FILES}) # 定义一个动态库目标Math,包含SRC_FILES变量中指定的源文件

# 3. 设置库的使用要求
# 设置构建目录与安装目录
target_include_directories(MyMath PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> # 构建时包含当前源目录下的include目录
    $<INSTALL_INTERFACE:include> # 安装时包含安装目录下的include目录
)

# 4. 修改默认输出路径为最顶层构建目录下的lib目录
set_target_properties(MyMath PROPERTIES 
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    OUTPUT_NAME "MyMath"
    VERSION 1.2.3
    SOVERSION 20
    COMPILE_OPTIONS "-fPIC" # 生成位置无关代码
)

# 5. 安装库文件
install(TARGETS MyMath)

# 6. 安装头文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include/math # 安装头文件到安装目录下的include/math
    FILES_MATCHING PATTERN "*.h" # 只安装.h文件
)