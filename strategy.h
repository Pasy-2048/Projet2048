#ifndef STRATEGY_H_
#define STRATEGY_H_
#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct strategy_s* strategy;

struct strategy_s{
  void* mem;
  char* name;
  dir (*play_move) (strategy, grid);
  void (*free_strategy) (strategy);
};

int availMoves(grid g);

void free_memless_strat (strategy strat);

void do_turn(grid g,dir d);

void show_grid(grid g);

unsigned int valeur(int a, unsigned int b);

typedef struct {dir direction;long unsigned int hMax;} retour;

typedef struct {grid grille;int nbFT;} gridP;

int nbfuses(grid g, dir d);

int sumfuses(grid g);

retour* maxfuses(grid g);

long unsigned int krakat(grid g);

long unsigned int heuristique(gridP e);

retour* best(gridP e,int depth);

dir play_move(strategy s, grid g);

int min(int a, int b);
#endif