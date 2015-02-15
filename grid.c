/******************************************************************************/
/*                               Groupe :                                     */
/*     Yannis Baltus - Simon Lejeune - Alexis Richard - Pierre Louis           */
/******************************************************************************/


#include "grid.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

int get_free_tiles (grid g);
void set_free_tiles (grid g, int x);
void show_grid(grid g);
unsigned int valeur(int a, unsigned int b);
void set_score (grid g, unsigned long int score);

struct grid_s
{
    tile** matrice;
    unsigned long int score;
    int nb_free_tiles;
};

/******************************************************************************/
/*                                Constructeurs                               */
/******************************************************************************/

//------------------------------------------------------------------------------
// param:  rien
// Return:  Gird : grille
// Purpose: Fonction qui construit une nouvelle grille
// realisation : Yannis Baltus
//------------------------------------------------------------------------------
grid new_grid ()
{
    grid g=malloc(sizeof(struct grid_s));
    set_score(g,0);
    set_free_tiles(g,GRID_SIDE*GRID_SIDE);
    g->matrice=(tile**)malloc(GRID_SIDE*sizeof(tile*));
    int i; int j;
    for(i=0;i<GRID_SIDE;i++)
    {
        g->matrice[i]=(tile*)malloc(GRID_SIDE*sizeof(tile));
        for(j=0;j<GRID_SIDE;j++)
            {
                set_tile(g,i,j,0);
            }
        }
    //add_tile(g);add_tile(g);
    return g;
}

/******************************************************************************/
/*                                 destructeur                                */
/******************************************************************************/

//------------------------------------------------------------------------------
// param: grid : grille
// Return:  rien
// Purpose: Fonction qui libère la mémoire d'une grille
// realisation : Simon Lejeune
//------------------------------------------------------------------------------
void delete_grid (grid g)
{
    int i;
    for(i=0;i<GRID_SIDE;i++)
    {
        free(g->matrice[i]);
    }
    free(g->matrice);
    free(g);
}

/******************************************************************************/
/*                                 Copie                                      */
/******************************************************************************/


//------------------------------------------------------------------------------
// param: grid : grille source
// param: grid : grille destination
// Return:  rien
// Purpose: Fonction qui copie une grille
// realisation : Simon Lejeune
//------------------------------------------------------------------------------
void copy_grid (grid src, grid dst)
{
    int i,j;
    for(i=0;i<GRID_SIDE;i++)
        {
            for(j=0;j<GRID_SIDE;j++)
            {
                set_tile(dst,i,j,get_tile(src,i,j));
            }
        }
    set_free_tiles(dst,get_free_tiles(src));
    set_score(dst,grid_score(src));
}

/******************************************************************************/
/*                              Accesseurs                                    */
/*  realisation : Simon Lejeune, Yannis Baltus, Pierre Louis, Alexis Richard  */
/******************************************************************************/

void set_score (grid g, unsigned long int score)
{
    g->score=score;
}

tile get_tile (grid g, int x, int y)
{
    return g->matrice[x][y];
}

void set_tile (grid g, int x, int y, tile t)
{
    g->matrice[x][y]=t;
}

// permet de savoir combien tuile vide il y a
int get_free_tiles (grid g)
{
    return g->nb_free_tiles;
}

// permet de mettre une nouvelle valeur dans une tuile vide
void set_free_tiles (grid g, int x)
{
    g->nb_free_tiles=x;
}

/******************************************************************************/
/*                               Fonctions                                    */
/******************************************************************************/


//------------------------------------------------------------------------------
// param: grid : grille
// Return:  unsigned long int : score
// Purpose: Fonction qui permet d'avoir le score de la partie
// realisation : Yannis Baltus
//------------------------------------------------------------------------------
unsigned long int grid_score (grid g)
{
    return g->score;
}


//------------------------------------------------------------------------------
// param: grid : grille
// param: dir : direction
// Return:  un booleen 
// Purpose: Fonction qui permet de savoir si on peut bouger vers une direction
// realisation : Pierre Louis, Alexis Richard
//------------------------------------------------------------------------------
bool can_move (grid g, dir d)
{
    int i,j,k;
    /*if(d==NOP)
        {
            return false;
        }*/
    bool loni=((d==LEFT||d==RIGHT)?1:0),sup=((d==RIGHT||d==DOWN)?1:0);
    tile Tj,Tk;
    for(i=0;i<GRID_SIDE;i++)
    {
        for(j=(GRID_SIDE-1)*(1-sup);j*(2*sup-1)<(GRID_SIDE-1)*sup;j+=(2*sup-1))
        {
            Tj=get_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni));
            if(Tj!=0)
            {
                k=j+2*sup-1;
                Tk=get_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni));
                if(Tk==0||Tk==Tj)
                    {
                        return true;
                    }
            }
        }
    }
    return false;
}

//------------------------------------------------------------------------------
// param: grid : grille
// Return:  rien
// Purpose: Fonction qui permet de savoir si la partie est fini
// realisation : Simon Lejeune, Yannis Baltus
//------------------------------------------------------------------------------

bool game_over (grid g)
{
    // si il y a encore des tuiles vide ce n'est pas "game over"
    if(get_free_tiles(g)!=0)
        {
            return false;
        }
    int i,j,k;
    for(i=0;i<GRID_SIDE;i++)
    {
        for(j=0;j<GRID_SIDE;j++)
        {
            for(k=((j!=GRID_SIDE-1)?0:1);k<=((i!=GRID_SIDE-1)?1:0);k++)
            {
                //printf("i:%d j:%d k:%d\n",i,j,k);
                if(get_tile(g,i+k,j+1-k)==get_tile(g,i,j))
                {
                    return false;
                }
            }
        }
    }
    return true;
}


//------------------------------------------------------------------------------
// param: grid : source
// param: dir : direction
// Return:  rien
// Purpose: Fonction qui execute les mouvements dans une direction.
// realisation : Alexis Richard Pierre Louis
//------------------------------------------------------------------------------
void do_move (grid g, dir d)
{
    /*if(d==NOP)
        {
            return;
        }*/
    bool loni=((d==LEFT||d==RIGHT)?1:0),sup=((d==RIGHT||d==DOWN)?1:0),continuer;
    tile Tj,Tk;
    int i,j,k,jmax=(GRID_SIDE-1)*(1-sup),kmax=jmax-(2*sup)+1;
    //printf("jmax:%d kmax:%d\n",jmax,kmax);
    for(i=0;i<GRID_SIDE;i++)
    {
        continuer=1;
        j=(GRID_SIDE-1)*sup;
        //printf("i:%d\n",i);
        while(continuer==1&&j*(1-2*sup)<jmax)
        {
            Tj=get_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni));
            //printf("j:%d Tj:%u\n",j,Tj);
            k=j;
            if(Tj==0)
            {
                continuer=0;
                for(k=k+1-2*sup;k*(1-2*sup)<kmax*(1-2*sup);k+=(1-2*sup))
                {
                    Tk=get_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni));
                    //printf("k:%d Tk:%u\n",k,Tk);
                    if(Tk!=0)
                    {
                        if(k!=jmax)
                        {
                            continuer=1;
                        }
                        set_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni),0);
                        set_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni),Tk);
                        break;
                    }
                }
                Tj=get_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni));
                //printf("New Tj:%u\n",Tj);
            }
            if(Tj!=0&&continuer==1)
            {
                continuer=0;
                for(k=k+1-2*sup;k*(1-2*sup)<kmax*(1-2*sup);k+=(1-2*sup))
                {
                    Tk=get_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni));
                    //printf("k:%d Tk:%u\n",k,Tk);
                    if(Tk!=0)
                    {
                        if(Tk==Tj)
                        {
                            continuer=1;
                            set_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni),0);
                            set_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni),Tj+1);
                            set_free_tiles(g,get_free_tiles(g)+1);
                            set_score(g,grid_score(g)+valeur(2,Tj));
                            //printf("fusion %d/ %d~%d %u\n",i,j,k,Tj+1);
                        }
                        if(Tk!=Tj)
                        {
                            continuer=1;
                            set_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni),0);
                            set_tile(g,(j+1-2*sup)*loni+i*(1-loni),i*loni+(j+1-2*sup)*(1-loni),Tk);
                            //printf("colle %d/ %d->%d %u\n",i,k,j+1-2*sup,Tk);
                        }
                        break;
                    }
                }
            }
            j+=1-2*sup;
        }
    }
}


//------------------------------------------------------------------------------
// param: grid source
// Return:  rien
// Purpose: Fonction qui ajoute aléatoirement un tuile de valeur 2 ou 4
// avec une chance de 1/10 pour la tuile 4 et 9/10 pour la tuile 2
// realisation : Pierre Louis
//------------------------------------------------------------------------------
void add_tile (grid g)
{
    int u=rand()%get_free_tiles(g),i=0,j=0;
    while(u>0)
    {
        if(get_tile(g,i,j)==0)
        {
            --u;
        }
        i++;
        if(i==GRID_SIDE)
        {
            i=0;
            j++;
        }
    }
    while(get_tile(g,i,j)!=0)
    {
        i++;
        if(i==GRID_SIDE)
        {
            i=0;
            j++;
        }
    }
    set_tile(g,i,j,((rand()%10)<1)?2:1);
    set_free_tiles(g,get_free_tiles(g)-1);
}

//------------------------------------------------------------------------------
// param: grid : grille
// param: dir : direction
// Return:  rien
// Purpose: Fonction qui joue un tour
// realisation : Yannis Baltus
//------------------------------------------------------------------------------

void play(grid g,dir d)
{
    //show_grid(g);
    //if(d!=NOP)
        //{
            if(can_move(g,d))
                {
                    do_move(g,d);add_tile(g);
                }
        //}
        //show_grid(g);
        if(game_over(g))
        {
            printf("Game Over\n");
        }/*else{
            printf("Deplacements possibles:%s%s%s%s.\n",(can_move(g,LEFT))?" LEFT":"",(can_move(g,RIGHT))?" RIGHT":"",(can_move(g,UP))?" UP":"",(can_move(g,DOWN))?" DOWN":"");
        }*/
}

//------------------------------------------------------------------------------
// param: grid : grille
// Return:  rien
// Purpose: Fonction permettant l'affichage de la grille
// realisation : Alexis Richard
//------------------------------------------------------------------------------

/*void show_grid(grid g)
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
    printf("Free tiles: %d. Score: %lu\n",get_free_tiles(g),grid_score(g));
}*/

//------------------------------------------------------------------------------
// param: a :
// param: b : 
// Return:  rien
// Purpose: Fonction qui 
// realisation : Alexis Richard
//------------------------------------------------------------------------------

/*
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
*/


/******************************************************************************/
/*                               Relecture et commentaire :                   */
/*                             Simon Lejeune, Alexis Machin                   */
/******************************************************************************/




