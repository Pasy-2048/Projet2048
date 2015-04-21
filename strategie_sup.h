#include "grid.h"
#include "fonctions-sup.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {dir direction;long unsigned int hMax;} retour;

typedef struct {grid grille;int nbFT;} gridP;

int nbfuses(grid g, dir d);

int sumfuses(grid g);

retour* maxfuses(grid g);

long unsigned int krakat(grid g);

long unsigned int heuristique(gridP *e);

retour* best(gridP *e,int depth);

int min(int a, int b);
