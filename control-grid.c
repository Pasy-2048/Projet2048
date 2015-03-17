#include "grid.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
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
    printf("Entrez Z(haut),Q(gauche),S(bas),D(droite) pour controler\n");
    printf("Entrez T pour terminer automatiquement le jeu\n");
    while(!game_over(g) && continuer==1){
      
      ordre = fgetc(stdin);
        
      switch(ordre){
      case 'q':
      case 'Q':
         play(g,LEFT);
         break;
      case 'd':
      case 'D':
         play(g,RIGHT);
         break;
      case 'z':
      case 'Z':
         play(g,UP);
         break;
      case 's':
      case 'S':
         play(g,DOWN);
         break;
      case 't':
      case 'T':
         continuer=0;
         break;
      }
    }
    bool hE=0;
    int i,j;
    i=availMoves(g);
    while(!game_over(g)){
    j=i%4;
      if(j!=0){if(hE==0){if(j%2==1){play(g,LEFT);hE=1;}
    else{play(g,RIGHT);}}
        else{if(j>=2){play(g,RIGHT);hE=0;}
    else{play(g,LEFT);}}}
      i=availMoves(g);j=i/4;
      if(j!=0){if(j>=2){play(g,UP);}
        else if(i==4){play(g,DOWN);}}}
    show_grid(g);
    delete_grid(g);
    return 0;
}
