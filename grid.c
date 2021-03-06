/******************************************************************************/
/*                               Groupe :                                     */
/*     Yannis Baltus - Simon Lejeune - Alexis Richard - Pierre Martin           */
/******************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#include "grid.h"
#include "fonctions-sup.h"



void set_score(grid g, unsigned long int score);
int get_free_tiles(grid g);
void set_free_tiles (grid g, int x);
void show_grid(grid g);
unsigned int valeur(int a, unsigned int b);


/******************************************************************************/
/*                                Constructeur                               */
/******************************************************************************/

//------------------------------------------------------------------------------
// param: rien
// Return:  Gird : grille
// Purpose: Fonction qui construit une nouvelle grille
// Realisation : Yannis Baltus
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
	add_tile(g);
	add_tile(g);
    return g;
}

/******************************************************************************/
/*                                 Destructeur                                */
/******************************************************************************/

//------------------------------------------------------------------------------
// Param: grid : grille
// Return:  rien
// Purpose: Fonction qui libère la mémoire d'une grille
// Realisation : Simon Lejeune
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
// Param: grid : grille source
// Param: grid : grille destination
// Return:  rien
// Purpose: Fonction qui copie une grille
// Realisation : Simon Lejeune
//------------------------------------------------------------------------------
void copy_grid (grid src, grid dst)
{
    int i,j;
    for(i=0; i<GRID_SIDE; i++)
        {
            for(j=0; j<GRID_SIDE; j++)
            {
                set_tile(dst,i,j,get_tile(src,i,j));
            }
        }
    set_free_tiles(dst,get_free_tiles(src));
    set_score(dst,grid_score(src));
}

/******************************************************************************/
/*                              Accesseurs                                    */
/*  realisation : Simon Lejeune, Yannis Baltus, Pierre Martin, Alexis Richard  */
/******************************************************************************/

tile get_tile (grid g, int x, int y)
{
    return g->matrice[x][y];
}

void set_tile (grid g, int x, int y, tile t)
{
    g->matrice[x][y]=t;
}

void set_score(grid g, unsigned long int score)
{
    g->score=score;
}

// permet de savoir combien tuile vide il y a
int get_free_tiles(grid g)
{
    return g->nb_free_tiles;
}

// permet de mettre une nouvelle valeur dans une tuile vide
void set_free_tiles(grid g, int x)
{
    g->nb_free_tiles=x;
}

/******************************************************************************/
/*                               Fonctions                                    */
/******************************************************************************/


//------------------------------------------------------------------------------
// Param: grid : grille
// Return:  unsigned long int : score
// Purpose: Fonction qui permet d'avoir le score de la partie
// Realisation : Yannis Baltus
//------------------------------------------------------------------------------
unsigned long int grid_score (grid g)
{
    return g->score;
}


//------------------------------------------------------------------------------
// param: grid : grille
// param: dir : direction
// Param: grid : grille
// Param: dir : direction
// Return:  un booleen
// Purpose: Fonction qui permet de savoir si on peut bouger vers une direction
// Realisation : Pierre Martin, Alexis Richard
//------------------------------------------------------------------------------
                                        

bool can_move (grid g, dir d){

    int i, j, k;
    bool hori=((d==LEFT||d==RIGHT)?1:0); // hori determine les roles de i et j; lequel fait l'abscisse, lequel fait l'ordonnée.

    short int sens=((d==RIGHT||d==DOWN)?-1:1);
    tile target, next;
    /* 
       target est la case sur laquelle on se trouve, 
       next représente la case vers laquelle elle veut 
       se deplacer en fonction de la direction
    */
    for(i=0; i<GRID_SIDE; i++){
      for(j=(GRID_SIDE-1)*(1-sens)/2; j*sens < (GRID_SIDE-1)*(1+sens)/2; j+=sens){ 
	target=get_tile(g, j*hori+i*(1-hori), i*hori+j*(1-hori)); 
        k=j+sens;
        next=get_tile(g, k*hori+i*(1-hori), i*hori+k*(1-hori));
	if(next!=0){
	  if (next==target || target==0){
          	return true;
	  }
        }
      }
    }
    return false;
}


//------------------------------------------------------------------------------
// Param: grid : grille
// Return:  rien
// Purpose: Fonction qui permet de savoir si la partie est finie
// realisation : Simon Lejeune, Yannis Baltus, Pierre Martin
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
// Param: grid : source
// Param: dir : direction
// Return:  rien
// Purpose: Fonction qui execute les mouvements dans une direction.
// realisation : Alexis Richard Pierre Martin
//------------------------------------------------------------------------------

void do_move (grid g, dir d){

  bool hori=((d==LEFT||d==RIGHT)?1:0);   
  short int sens=((d==RIGHT||d==DOWN)?-1:1); 

  tile target, next;
  int i, j, k;
  int jmax = (GRID_SIDE-1)*(1+sens)/2;
  bool continuer;

  for(i=0; i<GRID_SIDE; i++){
   
    j=(GRID_SIDE-1)*(1-sens)/2;
    continuer=true;
    
    while(continuer){
      
      target = get_tile(g, j*hori+i*(1-hori), i*hori+j*(1-hori));

      k=j+sens;
      while(k*sens <= jmax*sens){
	next = get_tile(g, k*hori+i*(1-hori), i*hori+k*(1-hori));
	if(next!=0){
	  continuer=true;
	  set_tile(g, k*hori+i*(1-hori), i*hori+k*(1-hori), 0);
	  if(target == 0){
	    set_tile(g, j*hori+i*(1-hori), i*hori+j*(1-hori), next);
	  }
	  else{
	    if(next == target){
	      set_tile(g, j*hori+i*(1-hori), i*hori+j*(1-hori), target+1);
	      set_free_tiles(g, get_free_tiles(g)+1);
	      set_score(g, grid_score(g) + 2*valeur(2, target));
	    }
	    else{
	      set_tile(g,(j+sens)*hori + i*(1-hori),i*hori + (j+sens)*(1-hori), next);
	    }
	    j+=sens;
	  }
	  target = get_tile(g, j*hori+i*(1-hori), i*hori+j*(1-hori));
	}

	if(k*sens == jmax){
	  continuer=false;
	}
	k+=sens;
      }
    }
  }
}

//------------------------------------------------------------------------------
// Param: grid source
// Return:  rien
// Purpose: Fonction qui ajoute aléatoirement un tuile de valeur 2 ou 4
// avec une chance de 1/10 pour la tuile 4 et 9/10 pour la tuile 2.
// realisation : Pierre Martin
//------------------------------------------------------------------------------

void add_tile (grid g)
{
    int random_free_tiles=rand()%get_free_tiles(g); // On prend un nombre entre 0 et le nombre de cases vides actuel -1.

    int ln=0, cl=0;
    while(random_free_tiles>0)        /* On le fait correspondre à une case vide sur la grille. */
    {
        if(get_tile(g, ln, cl)==0)
        {
            --random_free_tiles;
        }
        ln++;
        if(ln==GRID_SIDE)
        {
            ln=0;
            cl++;
        }
    }

    while(get_tile(g, ln, cl)!=0)  /* Ensuite, nous cherchons la prochaine case vide : A la place de celle ci apparaitra une tuile 2 ou 4.*/
    {
        ln++;
        if(ln==GRID_SIDE)
        {
            ln=0;
            cl++;
        }
    }
    set_tile(g, ln, cl,((rand()%10)<1)?2:1);  // 1/10 d'ajouter un 2, 9/10 d'ajouter un 1.
    set_free_tiles(g, get_free_tiles(g)-1);
}

//------------------------------------------------------------------------------
// Param: grid : grille
// Param: dir : direction
// Return:  rien
// Purpose: Fonction qui joue un tour
// Realisation : Yannis Baltus
//------------------------------------------------------------------------------

void play(grid g,dir d)
{
	if(can_move(g,d))
	{
		do_move(g,d);
		add_tile(g);
	}

}





/******************************************************************************/
/*                               Relecture et commentaire :                   */
/*                             Simon Lejeune, Alexis Richard                  */
/******************************************************************************/




