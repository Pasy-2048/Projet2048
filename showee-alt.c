#include "fonctions-sup.h"
// Algorithme de résolution rapide avec affichage.
// Radical identique à celui de hidee-alt.c.
int main(void){srand(time(NULL));grid g=new_grid();
  show_grid(g);bool hE=0;int i,j;i=availMoves(g);
  while(!game_over(g)){j=i%4;
    if(j!=0){if(hE==0){if(j%2==1){do_turn(g,LEFT);hE=1;}
	else{do_turn(g,RIGHT);}}
      else{if(j>=2){do_turn(g,RIGHT);hE=0;}
	else{do_turn(g,LEFT);}}
      show_grid(g);}
    i=availMoves(g);j=i/4;
    if(j!=0){if(j>=2){do_turn(g,UP);show_grid(g);}
      else if(i==4){do_turn(g,DOWN);}}}
  show_grid(g);delete_grid(g);return 0;}
