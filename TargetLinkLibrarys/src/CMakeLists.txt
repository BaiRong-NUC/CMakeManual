# 生成静态库
add_library(add STATIC add.cpp)

# 头文件包含路径
target_include_directories(add PRIVATE "/usr/local/include/PRIVATE")
target_include_directories(add PUBLIC "/usr/local/include/PUBLIC")
target_include_directories(add INTERFACE "/usr/local/include/INTERFACE")

# 库文件搜索路径
target_link_directories(add PRIVATE "/usr/local/lib/PRIVATE")
target_link_directories(add PUBLIC "/usr/local/lib/PUBLIC")
target_link_directories(add INTERFACE "/usr/local/lib/INTERFACE")

# 依赖库列表
target_link_libraries(add INTERFACE "pthread")