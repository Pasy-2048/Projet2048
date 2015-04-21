#include "fonctions-sup.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Algorithme de résolution rapide avec affichage.
// Radical identique à celui de hidee-alt.c.
int main(void){
  srand(time(NULL));
  grid g=new_grid();
  bool hE=0;
  int i,j;
  i=availMoves(g);
  while(!game_over(g)){
	show_grid(g);
	j=i%4;
    if(j!=0){if(hE==0){if(j%2==1){play(g,LEFT);hE=1;}
	else{play(g,RIGHT);}}
      else{if(j>=2){play(g,RIGHT);hE=0;}
	else{play(g,LEFT);}}}
    i=availMoves(g);j=i/4;
    if(j!=0){if(j>=2){play(g,UP);}
      else if(i==4){play(g,DOWN);}}}
	show_grid(g);
printf("%ld\n",grid_score(g));
	  delete_grid(g);return 0;}
