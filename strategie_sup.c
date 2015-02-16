#include "strategie_sup.h"

typedef struct {dir direction;long int hMax;} retour;

long int heuristique(grid g){
	return 0;//Va falloir determiner ce qui a le plus de valeur.
}

retour* best(grid g,int depth){
	retour* ret=(retour*)malloc(sizeof(retour));
	if(depth==1){
		ret->hMax=heuristique(g);
		return ret;
	}
	ret->hMax=0;
	if(game_over(g)){return ret;}
	retour* rTemp;
	copy_grid(g,h);
	if(can_move(h,LEFT)){
		do_move(h,LEFT);
		rTemp=best(h,LEFT);
		if(rTemp->hMax>ret->hMax){
			ret->dir=LEFT;
			ret->hMax=rTemp->hMax;}
		free(rTemp);}
	copy_grid(g,h);
	if(can_move(h,RIGHT)){
		do_move(h,RIGHT);
		rTemp=best(h,RIGHT);
		if(rTemp->hMax>ret->hMax){
			ret->dir=RIGHT;
			ret->hMax=rTemp->hMax;}
		free(rTemp);}
	copy_grid(g,h);
	if(can_move(h,UP)){
		do_move(h,UP);
		rTemp=best(h,UP);
		if(rTemp->hMax>ret->hMax){
			ret->dir=UP;
			ret->hMax=rTemp->hMax;}
		free(rTemp);}
	copy_grid(g,h);
	if(can_move(h,DOWN)){
		do_move(h,DOWN);
		rTemp=best(h,DOWN);
		if(rTemp->hMax>ret->hMax){
			ret->dir=DOWN;
			ret->hMax=rTemp->hMax;}
		free(rTemp);}
	delete_grid(h);
	return ret;
}