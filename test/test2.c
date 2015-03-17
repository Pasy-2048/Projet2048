#include "../grid.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "../fonctions-sup.h"

int equals(grid g, grid h){
	for(int i=0;i<GRID_SIDE;++i)
		for(int j=0;j<GRID_SIDE;++j)
			if(get_tile(g,i,j)!=get_tile(h,i,j))
				return i;
	return GRID_SIDE;
}

// remplit la grid de x
void fill_grid(grid g, unsigned int x){
	for (int i = 0; i < GRID_SIDE; ++i)
	{
		for (int j = 0; j < GRID_SIDE; ++j)
		{
			set_tile(g,i,j,x);
		}
	}
}

int main()
{
	srand(time(NULL));
	grid g = new_grid();
	grid h = new_grid();
	fill_grid(g,0);

	// Premier Cas Mouvement simple :
	set_tile(g,1,0,1);
	set_tile(g,2,0,1);
	set_tile(g,2,1,2);
	copy_grid(g,h);
	set_tile(g,3,2,1);
	set_tile(h,3,0,1);
	do_move(g,UP);

	int e = equals(g,h);
	if(e != GRID_SIDE){
		printf("Test mouvement simple echoue colonne %d\n",e);
		exit(1);
	}
	printf("Test mouvement simple ok\n");


	// second Cas Debut deplacement:
	// fusion simple et collage simple
	fill_grid(g,0);
	fill_grid(h,0);

	set_tile(g,0,1,1);
	set_tile(g,0,3,2);
	set_tile(g,1,0,1);
	set_tile(g,1,2,1);
	set_tile(g,2,1,1);
	set_tile(g,2,2,1);
	set_tile(g,3,1,2);
	set_tile(g,3,2,1);
	set_tile(g,3,3,1);

	set_tile(h,0,0,1);
	set_tile(h,0,1,2);
	set_tile(h,1,0,2);
	set_tile(h,2,0,2);
	set_tile(h,3,0,2);
	set_tile(h,3,1,2);
	do_move(g,UP);

	e = equals(g,h);
	if(e != GRID_SIDE){
		printf("Test debut deplacement echoue colonne %d\n",e);
		exit(1);
	}
	printf("Test debut deplacement ok\n");

	// deplacement complexe :
	// fusion complexe et collage complexe
	fill_grid(g,1);
	fill_grid(h,2);

	set_tile(g,0,0,0);
	set_tile(g,2,2,2);
	set_tile(g,2,3,2);
	set_tile(g,3,1,0);
	set_tile(g,3,2,2);

	set_tile(h,0,1,1);
	set_tile(h,0,2,0);
	set_tile(h,0,3,0);
	set_tile(h,1,2,0);
	set_tile(h,1,3,0);
	set_tile(h,2,1,3);
	set_tile(h,2,2,0);
	set_tile(h,2,3,0);
	set_tile(h,3,0,1);
	set_tile(h,3,2,1);
	set_tile(h,3,3,0);

	do_move(g,UP);

	e = equals(g,h);
	if(e != GRID_SIDE){
		printf("Test deplacement complexe echoue colonne %d\n",e);
		exit(1);
	}
	printf("Test deplacement complexe ok\n");


	// cas particulier :
	// valeurs embrassées et fusion complexe

	fill_grid(g,2);
	fill_grid(h,0);

	set_tile(g,0,0,1);
	set_tile(g,0,3,1);
	set_tile(g,1,0,0);
	set_tile(g,1,1,0);
	set_tile(g,1,2,1);
	set_tile(g,1,3,1);
	set_tile(g,2,0,0);
	set_tile(g,2,1,0);
	set_tile(g,2,2,1);
	set_tile(g,3,2,1);

	set_tile(h,0,0,1);
	set_tile(h,0,1,3);
	set_tile(h,0,2,1);
	set_tile(h,1,0,2);
	set_tile(h,2,0,1);
	set_tile(h,2,1,2);
	set_tile(h,3,0,3);
	set_tile(h,3,1,1);
	set_tile(h,3,2,2);

	do_move(g,UP);

	e = equals(g,h);
	if(e != GRID_SIDE){
		printf("Test cas particulier echoue colonne %d\n",e);
		exit(1);
	}
	printf("Test cas particulier ok\n");

	
	return 0;
}
