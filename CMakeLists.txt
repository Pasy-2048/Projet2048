cmake_minimum_required(VERSION 2.6)

project ("2048")

set(CMAKE_C_FLAGS "-std=c99 -g -Wall -Werror")



add_executable(2048 control-grid.c grid.c fonctions-sup.c)

add_executable(testFct test/test.c grid.c fonctions-sup.c)




