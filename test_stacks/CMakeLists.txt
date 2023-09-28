cmake_minimum_required(VERSION 3.26)
project(test_stacks C)

set(CMAKE_C_STANDARD 11)

add_library(
        stacks STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../stacks.c
)
set_target_properties(stacks PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-build-debug/libstacks.a)


add_executable(test_stacks main.c)

target_link_libraries(test_stacks PRIVATE stacks)
target_link_libraries(test_stacks PRIVATE cmocka)