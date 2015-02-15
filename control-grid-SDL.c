#include "graphical-grid.h"

int main(void){
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface* ecran=SDL_SetVideoMode(160,160,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
  atexit(SDL_Quit);
}
