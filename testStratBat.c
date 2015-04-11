#include "strategie_sup.h"
#include <time.h>

typedef struct histogramme{
  int size;
  int depth;
  int *compteur;
  int *maxes;
  int *score;
} *histo;

void afficheHis(histo h){
  printf("\nProfondeur: %d\n\n",h->depth);
  int nb;
  printf("Occupation finale (pour %d tests):\n\n",h->size);
  for(int i=16;i>=0;i--){
    if(h->compteur[i]!=0){
      printf("%u: %d\n",valeur(2,i+1),h->compteur[i]);}}

  printf("\nValeurs atteintes:\n\n");
  for(int i=16;i>0;i--){
    nb=0;
    for(int j=i;j<=16;j++){
      nb+=h->maxes[j];}
    if(nb>0){
      printf("%u: %d\n",valeur(2,i),nb);}}

  printf("\nScore max: ");
  nb=0;
  for(int i=0;i<h->size;i++)
    if(h->score[i]>nb)
      nb=h->score[i];
  printf("%d\n",nb);
}

int main(int argc, char** argv){
  int NBRE = 100;
  int depth=7,ar,i,j,m,v;
  srand(time(NULL));
  gridP e;
  for(depth=3;depth<7;depth++){
	histo h=calloc(1,sizeof(struct histogramme));
	h->size=NBRE;
    h->compteur=calloc(17,sizeof(int));
    h->maxes=calloc(17,sizeof(int));
    h->score=calloc(NBRE,sizeof(int));
    h->depth=depth;
    for(ar=0;ar<NBRE;ar++){
      grid g=new_grid();
      e.grille=g;
      e.nbFT=GRID_SIDE*GRID_SIDE-2;
      while(!game_over(g)){
	retour* r=best(e,depth);
	e.nbFT+=nbfuses(g,r->direction)+1;
	do_move(g,r->direction);
	free(r);
	add_tile(g);
      }
      h->score[ar]=grid_score(g);
      m=0;
      for(i=0;i<GRID_SIDE;i++)
	for(j=0;j<GRID_SIDE;j++){
	  v=get_tile(g,i,j);
	  (h->compteur[v-1])++;
	  if(v>=m){m=v;}}
      (h->maxes[m])++;
      delete_grid(g);
      }
    afficheHis(h);
    free(h->compteur);
    free(h->score);
    free(h->maxes);
    free(h);
  }
  return 0;}
