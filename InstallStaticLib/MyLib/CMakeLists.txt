# 1. 收集源代码
file(GLOB SRC_FILES "src/*.cpp") # 定义一个变量SRC_FILES,包含src目录下的所有cpp文件路径

# 2. 添加构建目标
add_library(MyMath STATIC ${SRC_FILES}) # 定义一个静态库目标MyMath,包含SRC_FILES变量中指定的源文件

# 3. 设置CMake使用该库时应从此路径查找头文件
target_include_directories(MyMath PUBLIC
    "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>" # /usr/local/include
)

# 4. 修改默认输出路径为最顶层构建目录下的lib目录
set_target_properties(MyMath PROPERTIES 
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# 5. 安装静态库
include(GNUInstallDirs)
install(TARGETS MyMath
    EXPORT MyMathTargets # 导出集合
    DESTINATION ${CMAKE_INSTALL_LIBDIR} # 安装库文件到/usr/local/lib
)

# 6. 安装头文件
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/math # 安装头文件到/usr/local/include/math
    FILES_MATCHING PATTERN "*.h" # 只安装.h文件
)

# 7. 安装导出目标集合到构建树
export(EXPORT MyMathTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/MyMathTargets.cmake" # 导出构建路径下的MyMathTargets.cmake文件
    NAMESPACE MyMath:: # 导出集合命名空间
)

# 8. 安装导出目标集合到安装树
install(EXPORT MyMathTargets
    FILE MyMathTargets.cmake # 安装MyMathTargets.cmake文件到安装树
    NAMESPACE MyMath:: # 安装集合命名空间 MyMath::MyMath(TargetName)
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyMath # 安装路径/usr/local/lib/cmake/MyMath
)

# 9. 生成MyMathConfig.cmake文件,定义如何使用MyMath库,CMake在find_package(MyMath)时找到配置文件
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/MyMathConfig.cmake.in # 模板文件路径
    ${CMAKE_CURRENT_BINARY_DIR}/MyMathConfig.cmake # 生成文件路径
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyMath # MyMathConfig.cmake安装路径
)

# 10. 安装MyMathConfig.cmake文件到标准路径
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MyMathConfig.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MyMath # 安装路径/usr/local/lib/cmake/MyMath
)