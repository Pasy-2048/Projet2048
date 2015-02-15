#include "fonctions-sup.h"
// Juste quelques fonctions additionelles.
// Toutes sont remplacables.
// Pour si vous voulez vous simplifier la vie pendant les debugs.
int availMoves(grid g){
  return (((can_move(g,LEFT))?1:0)+((can_move(g,RIGHT))?2:0)+((can_move(g,DOWN))?4:0)+((can_move(g,UP))?8:0));}

void do_turn(grid g,dir d){
  do_move(g,d);
  add_tile(g);}
