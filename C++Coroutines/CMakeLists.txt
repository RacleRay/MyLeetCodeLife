cmake_minimum_required(VERSION 3.18)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++2a -stdlib=libc++")

project(main LANGUAGES CXX)

add_executable(co_await_example ./co_await_example.cpp)

target_compile_options(co_await_example PRIVATE -fcoroutines-ts)