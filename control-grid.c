#include "grid.h"
// Fichier terminé.
// Usage: Lance un 2048 dans le repertoire, controllable par U(p),D(own),L(eft),R(ight) et S(top).
// À l'envoi de S(top), le programme joue automatiquement la grille jusqu'au game over
// selon un algorithme simple (mort rapide), puis s'arrête.
int main()
{
    srand(time(NULL));
    grid g=new_grid();
    bool continuer=1;
    char ordre[11];
    while(!game_over(g)&&continuer==1){
      show_grid(g);
        fgets(ordre,10,stdin);
        switch(ordre[0]){
        case 'L':
            play(g,LEFT);
            break;
        case 'R':
            play(g,RIGHT);
            break;
        case 'U':
            play(g,UP);
            break;
        case 'D':
            play(g,DOWN);
            break;
        case 'S':
            continuer=0;
            break;
        }
    }
    while(!game_over(g)){
        if(can_move(g,RIGHT)){
            play(g,RIGHT);
        }else if(can_move(g,UP)){
            play(g,UP);
        }else if(can_move(g,DOWN)){
            play(g,DOWN);
        }else{
            play(g,LEFT);
        }
    }
    show_grid(g);
    delete_grid(g);
    return 0;
}
