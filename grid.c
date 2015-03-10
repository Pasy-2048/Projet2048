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



>>>>>>> 17/02_Compil
void set_score(grid g, unsigned long int score);
int get_free_tiles(grid g);
void set_free_tiles (grid g, int x);
void show_grid(grid g);
unsigned int valeur(int a, unsigned int b);
static tile next(grid g, int x, int y, dir d);
struct grid_s
{
    tile** matrice;
  
    unsigned long int score;
    int nb_free_tiles;
};

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
	show_grid(g);
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
//                             Version 1
/*bool can_move (grid g, dir d){
	int i,j,k;
    bool loni=((d==LEFT||d==RIGHT)?1:0),sup=((d==RIGHT||d==DOWN)?1:0);
    tile Tj,Tk;
	for(i=0;i<GRID_SIDE;i++){
    //On parcours la grille dans le sens fourni par sup.
	  for(j=(GRID_SIDE-1)*(1-sup);j*(2*sup-1)<(GRID_SIDE-1)*sup;j+=(2*sup-1)){
            //loni determine les roles de i et j; lequel fait l'abscisse, lequel fait l'ordonnée.
            Tj=get_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni));
	    if(Tj!=0){
		 k=j+2*sup-1;
        //Tk est la case 'suivant' Tj.
		 Tk=get_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni));
        //Si on peut y mettre Tj (déplacement ou fusion), c'est que le mouvement est possible,
                if(Tk==0||Tk==Tj){
					return true;
				}
			}
		}
	}
 //Et si aucun déplacement n'est possible, le mouvement n'est pas valable, et on renvoie false.
    return false;*/
//--------------------------------------------------------------------------------
//                             Version 2                                          

bool can_move(grid g, dir d)
{
/* 
   On parcourt le tableau dans le meme sens pour chaque direction.
   Si une tuile non vide suit une tuile vide, alors on peut bouger.
   Si deux tuiles qui se suivent ont la meme valeur, alors on peut bouger.
*/
    int xDebut = (d==LEFT)?1:0, xFin = (d==RIGHT)? GRID_SIDE-2:GRID_SIDE-1;  
    int yDebut = (d==UP)?1:0, yFin = (d==DOWN)? GRID_SIDE-2:GRID_SIDE-1;    
    int x,y;                                                                    
    tile nextTile;
    for(x=xDebut; x<=xFin; x++){
        for(y=yDebut; y<=yFin; y++){
	    if(get_tile(g, x, y)!=0){
	      nextTile = next(g, x, y, d);
              if(nextTile == 0 || nextTile == get_tile(g, x, y))
                 return true;
	    }
        }
    }
    return false;

/*     int i,j,k;

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
    return false;*/
}

static tile next(grid g, int x, int y, dir d)
{
  bool horizontal=0, vertical=0;
  if (d==LEFT || d==RIGHT)
    horizontal=(d==LEFT)?-1:1;
  else
    vertical=(d==DOWN)?1:-1;
  return get_tile(g, x+horizontal, y+vertical);
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
    bool loni=((d==LEFT||d==RIGHT)?1:0),sup=((d==RIGHT||d==DOWN)?1:0),continuer;// Loni représente la verticalité (ou non) du mouvement. Sup détermine s'il faudras partir du début ou de la fin des colonnes parcourues.
    tile Tj,Tk;
    int i,j,k,jmax=(GRID_SIDE-1)*(1-sup),kmax=jmax-(2*sup)+1;
	/*
	Equivalent à:
	int i;
	int j;
	int k;
	if(sup==1){
		int jmax=0;
		int kmax=-1;
	}else if(sup==0){
		int jmax=GRID_SIDE-1;
		int kmax=GRID_SIDE;
	}
															//Les 'maximums' ne sont atteints ni par j, ni par k; aucun risque d'erreur.
	*/
    for(i=0;i<GRID_SIDE;i++){
        continuer=1;
        j=(GRID_SIDE-1)*sup;											//On initialise j à la 'première' case de la ligne/colonne, selon le sens dans lequel elle doit être parcourue (fourni par sup).
        while(continuer==1&&j*(1-2*sup)<jmax){	       	                //On continue tant qu'il reste des cases non vérifiées (potentiellement non nulles) dans la ligne/colonne actuellement parcourue, et qu'on est pas arrivé à la fin de ladite li/co.
            Tj=get_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni));		 	//Ici, loni determine le role de i et j. Par exemple, pour un mouvement vertical, i est l'absisse et j l'ordonnée, et c'est l'inverse pour un mouvement horizontal.
=======
// Realisation : Alexis Richard Pierre Martin
//------------------------------------------------------------------------------
void do_move (grid g, dir d){
// Loni représente la verticalité (ou non) du mouvement. 
// Sup détermine s'il faudras partir du début ou de la fin des colonnes parcourues.
    bool horizontal=((d==LEFT||d==RIGHT)?1:0);
    bool sup=((d==RIGHT||d==DOWN)?1:0);
    bool continuer;
    
    tile Tj, Tk;
    int i, j, k;
    int jmax = (GRID_SIDE-1)*(1-sup);
    int kmax = jmax-(2*sup)+1;

    for(i=0;i<GRID_SIDE;i++){
        continuer=1;
        //j représente la première case de la ligne ou de la colonne que nous allons parcourir.
        j=(GRID_SIDE-1)*sup;
        //On continue tant qu'il reste des cases non vérifiées (potentiellement non nulles) dans la ligne/colonne actuellement parcourue, et qu'on est pas arrivé à la fin de ladite li/co.
        while(continuer==1&&j*(1-2*sup)<jmax){
            //Ici, loni determine le role de i et j. Par exemple, pour un mouvement vertical, i est l'absisse et j l'ordonnée, et c'est l'inverse pour un mouvement horizontal.
            Tj=get_tile(g,j*horizontal+i*(1-horizontal),i*horizontal+j*(1-horizontal));
            k=j;
            //Si la case actuelle est vide, on cherche plus 'loin' dans la lico pour une nouvelle valeur.
            if(Tj==0){
                continuer=0;
                for(k=k+1-2*sup;k*(1-2*sup)<kmax*(1-2*sup);k+=(1-2*sup)){

																	    
			       
		  Tk=get_tile(g, k*horizontal+i*(1-horizontal),i*horizontal+k*(1-horizontal)); /*<=next*/
                    if(Tk!=0){
                        //Ce if est utile si on trouve bien une nouvelle valeur, mais à la dernière case de la lico.
                        if(k!=jmax){
                            continuer=1;
                        }
                        //En effet, il n'y auras plus de cases de valeur après Tj, donc ni déplacement ni fusions.
                        set_tile(g,k*horizontal+i*(1-horizontal),i*horizontal+k*(1-horizontal),0);
                        set_tile(g,j*horizontal+i*(1-horizontal),i*horizontal+j*(1-horizontal),Tk);
                        //On 'déplace' Tk dans Tj
                        Tj=get_tile(g,j*horizontal+i*(1-horizontal),i*horizontal+j*(1-horizontal));
                        //Et on met Tj à jour.
                        break;
                    }
                }
            }
            //On va chercher s'il y a après Tj une case de valeur, soit pour la fusionner avec Tj, soit pour la rapprocher.
            if(Tj!=0&&continuer==1){																                continuer=0;
                for(k=k+1-2*sup;k*(1-2*sup)<kmax*(1-2*sup);k+=(1-2*sup)){
				/*
				Equivalent à:
				if(sup==1){	
                 //On remonte dans la ligne/colonne; vu que le mouvement est descendant, on part de la dernière case.
					for(k=k-1;k>kmax;k--){
						(...)
					}
				}else if(sup==0){																	
                 //L'inverse, on part de la première case et on va checker les suivantes.
					for(k=k+1;k<kmax;k++){
						(...)
					}
				}																					
                 //À noter que kmax est un extrème, pas forcément un maximum.
				*/
                    Tk=get_tile(g,k*horizontal+i*(1-horizontal),i*horizontal+k*(1-horizontal));
                    if(Tk!=0){
                        //Si la case suivante est équivalente à Tj, on fusionne;
                        if(Tk==Tj){
                            //On enlève l'autre case.
                            set_tile(g,k*horizontal+i*(1-horizontal),i*horizontal+k*(1-horizontal),0);
                            //On augmente le niveau de Tj.
                            set_tile(g,j*horizontal+i*(1-horizontal),i*horizontal+j*(1-horizontal),Tj+1);
                            //Ca libère une case.
                            set_free_tiles(g,get_free_tiles(g)+1);
                            //Et ça donne des points.
                            set_score(g,grid_score(g)+valeur(2,Tj));									                        }
                        //Sinon, on la rapproche de Tj:
                        if(Tk!=Tj){
                            //On l'enlève.
                            set_tile(g,k*horizontal+i*(1-horizontal),i*horizontal+k*(1-horizontal),0);
                            //La case 'après' Tj prend sa valeur. (À noter que ce mouvement peut n'avoir aucun impact.
                            set_tile(g,(j+1-2*sup)*horizontal+i*(1-horizontal),i*horizontal+(j+1-2*sup)*(1-horizontal),Tk);
                        }
						if(k!=jmax){
                            continuer=1;
						}
                        break;
                    }
                }
            }
            //On passe de toute manière au j suivant (pas deux fusions sur la même case, et on ne peut pas coller par dessus son nouveau voisin, si nouveau voisin il y a).
            j+=1-2*sup;
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
    // On prend un nombre entre 0 et le nombre de cases vides actuel -1.
    int random_free_tiles=rand()%get_free_tiles(g);
    int ln=0, cl=0;
    // On le fait correspondre à une case vide sur la grille.
    while(random_free_tiles>0)
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
    // Ensuite, nous cherchons la prochaine case vide : A la place de celle ci apparaitra une tuile 2 ou 4.
    while(get_tile(g, ln, cl)!=0)
    {
        ln++;
        if(ln==GRID_SIDE)
        {
            ln=0;
            cl++;
        }
    }
    // 1/10 d'ajouter un 4, 9/10 d'ajouter un 2.
    set_tile(g, ln, cl,((rand()%10)<1)?4:2);
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
	show_grid(g);
	printf("Score: %lu\n",grid_score(g));
	if(game_over(g))
	{
		printf("Game Over\n");
	}
}





/******************************************************************************/
/*                               Relecture et commentaire :                   */
/*                             Simon Lejeune, Alexis Richard                  */
/******************************************************************************/




