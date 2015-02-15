#ifndef GRAPHICAL_GRID_H_
#define GRAPHICAL_GRID_H_
#include "grid.h"
#include <SDL.h>

typedef struct gGrid_s *gGrid;

typedef struct piece_s *piece;

void show_grid_SDL(gGrid g, SDL_Surface* ecran);

SDL_Surface *get_piece_surf(gGrid g,int x,int y);

SDL_Rect* get_piece_pos(gGrid g,int x,int y);



#endif
