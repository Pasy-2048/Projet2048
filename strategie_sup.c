#include "strategie_sup.h"

int nbfuses(grid g, dir d){
	int i,j,k,n=0;
	bool loni=((d==LEFT||d==RIGHT)?1:0),sup=((d==RIGHT||d==DOWN)?1:0);
	tile Tj,Tk;
	for(i=0;i<GRID_SIDE;i++){
		for(j=(GRID_SIDE-1)*(1-sup);j*(2*sup-1)<(GRID_SIDE-1)*sup;j+=(2*sup-1)){
			Tj=get_tile(g,j*loni+i*(1-loni),i*loni+j*(1-loni));
			if(Tj!=0){
				for(k=j+2*sup-1;k*(2*sup-1)<=(GRID_SIDE-1)*sup;k+=(2*sup-1)){
					Tk=get_tile(g,k*loni+i*(1-loni),i*loni+k*(1-loni));
					if(Tk!=0){
						j=k+1-2*sup;
						if(Tk==Tj){
							n++;
							j+=2*sup-1;}
					}
				}
			}
		}
	}
	return n;
}

int beurb(grid g){
  int i,j,ret=0;
  for(i=0;i<GRID_SIDE;i++)
    for(j=0;j<GRID_SIDE;j++)
      ret+=min(i+1,GRID_SIDE-i)*min(j+1,GRID_SIDE-j)*get_tile(g,i,j);
  return ret;
}

int sumfuses(grid g){
	dir dirTab[4]={UP,DOWN,RIGHT,LEFT};
	int i,n;
	for(i=0;i<4;i++){
		n+=nbfuses(g,dirTab[i]);}
	return n;
}

retour* maxfuses(grid g){
	dir dirTab[4]={UP,DOWN,RIGHT,LEFT};
	int i,n;
	retour* ret=(retour*)malloc(sizeof(retour));
	ret->hMax=0;
	for(i=0;i<4;i++){
		n=nbfuses(g,dirTab[i]);
		if(n>=ret->hMax){
			ret->hMax=n;
			ret->direction=dirTab[i];}}
	return ret;
}

long unsigned int krakat(grid g){
	int i,j,k;
	long unsigned int ret=0;
	for(i=0;i<GRID_SIDE;i++)
		for(j=0;j<GRID_SIDE;j++)
			for(k=((j==GRID_SIDE-1)?1:0);k<=((i==GRID_SIDE-1)?0:1);k++)
				ret+=abs(get_tile(g,i,j)-get_tile(g,i+k,j+1-k));
	return ret;
}

int min(int a, int b){
	return (a<b)?a:b;}

long unsigned int heuristique(gridP *e){
	retour* r=maxfuses(e->grille);
	long int retour=25*(e->nbFT+(r->hMax))-(9*krakat(e->grille)+4*beurb(e->grille));
	free(r);
	return retour;
}

retour* best(gridP *e,int depth){
	retour* ret=(retour*)malloc(sizeof(retour));
	ret->hMax=0;
	if(depth==0||game_over(e->grille)){
		ret->hMax=heuristique(e);
		return ret;
	}
	dir dirTab[4]={UP,DOWN,RIGHT,LEFT};
	int i;
	grid h=new_grid();
	gridP *f=malloc(sizeof(gridP));
	f->grille=h;
	f->nbFT=e->nbFT-1;
	for(i=0;i<4;i++){
		copy_grid(e->grille,f->grille);
		f->nbFT=e->nbFT;
		if(can_move(f->grille,dirTab[i])){
			f->nbFT+=nbfuses(f->grille,dirTab[i]);
			do_move(f->grille,dirTab[i]);
			retour* rTemp=best(f,depth-1);
			if(rTemp->hMax>=ret->hMax){
				ret->direction=dirTab[i];
				ret->hMax=rTemp->hMax;}
			free(rTemp);}}
	delete_grid(h);
	free(f);
	ret->hMax=(ret->hMax)*0.5+heuristique(e);
	return ret;
}
