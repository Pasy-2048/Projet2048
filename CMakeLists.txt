cmake_minimum_required(VERSION 2.6)

project ("2048")

set(CMAKE_C_FLAGS "-std=c99 -g -Wall -Werror")

add_library(grid grid.c fonctions-sup.c)

add_executable(2048 control-grid.c grid)

add_executable(testFct1 test/test.c grid)

add_executable(testFct2 test/test2.c grid)

target_link_libraries(2048 grid)

target_link_libraries(testFct1 grid)

target_link_libraries(testFct2 grid)



