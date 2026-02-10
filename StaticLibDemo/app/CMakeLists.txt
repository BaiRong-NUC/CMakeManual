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

# 5. 打印计算出静态库的路径
add_custom_command(
    TARGET main POST_BUILD # 在main完成链接后
    COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_FILE:Math>" # 打印Math库的路径,CMAKE_COMMAND是CMake的安装位置
    COMMENT "Math库的路径" # 打印注释
)