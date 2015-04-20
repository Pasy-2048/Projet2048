#ifndef FUNC_SUP_H_
#define FUNC_SUP_H_
#include "grid.h"

// c.f. fonctions-sup.c.

struct grid_s
{
    tile** matrice;
    unsigned long int score;
    int nb_free_tiles;
};

int availMoves(grid g);

void do_turn(grid g,dir d);

void show_grid(grid g);

unsigned int valeur(int a, unsigned int b);

#endif
