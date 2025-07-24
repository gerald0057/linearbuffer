cmake_minimum_required(VERSION 3.10)

project(linearbuffer_test)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(linearbuffer REQUIRED)

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(run_unit_tests
        main.cpp
        tc.cpp
)
target_link_libraries(run_unit_tests PRIVATE
    gtest
    linearbuffer::linearbuffer
)
add_test(NAME linearbuffer_test COMMAND run_unit_tests)