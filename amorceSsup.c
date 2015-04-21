#include "strategie_sup.h"
#include <time.h>

int main(int argc, char** argv){
  int depth=4;
  srand(time(NULL));
  gridP *e = malloc(sizeof(gridP));
  grid g=new_grid();
  e->grille=g;
  e->nbFT=GRID_SIDE*GRID_SIDE-2;
  while(!game_over(g)){
    retour* r=best(e,depth);
    e->nbFT+=nbfuses(g,r->direction)-1;
    do_move(g,r->direction);
    free(r);
    add_tile(g);
  show_grid(g);
  printf("%ld\n",grid_score(g));}
  delete_grid(g);
  return 0;}
