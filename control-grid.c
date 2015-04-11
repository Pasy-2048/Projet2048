#include "grid.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "fonctions-sup.h"

// Fichier terminé.
// Usage: Lance un 2048 dans le repertoire, controllable par U(p),D(own),L(eft),R(ight) et S(top).
// À l'envoi de S(top), le programme joue automatiquement la grille jusqu'au game over
// selon un algorithme simple (mort rapide), puis s'arrête.

int main()
{
    srand(time(NULL));
    grid g=new_grid();
    bool continuer=1;
    char ordre[2];
    show_grid(g);
    while(!game_over(g) && continuer==1){
      fgets(ordre, 2, stdin);
      switch(ordre[0]){
      case 'L':
      case 'l':
         play(g,LEFT);
         break;
      case 'R':
      case 'r':
         play(g,RIGHT);
         break;
      case 'U':
      case 'u':
         play(g,UP);
         break;
      case 'D':
      case 'd':
         play(g,DOWN);
         break;
      case 'S':
      case 's':
         continuer=0;
         break;
      }
    }
    while(!game_over(g)){
        if(can_move(g,RIGHT)){
            play(g,RIGHT);
        }
	else if(can_move(g,UP)){
            play(g,UP);
        }
	else if(can_move(g,DOWN)){
            play(g,DOWN);
        }
	else{
            play(g,LEFT);
        }
    }
    delete_grid(g);
    return 0;
}
