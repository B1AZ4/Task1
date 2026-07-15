cmake_minimum_required(VERSION 4.0)
project(Test1 VERSION 1.0.0)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(BLOCK_SIZE 1024 CACHE STRING "Block size for file operations (N bytes)")


set(LIB_SOURCES
    lib/src/buffer.c
    lib/src/processor.c
    lib/src/cli_parser.c
)

add_library(replace_lib STATIC ${LIB_SOURCES})
target_compile_definitions(replace_lib PRIVATE BLOCK_SIZE=${BLOCK_SIZE})
target_include_directories(replace_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

if(BUILD_SHARED_LIBS)
    add_library(replace_lib_shared SHARED ${LIB_SOURCES})
    target_compile_definitions(replace_lib_shared PRIVATE BLOCK_SIZE=${BLOCK_SIZE})
    target_include_directories(replace_lib_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
endif()

add_executable(replace_app app/src/main.c)

if(BUILD_SHARED_LIBS)
    target_link_libraries(replace_app replace_lib_shared)
else()
    target_link_libraries(replace_app replace_lib)
endif()

target_include_directories(replace_app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib)
