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

# 5. CMake if语句

# 常量真
if("ON")
    message(STATUS "ON is true")
else()
    message(STATUS "ON is false")
endif()

# 常量假
if("abc")
    message(STATUS "abc is true")
else()
    message(STATUS "abc is false")
endif()

# 变量
set(VAR "NOTFOUND")
if(VAR)
    message(STATUS "VAR is true")
else()
    message(STATUS "VAR is false")
endif()

set(VAR "ON")
if(${VAR})
    message(STATUS "Modify VAR is true")
else()
    message(STATUS "Modify VAR is false")
endif()

# 环境变量(始终为假)
if(ENV{PATH})
    message(STATUS "Environment variable PATH is true")
else()
    message(STATUS "Environment variable PATH is false")
endif()

# 逻辑运算
if(NOT "ON")
    message(STATUS "NOT ON is true")
else()
    message(STATUS "NOT ON is false")
endif()

if("ON" AND "abc")
    message(STATUS "ON AND abc is true")
else()
    message(STATUS "ON AND abc is false")
endif()

if("ON" OR "abc")
    message(STATUS "ON OR abc is true")
else()
    message(STATUS "ON OR abc is false")
endif()

# 存在性检测
if(COMMAND project)
    message(STATUS "Command project exists")
else()
    message(STATUS "Command project does not exist")
endif()

add_library(MyMath INTERFACE) # 定义一个接口库MyMath,该库不包含任何源文件,仅用于提供接口和属性
if(TARGET MyMath)
    message(STATUS "Target MyMath exists")
else()
    message(STATUS "Target MyMath does not exist")
endif()

# 变量是否定义
if(DEFINED VAR)
    message(STATUS "Variable VAR is defined")
else()
    message(STATUS "Variable VAR is not defined")
endif()

# set(AGE "18" CACHE STRING "Age") # 定义一个全局变量AGE,并将其保存到CMake缓存中,使得在整个CMakeLists.txt文件中都能访问到该变量
if(DEFINED AGE)
    message(STATUS "Variable AGE is defined")
else()
    message(STATUS "Variable AGE is not defined")
endif()

if(DEFINED ENV{PATH})
    message(STATUS "Environment variable PATH is defined")
else()
    message(STATUS "Environment variable PATH is not defined")
endif()

# 文件是否存在
if(EXISTS ${CMAKE_CURRENT_LIST_FILE})
    message(STATUS "Current CMakeLists.txt file exists")
else()
    message(STATUS "Current CMakeLists.txt file does not exist")
endif()

# 相对路径取决于源外还是源内构建,不推荐使用
# if(EXISTS "./CMakeCache.txt")
#     message(STATUS "./CMakeCache.txt file exists")
# else()
#     message(STATUS "./CMakeCache.txt file does not exist")
# endif()

if(EXISTS "${CMAKE_BINARY_DIR}/CMakeCache.txt")
    message(STATUS "CMakeCache.txt file exists")
else()
    message(STATUS "CMakeCache.txt file does not exist")
endif()

# 比较
if(AGE GREATER 18)
    message(STATUS "AGE is greater than 18")
else()
    message(STATUS "AGE is not greater than 18")
endif()

if("abc" STRLESS "abd")
    message(STATUS "abc is less than abd")
else()
    message(STATUS "abc is not less than abd")
endif()

if("30" LESS "20")
    message(STATUS "30 is less than 20")
else()
    message(STATUS "30 is not less than 20")
endif()

# 版本号
if(CMAKE_VERSION VERSION_LESS "3.20")
    message(STATUS "CMake version is less than 3.20")
else()
    message(STATUS "CMake version is greater than or equal to 3.20")
endif()

# 6. CMake foreach循环
foreach(ELEMENT "A" "B" "C") # 遍历列表变量LIST中的每个元素,将当前元素赋值给变量ELEMENT
    message(STATUS "Current element: ${ELEMENT}") # 打印当前元素的值
endforeach()

set(LIST "1;2;3")
foreach(ELEMENT ${LIST})
    message(STATUS "Current element: ${ELEMENT}")
endforeach()

foreach(ELEMENT RANGE 1 5 2)
    message(STATUS "Current element: ${ELEMENT}")
endforeach()

foreach(ELEMENT IN LISTS LIST)
    message(STATUS "Current element: ${ELEMENT}")
endforeach()

foreach(ELEMENT IN ITEMS "A;B;C")
    message(STATUS "Current element: ${ELEMENT}")
endforeach()

# 7. CMake while循环
set(COUNTER 1)
while(COUNTER LESS_EQUAL 5)
    message(STATUS "Counter: ${COUNTER}")
    math(EXPR COUNTER "${COUNTER} + 1") # 使用math函数对变量进行算术运算,将COUNTER的值加1
endwhile()