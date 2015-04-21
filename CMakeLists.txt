cmake_minimum_required(VERSION 2.6)

project ("2048")

set(CMAKE_C_FLAGS "-std=c99 -g -Wall -Werror")

add_library(grid grid.c fonctions-sup.c)

add_library(A1_baltus_lejeune_richard_martin_slow SHARED grid.c strategy.c)

add_executable(2048 control-grid.c grid.c fonctions-sup.c)

add_executable(2048G grid.c graphical-grid.c fonctions-sup.c)

add_executable(FastStrat hidee-alt.c grid.c fonctions-sup.c)

add_executable(FastStratShow showee-alt.c grid.c fonctions-sup.c)

add_executable(EfficientStrat amorceSsup.c strategie_sup.c grid.c fonctions-sup.c)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL REQUIRED sdl)

PKG_SEARCH_MODULE(SDL_TTF_REQUIRED sdl_ttf)

INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})

INCLUDE_DIRECTORIES(${SDLTTF_INCLUDE_DIR})

TARGET_LINK_LIBRARIES(2048G ${SDL_LIBRARIES} ${SDLTTF_LIBRARY} SDL_ttf)

add_executable(test1 test/test.c grid.c fonctions-sup.c)

add_executable(test2 test/test2.c grid.c fonctions-sup.c)
