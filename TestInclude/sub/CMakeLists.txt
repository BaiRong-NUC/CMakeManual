message("From sub/CMakeLists.txt")
# 打印当前CMakeLists.txt所在目录(源代码目录)
message("Current source directory: ${CMAKE_CURRENT_SOURCE_DIR}")

# 打印当前正在执行的cmake脚本完整名称
message("Current CMake script: ${CMAKE_CURRENT_LIST_FILE}")

# 打印当前正在执行cmake脚本的全目录
message("Current CMake script directory: ${CMAKE_CURRENT_LIST_DIR}")