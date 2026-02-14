# 库生产者
# 1. 收集库源代码
file(GLOB SRC_FILES "src/*.cpp") # 定义一个变量SRC_FILES,包含src目录下的所有cpp文件路径

# 2. 添加构建目标
add_library(Math SHARED ${SRC_FILES}) # 定义一个动态库目标Math,包含SRC_FILES变量中指定的源文件

# 3. 设置库的使用要求
# 设置Math库的使用者需要包含include目录,public表示生产者与消费者都需要包含这个目录
target_include_directories(Math PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 4. 修改默认输出路径为最顶层构建目录下的lib目录
# ARCHIVE_OUTPUT_DIRECTORY: 静态库的输出路径,LIBRARY_OUTPUT_DIRECTORY: 共享库的输出路径,RUNTIME_OUTPUT_DIRECTORY: 可执行文件的输出路径
set_target_properties(Math PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# -fpic选项: 生成位置无关代码
target_compile_options(Math PRIVATE "-fPIC") # Math库的编译选项,PRIVATE表示仅对当前目标有效

