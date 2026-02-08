# 库消费者

#  1. 搜索文件
file(GLOB SRC_FILES "./*.cpp") # 定义一个变量SRC_FILES,包含src目录下的所有cpp文件路径

#  2. 添加构建目标
add_executable(main ${SRC_FILES})

#  3. 添加依赖库列表
# 为main目标添加依赖库Math,PRIVATE表示只有main目标需要链接该库
target_link_libraries(main PRIVATE Math)

#  4. 设置输出目录
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) # 设置main目标的可执行文件输出路径为构建目录下的bin目录