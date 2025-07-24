cmake_minimum_required(VERSION 3.10)

project(linearbuffer_demo)

set(CMAKE_C_STANDARD 11)

find_package(linearbuffer REQUIRED)

add_executable(linearbuffer_demo
    main.c
)

target_link_libraries(linearbuffer_demo PRIVATE
    linearbuffer::linearbuffer
)
