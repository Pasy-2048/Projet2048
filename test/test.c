#include "../grid.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "../fonctions-sup.h"

int main()
{
    srand(time(NULL));
    grid g=new_grid();
    bool continuer=1;
    char ordre;
    printf("Entrez L,R,U,D pour controler\n");
    printf("Entrez S pour terminer automatiquement le jeu\n");
    while(!game_over(g) && continuer==1){
      
      ordre = fgetc(stdin);


    // test de la fonction can_move
    if(can_move(g,RIGHT))
      printf("can_move:test RIGHT--------OK\n");
    else
      printf("can_move:test RIGHT--------NOK\n");

    if(can_move(g,LEFT))
      printf("can_move:test LEFT--------OK\n");
    else
      printf("can_move:test LEFT--------NOK\n");
    
    if(can_move(g,UP))
      printf("can_move:test UP--------OK\n");
    else
      printf("can_move:test UP--------NOK\n");
    
    if(can_move(g,DOWN))
      printf("can_move:test DOWN--------OK\n");
    else
      printf("can_move:test DOWN--------NOK\n");
        
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