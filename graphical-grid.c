//
//  main.c
//  2048
//
//  Created by Simon Lejeune on 17/02/2015.
//  Copyright (c) 2015 Simon Lejeune. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "fonctions-sup.h"

#include "grid.h"

#define TAILLE_BLOC 106 

SDL_Surface *ecran;
SDL_Surface *fondJeux;


static void add_fond();
static void actualiser_grid(grid g);
static void aff_tile(grid g, int c, int l, tile t);
static void tile1(int r, int g, int b, int c, int l, char *tab);
static void move(grid g);
static void restart(grid g);
static void aff_game_over(grid g);
 
int main(int argc, char *argv[])
{
   fondJeux = NULL;
   ecran = NULL;
   grid g = new_grid();

    
    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL
   TTF_Init();
    ecran = SDL_SetVideoMode(520, 520, 32, SDL_HWSURFACE); // Ouverture de la fenêtre
    if (ecran == NULL) // Si l'ouverture a échoué, on le note et on arrête
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    } 
    SDL_WM_SetCaption("2048 - Baltus Lejeune Martin Richard ", NULL);

    // Coloration de la surface ecran
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 250, 248, 239));

   add_fond();
    actualiser_grid(g);
	move(g);

    SDL_Flip(ecran); /* Mise à jour de l'écran avec sa nouvelle couleur */
    

    SDL_FreeSurface(fondJeux);
    SDL_FreeSurface(ecran);
 	TTF_Quit();
    SDL_Quit(); // Arrêt de la SDL
 
    return EXIT_SUCCESS; // Fermeture du programme
}

static void add_fond()
{
	SDL_Rect positionFond;
	positionFond.x = 10; // Les coordonnées de la surface seront (0, 0)
	positionFond.y = 10;
    	fondJeux = SDL_LoadBMP("../img/grid.bmp");
    	SDL_BlitSurface(fondJeux, NULL, ecran, &positionFond);
}

/* actualise la grille de jeux, le score 
et affiche les tuiles a chaque coup */
static void actualiser_grid(grid g){
  SDL_FreeSurface(fondJeux);
  SDL_Surface *texte = NULL;
  SDL_Rect positionFond;
  SDL_Rect position;
  positionFond.x = 10;
  positionFond.y = 10;
  fondJeux = SDL_LoadBMP("../img/grid.bmp");
  SDL_BlitSurface(fondJeux, NULL, ecran, &positionFond);
  
  for(int c=0;c<GRID_SIDE;c++){
    for(int l=0;l<GRID_SIDE;l++){
      if(get_tile(g,c,l)!=0)
	aff_tile(g,c,l,get_tile(g,c,l));
    }
  }

  unsigned long int score = grid_score(g);
  TTF_Font *police;
  SDL_Color couleur = {0,0,0};
  char *tab;
  tab = malloc(sizeof(unsigned long int));
  sprintf(tab,"%ld",score);
  positionFond.x = 150;
  positionFond.y = 8;
  position.x = 50 ;
  position.y = 8;
  police = TTF_OpenFont("../Font/game_over.ttf",50);
  texte = TTF_RenderText_Blended(police,"SCORE :",couleur);
  SDL_BlitSurface(texte,NULL,ecran,&position);
  texte = TTF_RenderText_Solid(police,tab,couleur);
  SDL_BlitSurface(texte,NULL,ecran,&positionFond);
  SDL_Flip(ecran);
  free(tab);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
}


/* execute le movement celui l'appuie 
des flèches directionnelles*/
static void move(grid g){
  SDL_Event event;
  int continuer = 1;
  while(continuer){
    SDL_WaitEvent(&event); 
    if(game_over(g))
      aff_game_over(g);
    switch(event.type){
    case SDL_QUIT:
      continuer = 0;
      break;
    case SDL_KEYDOWN:
      if(!game_over(g)){
	switch(event.key.keysym.sym){
	case SDLK_ESCAPE:
	  restart(g);
	  break;
	case SDLK_UP:
	  play(g,UP);
	  actualiser_grid(g);
	  break;
	case SDLK_DOWN:
	  play(g,DOWN);
	  actualiser_grid(g);
	  break;

	case SDLK_RIGHT:
	  play(g,RIGHT);
	  actualiser_grid(g);
	  break;
	case SDLK_LEFT:
	  play(g,LEFT);
	  actualiser_grid(g);
	  break;
	default:
	  break;
	}
      }
      break;
    default:
      break;
    }
  }
}

/* affiche la valeur des tuiles ainsi que leurs couleurs*/
static void aff_tile(grid g, int c, int l, tile t){

  char *tab = malloc(sizeof(tile));
  sprintf(tab,"%d",valeur(2,t));

  switch(t){
  case 1:
    tile1(236, 240, 241,c,l,tab);
    break;
  case 2:
    tile1(46, 204, 113,c,l,tab);
    break;
  case 3:
    tile1(231, 76, 60,c,l,tab);
    break;
  case 4:
    tile1(155, 89, 182,c,l,tab);
    break;
  case 5:
    tile1(155, 89, 182,c,l,tab);
    break;
  case 6:
    tile1(243, 156, 18,c,l,tab);
    break;
  case 7:
    tile1(22, 160, 133,c,l,tab);
    break;
  case 8:
    tile1(52, 73, 94,c,l,tab);
    break;
  case 9:
    tile1(237,200,80,c,l,tab);
    break;
  case 10:
    tile1(233,183,9,c,l,tab);
    break;
  case 11:
    tile1(227,208,0,c,l,tab);
    break;
  default:
    tile1(255,255,255,c,l,tab);
    break;
  }
  free(tab);
}

/* créer chaque tuile et les places dans la grille */
static void tile1(int r, int g, int b, int c, int l, char *tab){
  SDL_Rect pos;
  SDL_Surface *ti = NULL;
  TTF_Font *police;

  pos.x = c*115+35;
  pos.y = l*115+35;
  ti = SDL_CreateRGBSurface(SDL_HWSURFACE,TAILLE_BLOC,TAILLE_BLOC,32,0,0,0,0);

if ( atoi(tab) < 10)
 police = TTF_OpenFont("../Font/ka1.ttf",30);
else if (atoi(tab) < 100)
police = TTF_OpenFont("../Font/ka1.ttf",25);
else 
police = TTF_OpenFont("../Font/ka1.ttf",20);
  
  SDL_Surface *texte;

  SDL_Color black = {0,0,0};
  SDL_Color couleur = {r,g,b};

  SDL_FillRect(ti,NULL,SDL_MapRGB(ecran->format,r,g,b));
  SDL_BlitSurface(ti,NULL,ecran,&pos);
  texte = TTF_RenderText_Shaded(police,tab,black,couleur);

if ( atoi(tab) < 10)
  pos.x += 40;
else if (atoi(tab) <100)
  pos.x += 32;
else
  pos.x += 28;  
  pos.y += 32;

  SDL_BlitSurface(texte,NULL,ecran,&pos);

  SDL_Flip(ecran);
  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
  SDL_FreeSurface(ti);
}

/* redemare la grille à zero */
static void restart(grid g){
  delete_grid(g);
  g = new_grid();
  actualiser_grid(g);
  move(g);
}


/* affiche le game over et le score */
static void aff_game_over(grid g){
  TTF_Font *police;
  SDL_Surface *fondGameOver;
  SDL_Rect pos;
  SDL_Rect posFond;
  SDL_Rect position;
  SDL_Surface *texte;
  SDL_Color noir = {0,0,0};
  pos.x = 20;
  pos.y = 185;
  posFond.x = 0;
  posFond.y = 0;
  police = TTF_OpenFont("../Font/ka1.ttf",65);
  texte = TTF_RenderText_Blended(police,"GAME OVER",noir);
  fondGameOver = SDL_CreateRGBSurface(SDL_HWSURFACE,520,520,32,0,0,0,0);
  SDL_FillRect(fondGameOver,NULL,SDL_MapRGB(ecran->format,236,240,241));
  SDL_BlitSurface(fondGameOver,NULL,ecran,&posFond);
  SDL_BlitSurface(texte,NULL,ecran,&pos);

  unsigned long int score = grid_score(g);
  SDL_Color couleur = {0,0,0};
  char *tab;
  tab = malloc(sizeof(unsigned long int));
  sprintf(tab,"%ld",score);
  position.x = 175;
  position.y = 295;
  police = TTF_OpenFont("../Font/game_over.ttf",65);
  texte = TTF_RenderText_Blended(police,"SCORE:",couleur);
  SDL_BlitSurface(texte,NULL,ecran,&position);
  position.x = 265;
  position.y = 295;
  police = TTF_OpenFont("../Font/game_over.ttf",65);
  texte = TTF_RenderText_Solid(police,tab,couleur);
  SDL_BlitSurface(texte,NULL,ecran,&position);


  SDL_Flip(ecran);

  TTF_CloseFont(police);
  SDL_FreeSurface(texte);
}

