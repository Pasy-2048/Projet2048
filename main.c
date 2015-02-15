#include "grid.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void show_grid(grid g);
unsigned int valeur(int a, unsigned int b);

int main()
{
    srand(time(NULL));
    grid g=new_grid();
    add_tile(g);
    add_tile(g);
    play(g,LEFT);
    /*
    bool continuer=1;
    char ordre[11];
    while(!game_over(g)&&continuer==1){
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
    }*/
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
