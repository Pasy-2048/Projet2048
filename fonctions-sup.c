#include "fonctions-sup.h"
#include "grid.h"
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

//------------------------------------------------------------------------------
// param: grid : grille
// Return:  rien
// Purpose: Fonction affichant la grille
// realisation : Alexis Richard
//------------------------------------------------------------------------------

void show_grid(grid g)
{
    int i,j;
    for(i=0;i<GRID_SIDE;i++)
        {
            printf("_______");
        }
        printf("\n");
    for(j=0;j<GRID_SIDE;j++)
	{
		printf("|");
		for(i=0;i<GRID_SIDE;i++)
		{
			printf("      |");
		}
		printf("\n|");
		for(i=0;i<GRID_SIDE;i++)
		{
			printf("%6u|",valeur(2,get_tile(g,i,j)));
		}
		printf("\n|");
		for(i=0;i<GRID_SIDE;i++)
		{
			printf("      |");
		}
		printf("\n");
		for(i=0;i<GRID_SIDE;i++)
		{
			printf("_______");
		}
		printf("\n\n");
	}
    //printf("Free tiles: %d. Score: %lu\n",get_free_tiles(g),grid_score(g));
}

//------------------------------------------------------------------------------
// param: a :	2 par défaut. La valeur à exposer, en quelque sorte.
// param: b : 	L'exposant (en fait le niveau de la case; valeur(2,0) != 2^0).
// Return:  rien
// Purpose: Fonction qui fournis à show_grid(...) la valeur à afficher
// selon le 'niveau' de la case.
// realisation : Alexis Richard
//------------------------------------------------------------------------------

unsigned int valeur(int a, unsigned int b)
{
    if(b==0)
    {
        return 0;
    }
    if(b==1)
	{
		return a;
	}
    if(b%2==0)
	{
		return valeur(a*a,b/2);
	}
    return a*valeur(a,b-1);
}

