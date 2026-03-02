cmake_minimum_required(VERSION 3.18)

project(CMakeLanguage)

# 1. message函数

message("Begin CMakeLists.txt")

message(STATUS "Hello World")

message(STATUS "1" "2" "3")

# message(FATAL_ERROR "FATAL_ERROR")

message(WARNING "WARNING")

message(STATUS "End")

# 2. CMake变量

set(SCOP "Directory Scop")

function(print_var)
    # 2.1 获取父目录变量
    message(STATUS "1. Func: Parent Scope Variable: ${SCOP}")
    # 2.2 修改变量,将其保存到函数作用域空间
    # set(SCOP "Modified in Function")
    set(SCOP "Modified in Function" PARENT_SCOPE) # 将修改后的变量保存到父目录作用域空间,使得在函数外部也能访问到修改后的值
    message(STATUS "2. Func: Modified Parent Scope Variable: ${SCOP}") 
    # 注意: 使用PARENT_SCOPE修改后本次打印仍然是Directory Scop,因为修改后的值是保存到父目录作用域空间的,而当前函数作用域空间中的变量值没有被修改,仍然是Directory Scop

endfunction(print_var)


print_var()

message(STATUS "3. main: ${SCOP}") # 输出Directory Scop

# 3. 全局变量
# 第一次
# set(OS "Linux" CACHE STRING "Operating System") # 定义一个全局变量OS,并将其保存到CMake缓存中,使得在整个CMakeLists.txt文件中都能访问到该变量
# 第二次带force参数修改变量值
set(OS "Windows" CACHE STRING "Operating System" FORCE)

message(STATUS "OS: ${OS}")
# message(STATUS "OS: $CACHE{OS}") # 指定从CMakeCache.txt文件中获取变量值,与直接使用${OS}效果相同

# 4. 环境变量
message(STATUS "PATH: $ENV{PATH}") # 获取环境变量PATH的值,并打印输出
message(STATUS "OS: $ENV{OS}") # 获取环境变量OS的值,并打印输出
set(ENV{OS} "Linux") # 环境变量OS的值随CMake进程结束后消失
message(STATUS "OS: $ENV{OS}") 
message(STATUS "OS: ${OS}") # 获取环境变量OS的值,并打印输出