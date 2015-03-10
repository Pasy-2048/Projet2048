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
    char ordre;
    printf("Entrez L,R,U,D pour contrôler\n");
    printf("Entrez S pour terminer automatiquement le jeu\n");
    while(!game_over(g) && continuer==1){
      
      ordre = fgetc(stdin);
        
      switch(ordre){
      case 'l':
      case 'L':
         play(g,LEFT);
         break;
      case 'r':
      case 'R':
         play(g,RIGHT);
         break;
      case 'u':
      case 'U':
         play(g,UP);
         break;
      case 'd':
      case 'D':
         play(g,DOWN);
         break;
      case 's':
      case 'S':
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
    show_grid(g);
    delete_grid(g);
    return 0;
}
