#ifndef FUNC_SUP_H_
#define FUNC_SUP_H_
#include "grid.h"
// c.f. fonctions-sup.c.

int availMoves(grid g);

void do_turn(grid g,dir d);

void show_grid(grid g);

unsigned int valeur(int a, unsigned int b);

#endif
