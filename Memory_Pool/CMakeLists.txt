cmake_minimum_required(VERSION 3.6)  # 指定CMake的最低版本要求

project(MyProject)  # 设置项目名称

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)

# 添加可执行文件
add_executable(MyExecutable main.cpp)

# 添加其他源文件
# add_library(MyLibrary mylibrary.cpp)

# 设置编译选项
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 添加链接库
# target_link_libraries(MyExecutable MyLibrary)