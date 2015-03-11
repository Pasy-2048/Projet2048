#include "strategie_sup.h"

typedef struct {dir direction;long int hMax;} retour;

long int heuristique(grid g){
	return grid_score(g);
	
}

retour* best(grid g,int depth){
	retour* ret=(retour*)malloc(sizeof(retour));
	ret->hMax=heuristique(g);
	if(depth==0||game_over(g)){
		return ret;
	}
	dir dirTab[4]={UP,DOWN,RIGHT,LEFT};
	int i;
	for(i=0;i<4;i++){
		copy_grid(g,h);
		if(can_move(h,dirTab[i])){
			do_move(h,dirTab[i]);
			retour* rTemp=best(h,dirTab[i]);
			if(rTemp->hMax>ret->hMax){
				ret->dir=dirTab[i];
				ret->hMax=rTemp->hMax;}
			free(rTemp);}}
	delete_grid(h);
	return ret;
}
