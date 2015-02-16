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
	int i,j,k;
    bool loni=((d==LEFT||d==RIGHT)?1:0),sup=((d==RIGHT||d==DOWN)?1:0);
    tile Tj,Tk;
	for(i=0;i<GRID_SIDE;i++){														//
        for(j=(GRID_SIDE-1)*(1-sup);j*(2*sup-1)<(GRID_SIDE-1)*sup;j+=(2*sup-1)){	//On parcours la grille dans le sens fourni par sup.
            Tj=get_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni));						//loni determine les roles de i et j; lequel fait l'abscisse, lequel fait l'ordonnée.
			if(Tj!=0){
                k=j+2*sup-1;														//
				Tk=get_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni));					//Tk est la case 'suivant' Tj.
                if(Tk==0||Tk==Tj){													//Si on peut y mettre Tj (déplacement ou fusion), c'est que le mouvement est possible,
					return true;													//donc on renvoie true.
				}
			}
		}
	}
    return false;																	//Et si aucun déplacement n'est possible, le mouvement n'est pas valable, et on renvoie false.
}

//------------------------------------------------------------------------------
// param: grid : grille
// Return:  rien
// Purpose: Fonction qui permet de savoir si la partie est finie
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
        j=(GRID_SIDE-1)*sup;													//On initialise j à la 'première' case de la ligne/colonne, selon le sens dans lequel elle doit être parcourue (fourni par sup).
        while(continuer==1&&j*(1-2*sup)<jmax){									//On continue tant qu'il reste des cases non vérifiées (potentiellement non nulles) dans la ligne/colonne actuellement parcourue, et qu'on est pas arrivé à la fin de ladite li/co.
            Tj=get_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni));					//Ici, loni determine le role de i et j. Par exemple, pour un mouvement vertical, i est l'absisse et j l'ordonnée, et c'est l'inverse pour un mouvement horizontal.
            k=j;
            if(Tj==0){ 															//Si la case actuelle est vide, on cherche plus 'loin' dans la lico pour une nouvelle valeur.
                continuer=0;
                for(k=k+1-2*sup;k*(1-2*sup)<kmax*(1-2*sup);k+=(1-2*sup)){
					/*
					Equivalent à:
					if(sup==1){
						for(k=k-1;k>kmax;k--){
							(...)
						}
					}else if(sup==0){
						for(k=k+1;k<kmax;k++){
							(...)
						}
					}
																				//On initialise k à la case 'suivant' celle de j, puis on parcours la lico dans le sens fourni par sup.
					*/
                    Tk=get_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni));			//loni determine le role de i et k..
                    if(Tk!=0){
                        if(k!=jmax){											//
                            continuer=1;										//Ce if est utile si on trouve bien une nouvelle valeur, mais à la dernière case de la lico.
                        }														//En effet, il n'y auras plus de cases de valeur après Tj, donc ni déplacement ni fusions.
                        set_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni),0);		//
                        set_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni),Tk);		//On 'déplace' Tk dans Tj
						Tj=get_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni));		//Et on met Tj à jour.
                        break;
                    }
                }
            }
<<<<<<< Updated upstream
            if(Tj!=0&&continuer==1){																//On va chercher s'il y a après Tj une case de valeur, soit pour la fusionner avec Tj, soit pour la rapprocher.
                continuer=0;
                for(k=k+1-2*sup;k*(1-2*sup)<kmax*(1-2*sup);k+=(1-2*sup)){
				/*
				Equivalent à:
				if(sup==1){																			//On remonte dans la ligne/colonne; vu que le mouvement est descendant, on part de la dernière case.
					for(k=k-1;k>kmax;k--){
						(...)
					}
				}else if(sup==0){																	//L'inverse, on part de la première case et on va checker les suivantes.
					for(k=k+1;k<kmax;k++){
						(...)
					}
				}																					//À noter que kmax est un extrème, pas forcément un maximum.
				*/
                    Tk=get_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni));								//loni détermine, blah blah blah...
                    if(Tk!=0){
                        if(Tk==Tj){																	//Si la case suivante est équivalente à Tj, on fusionne;
                            set_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni),0);						//On enlève l'autre case.
                            set_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni),Tj+1);					//On augmente le niveau de Tj.
                            set_free_tiles(g,get_free_tiles(g)+1);									//Ca libère une case.
                            set_score(g,get_score(g)+valeur(2,Tj));									//Et ça donne des points.
=======
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
                            set_score(g , grid_score(g)+valeur(2,Tj));                 //Et on update le score aussi
>>>>>>> Stashed changes
                        }
                        if(Tk!=Tj){																	//Sinon, on la rapproche de Tj:
                            set_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni),0);						//On l'enlève.
                            set_tile(g,(j+1-2*sup)*loni+i*(1-loni),i*loni+(j+1-2*sup)*(1-loni),Tk);	//La case 'après' Tj prend sa valeur. (À noter que ce mouvement peut n'avoir aucun impact.
                        }
						if(k!=jmax){
                            continuer=1;															//Et si c'est la peine, on refait un tour.
						}
                        break;																		//On passe de toute manière au j suivant (pas deux fusions sur la même case, et on ne peut pas coller par dessus son nouveau voisin, si nouveau voisin il y a).
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
    int u=rand()%get_free_tiles(g),i=0,j=0; 		//u indique quelle case prendras la valeur.
    while(u>0)										//on parcours jusqu'à passer la (u-1)ème case vide.
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
    while(get_tile(g,i,j)!=0)						//on trouve la case vide suivante
    {
        i++;
        if(i==GRID_SIDE)
        {
            i=0;
            j++;
        }
    }
    set_tile(g,i,j,((rand()%10)<1)?2:1);			//et on lui impute une valeur, soit 2, soit 4.
    set_free_tiles(g,get_free_tiles(g)-1);			//(Une case libre en moins, donc.)
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
// Purpose: Fonction affichant la grille
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
}

//------------------------------------------------------------------------------
// param: a :	2 par défaut. La valeur à exposer, en quelque sorte.
// param: b : 	L'exposant (en fait le niveau de la case; valeur(2,0) != 2^0).
// Return:  rien
// Purpose: Fonction qui fournis à show_grid(...) la valeur à afficher
// selon le 'niveau' de la case.
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
*/


/******************************************************************************/
/*                               Relecture et commentaire :                   */
/*                             Simon Lejeune, Alexis Machin (MACHIN??????)    */
/******************************************************************************/




