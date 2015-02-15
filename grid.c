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
bool can_move (grid g, dir d){
    int i,j,k;                                                                          //i,j compteurs, k "case suivante"
    bool direction = ((d==LEFT||d==RIGHT)?1:0) , sup=((d==RIGHT||d==DOWN)?1:0);             //"direction" determine la direction du mouvement (s'il faut parcourir les lignes ou les colonnes)
                                                                                        //sup est le sens dudit mouvement (s'il faut partir du début ou de la fin des lignes/colonnes concernees)
    tile Tj,Tk;                                                                         //Tj à comparer à Tk
    for(i=0;i<GRID_SIDE;i++)                                                            //que l'on prenne les lignes ou les colonnes, on part de la première, et on va à la dernière....
    {                                                                                   
        for(j=(GRID_SIDE-1)*(1-sup) ; j*(2*sup-1)<(GRID_SIDE-1)*sup ; j+=(2*sup-1))         //on se sert de sup pour faire aller j du début à la fin ou inversement.
        {                                                                               
            Tj = get_tile(g , j*direction+i*(1-direction) , i*direction+j*(1-direction));   //on se sert de "direction" pour déterminer sur quelle case on est exactement, et on la stocke.
            if(Tj!=0)                                                                       //Si ce n'est pas une case 'nulle'
            {                                                                           
                k = j+2*sup-1;                                                              //on se sert de k
                Tk=get_tile(g , k*direction+i*(1-direction) , i*direction+k*(1-direction)); //pour prendre la case 'suivante'
                if(Tk==0 || Tk==Tj)                                                         //si elle est nulle, Tj pourras y aller. Si elle est égale à Tj, elles pourront fusionner.
                {                                                    
                    return true;                                                            //Donc le mouvement a bien un sens.
                }
            }
        }
    }
    return false;                                                                       //Et sinon, on renvoie false.
}

//------------------------------------------------------------------------------
// param: grid : grille
// Return:  rien
// Purpose: Fonction qui permet de savoir si la partie est fini
// realisation : Simon Lejeune, Yannis Baltus, Pierre Louis
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
            for(k=((j!=GRID_SIDE-1)?0:1) ; k<=((i!=GRID_SIDE-1)?1:0) ; k++)
            {
                if(get_tile(g , i+k , j+1-k) == get_tile(g , i , j))
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
void do_move (grid g, dir d){
    bool dire=((d==LEFT||d==RIGHT)?1:0) , sup=((d==RIGHT||d==DOWN)?1:0) , continuer;   //continuer déterminera si c'est la peine de continuer à bosser sur la Li/Co séléctionnée.
    tile Tj,Tk;                                                                    //c.f. can_move(...);
    int i,j,k;
    int jmax=(GRID_SIDE-1)*(1-sup);                                                //jmax et kmax sont précalculés
    int kmax=jmax-(2*sup)+1;                                                       //pour simplifier l'écriture du code. Leur utilisation sera détaillée.
    for(i=0 ; i<GRID_SIDE ; i++){                                                      //que l'on prenne lignes ou colonnes, blah blah blah..
        continuer=1;                                                               //on initialise continuer à chaque Li/Co.
        j= (GRID_SIDE-1)*sup;                                                       //on selectionne la 'première' case de la Li/Co, selon sup.
        while(continuer==1&&j*(1-2*sup) < jmax){                                     //tant que c'est la peine de bosser sur la lico...;
            Tj=get_tile(g , j*dire+i*(1-dire) , i*dire+j*(1-dire));                    //on prend la case du tour
            k=j;                                                                   //on initialise k (pas besoin de checker les cases AVANT Tj).
            if(Tj==0)                                                              //si la case actuelle est nulle, on va voir s'il y en a une non-nulle plus loin dans la lico pour la mettre à sa place:
            {                                                             
                continuer=0;                                                       //D'ailleurs si on en trouve pas, on passe à la lico suivante.
                for(k=k+1-2*sup ; k*(1-2*sup)<kmax*(1-2*sup) ; k+=(1-2*sup)){          //donc, pour chacune des cases suivantes;
                    Tk = get_tile(g , k*dire+i*(1-dire) , i*dire+k*(1-dire));            //Déjà on prend la case en question, c'est plus pratique..
                    if(Tk!=0)                                                       //si elle est pas nulle
                    {                                                     
                        if(k!=jmax)                                                 //(si c'est la dernière de la colonne c'est quand même la dernière chose qu'on feras)
                        {                                               
                            continuer=1;                                           //(mais si il reste des cases derrière, on les checkeras juste pour être sur.)
                        }
                        set_tile(g , k*dire+i*(1-dire) , i*dire+k*(1-dire) , 0);         //Comme elle va se mettre sur Tj, on la met à zéro (pour pas qu'il reste un clone sur place)
                        set_tile(g , j*dire+i*(1-dire) , i*dire+j*(1-dire) , Tk);        //Et Tj, qui était nulle a une toute nouvelle valeur, yippee
                        break;                                                     //Du coup plus besoin de lui en chercher une nouvelle
                    }
                }
                Tj=get_tile(g , j*dire+i*(1-dire) , i*dire+j*(1-dire));                 //On prend sa nouvelle valeur, si nouvelle valeur il y a.
            }
            if(Tj!=0 && continuer==1)                                               //Si Tj avait déjà une valeur non nulle, ou si on lui en a trouvé une nouvelle
            {                                                
                continuer=0;                                                        //(Là encore, si il n'y a plus rien sur quoi bosser plus loin sur la lico, on passe à la suivante.
                for(k=k+1-2*sup ; k*(1-2*sup)<kmax*(1-2*sup) ; k+=(1-2*sup)){           //Donc très important on a pas reset le k, c'est aussi pour ça qu'on l'initialise en dehors du if(Tj==0).
                    Tk=get_tile(g , k*dire+i*(1-dire) , i*dire+k*(1-dire));             //case suivante,donc. On prend sa valeur. (toutes celles entre Tj et Tk sont à 0 btw)
                    if(Tk!=0)                                                       //Si celle-là est pas à zéro
                    {                                                      
                        if(k!=jmax)                                                 //Même chose, s'il reste d'autres case derrière on referas un tour.
                        {                                                
                            continuer=1;                                            //voila, nouveau tour en approche
                        }
                        if(Tk==Tj)                                                  //Si les deux cases sont égales, on les fusionne;
                        {                                                 
                            set_tile(g , k*dire+i*(1-dire) , i*dire+k*(1-dire) , 0);      //celle qui 'arrive' passe à 0
                            set_tile(g , j*dire+i*(1-dire) , i*dire+j*(1-dire) , Tj+1);   //L'autre gagne un niveau
                            set_free_tiles(g , get_free_tiles(g)+1);                  //Et du coup ça libère une case (une case libre en plus!!)
                            set_score(g , get_score(g)+valeur(2,Tj));                 //Et on update le score aussi
                        }
                        if(Tk!=Tj)                                                  //Par contre si elles sont pas pareil, on va 'coller' Tk à Tj
                        {                                                 
                            set_tile(g , k*dire+i*(1-dire) , i*dire+k*(1-dire) , 0);      //Donc la case à k passe à 0
                            set_tile(g , (j+1-2*sup)*dire+i*(1-dire) , i*dire+(j+1-2*sup)*(1-dire) , Tk); //Et celle juste après Tj prend sa valeur (à Tk). Notez que l'ordre des affectations est important dans le cas ou Tk pourrait être juste après Tj.
                        }
                        break;                                                      //Et qu'on aie fusionné ou collé, on ne bosseras plus sur ce Tj. (pas 2 fusions par tour)
                    }
                }
            }
            j+=1-2*sup;                                                             //Et donc on passe à la case suivante, pour lui chercher une nouvelle valeur, une fusion, ou un voisin.
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
      if(can_move(g,d))
        {
            do_move(g,d);
            add_tile(g);
        }
        if(game_over(g))
        {
            show_grid(g);
            printf("Game Over\n");
        }
}

//------------------------------------------------------------------------------
// param: grid : grille
// Return:  rien
// Purpose: Fonction permettant l'affichage de la grille
// realisation : Alexis Richard
//------------------------------------------------------------------------------

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
    printf("Free tiles: %d. Score: %lu\n",get_free_tiles(g),grid_score(g));
}

//------------------------------------------------------------------------------
// param: a :
// param: b : 
// Return:  rien
// Purpose: Fonction qui 
// realisation : Alexis Richard
//------------------------------------------------------------------------------

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



/******************************************************************************/
/*                               Relecture et commentaire :                   */
/*                             Simon Lejeune, Alexis Machin                   */
/******************************************************************************/




