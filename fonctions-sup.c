#include "fonctions-sup.h"
#include <stdio.h>
#include <stdlib.h>
// En fait ce fichier va prendre toutes les fonctions pas présentes dans grid.h (sauf les natives au module)
// Un fois inclus dans grid.c, ça auras le même résultat.
// Pensez à mettre fonctions-sup.c en source pendant la compilation tho.
int availMoves(grid g){
	return (((can_move(g,LEFT))?1:0)+((can_move(g,RIGHT))?2:0)+((can_move(g,DOWN))?4:0)+((can_move(g,UP))?8:0));}

void do_turn(grid g,dir d){
	do_move(g,d);
	add_tile(g);
}

