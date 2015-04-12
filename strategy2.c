#include "strategy2.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
void free_memless_strat (strategy strat){
  free (strat);}

dir Israfel(strategy s,grid g){
	if(((bool*)s->mem)[1]==0)
		return Shinji(s,g);
	else
		return Asuka(s,g);
}
  
dir Shinji(strategy s, grid g){
	((bool*)s->mem)[1]==1;
	int j=availMoves(g)%4;
	if(j!=0){
		if(((bool*)s->mem)[0]==0){
			if(j%2==1){
				return LEFT;
				((bool*)s->mem)[0]=1;
			}
			else{
				return RIGHT;
			}
		}
		else{
			if(j>=2){
				return RIGHT;
				((bool*)s->mem)[0]=0;
			}
			else{
				return LEFT;
			}
		}
	}
	else
		return Asuka(s,g);
}

dir Asuka(strategy s, grid g){
	((bool*)s->mem)[1]==0;
	int j=availMoves(g)/4;
	if(j!=0){
		if(j>=2){
			return UP;
		}
		else{
			return DOWN;
		}
	}
	return Shinj(s,g);
}

void Zeruel (strategy strat){
free(strat->mem);}

strategy A1_baltus_lejeune_richard_martin_fast(){
	srand(time(NULL));
	strategy s=malloc(sizeof(struct strategy_s));
	s->name="PASY";
	s->play_move=Israfel;
	s->mem=calloc(2,sizeof(bool));
	s->free_strategy=Zeruel;
	return s;
}
int availMoves(grid g){
	return (((can_move(g,LEFT))?1:0)+((can_move(g,RIGHT))?2:0)+((can_move(g,DOWN))?4:0)+((can_move(g,UP))?8:0));}
