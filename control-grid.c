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
    show_grid(g);
    printf("Entrez Z(haut),Q(gauche),S(bas),D(droite) pour controler\n");
    printf("Entrez T pour terminer la partie.\n");

    while(!game_over(g) && continuer==1){
      ordre = fgetc(stdin);
      switch(ordre){
      case 'Q':
      case 'q':
         play(g,LEFT);
         break;
      case 'D':
      case 'd':
         play(g,RIGHT);
         break;
      case 'Z':
      case 'z':
         play(g,UP);
         break;
      case 'S':
      case 's':
         play(g,DOWN);
         break;
      case 'T':
      case 't':
	continuer=0;
	break;
      }
      show_grid(g);
      printf("Score: %lu\n",grid_score(g));
      if(game_over(g))
      {
	printf("Game Over\n");
      }
    }

    delete_grid(g);
    return 0;
}
