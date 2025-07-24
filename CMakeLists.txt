cmake_minimum_required(VERSION 3.10)

project(linearbuffer VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

add_library(linearbuffer STATIC
    src/linearbuffer.c
)

target_include_directories(linearbuffer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:include>
)

install(TARGETS linearbuffer
    EXPORT linearbufferTargets
    DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/inc DESTINATION include/linearbuffer)

install(EXPORT linearbufferTargets
    FILE linearbuffer-config.cmake
    NAMESPACE linearbuffer::
    DESTINATION lib/cmake/linearbuffer
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    linearbuffer-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/linearbuffer-config-version.cmake
    DESTINATION lib/cmake/linearbuffer
)
