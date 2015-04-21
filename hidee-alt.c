#include "fonctions-sup.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// Algorithme de résolution rapide sans affichage.
// Score autour de 4k.
// Termine en .1 secondes en moyenne.
// Un algorithme plus complexe est à préparer.
// Avec gestion des heuristiques de préférence.
int main(void){srand(time(NULL));grid g=new_grid();
  bool hE=0;int i,j;i=availMoves(g);
  while(!game_over(g)){j=i%4;
    if(j!=0){if(hE==0){if(j%2==1){do_turn(g,LEFT);hE=1;}
	else{do_turn(g,RIGHT);}}
      else{if(j>=2){do_turn(g,RIGHT);hE=0;}
	else{do_turn(g,LEFT);}}}
    i=availMoves(g);j=i/4;
    if(j!=0){if(j>=2){do_turn(g,UP);}
      else if(i==4){do_turn(g,DOWN);}}}
	  play(g,UP);
	show_grid(g);
printf("%ld\n",grid_score(g));
  delete_grid(g);return 0;}
