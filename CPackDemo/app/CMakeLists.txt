# 库消费者

#  1. 搜索文件
file(GLOB SRC_FILES "./*.cpp") # 定义一个变量SRC_FILES,包含src目录下的所有cpp文件路径

#  2. 添加构建目标
add_executable(main ${SRC_FILES})

#  3. 添加依赖库列表
# 为main目标添加依赖库MyMath,PRIVATE表示只有main目标需要链接该库
target_link_libraries(main PRIVATE MyMath)

#  4. 设置输出目录
set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    INSTALL_RPATH "$ORIGIN/../lib" # 设置运行时库搜索路径为可执行文件所在目录的上一级目录下的lib目录
) # 设置main目标的可执行文件输出路径为构建目录下的bin目录

# 5. 打印计算出静态库的路径
add_custom_command(
    TARGET main POST_BUILD # 在main完成链接后
    COMMAND ${CMAKE_COMMAND} -E echo "$<TARGET_FILE:MyMath>" # 打印MyMath库的路径,CMAKE_COMMAND是CMake的安装位置
    COMMENT "MyMath库的路径" # 打印注释
)

# 6. 安装可执行文件
install(TARGETS main)