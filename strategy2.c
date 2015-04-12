#include "strategy2.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
void free_memless_strat (strategy strat){
  free (strat);}

dir Israfel(strategy s, grid g){
	return Shinji(s,g);
}

dir Shinji(strategy s, grid g){
	j=availMoves(g)%4;
	if(j!=0){
		if(s->mem[0]==0){
			if(j%2==1){
				return LEFT;
				s->mem[0]=1;
			}
			else{
				return RIGHT;
			}
		}
		else{
			if(j>=2){
				return RIGHT;
				s->mem[0]=0;
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
	j=availMoves(g)/4;
	if(j!=0){
		if(j>=2){
			return UP;
		}
		else if(j==1){
			return DOWN;
		}
	}
}

void Zeruel (strategy strat){
free(strat->mem);}

strategy A1_baltus_lejeune_richard_martin_slow(){
	srand(time(NULL));
	strategy s=malloc(sizeof(struct strategy_s));
	s->name="PASY";
	s->play_move=Israfel;
	s->mem=malloc(sizeof(bool));
	s->free_strategy=Zeruel;
	((int*)(s->mem))={0,0};
	return s;
}
