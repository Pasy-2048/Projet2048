#include "graphical-grid.h"
// grid.c, mais pour une utilisation par la SDL.
// Ultimement, elles devraient faire appel aux fonctions de grid.h.
// À travailler.
struct piece_s{
  tile tIle;
  SDL_Surface* sUrface;
  SDL_Rect* position;};

struct gGrid_s{
  piece** matrice;
  unsigned long int score;
  int nb_free_tiles;};

void show_grid_SDL(gGrid g, SDL_Surface* ecran){
  SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,0,0,0));
  int i,j;
  for(i=0;i<GRID_SIDE;i++){
    for(j=0;j<GRID_SIDE;j++){
      SDL_BlitSurface(get_piece_surf(g,i,j),NULL,ecran,get_piece_pos(g,i,j));
    }
  }
  SDL_Flip(ecran);
}
