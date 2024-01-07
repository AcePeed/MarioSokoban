#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <windows.h>

#include "levels.h"
#include "constante.h"
#include "jeu.h"


int buttonUp(int canClic[9] , int x , int y ,int button);
int choiceLevel(SDL_Surface *Screen , SDL_Surface *LevelsSurface[9] , int ownSprites[9], int canClic[9] , int *continuer, FMOD_SYSTEM *system,TTF_Font *mainFont)
{
	SDL_Surface *LevelsFond=NULL;
	int cheminInfo=0;
	SDL_Rect PosiLevels,PosiFond;
    int continuer2,ContinueInMenu2;
	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 255, 255, 255));
	SDL_Flip(Screen);
	PosiFond.x=0;
	PosiFond.y=0;
	LevelsFond = IMG_Load("resources/imgs/levels.bmp");
	SDL_Event event;

	int identifier=0;
    int ContinueInChoiceLVL=1;
    int ContinueInMenu=1;
    int actualTicks=SDL_GetTicks();

	while(*continuer && ContinueInMenu )
	{
    SDL_BlitSurface( LevelsFond, NULL, Screen, &PosiFond);
    PosiLevels.x=HAUTEUR_FENETRE/3-longueur_niveaux/2-100;//Posi. 1
    PosiLevels.y=LARGEUR_FENETRE/3-largeur_niveaux/2-40;
    SDL_BlitSurface( LevelsSurface[0], NULL, Screen, &PosiLevels);
    PosiLevels.x=HAUTEUR_FENETRE/2-longueur_niveaux/2;//Posi. 2
    PosiLevels.y=LARGEUR_FENETRE/3-largeur_niveaux/2-40;
    SDL_BlitSurface( LevelsSurface[1], NULL, Screen, &PosiLevels);
    PosiLevels.x=HAUTEUR_FENETRE/2-longueur_niveaux/2+320;//Posi. 3
    PosiLevels.y=LARGEUR_FENETRE/3-largeur_niveaux/2-40;
    SDL_BlitSurface( LevelsSurface[2], NULL, Screen, &PosiLevels);
    PosiLevels.x=HAUTEUR_FENETRE/3-longueur_niveaux/2-100;//Posi. 4
    PosiLevels.y=LARGEUR_FENETRE/2-largeur_niveaux/2;
    SDL_BlitSurface( LevelsSurface[3], NULL, Screen, &PosiLevels);
    PosiLevels.x=HAUTEUR_FENETRE/2-longueur_niveaux/2;//Posi. 5
    PosiLevels.y=LARGEUR_FENETRE/2-largeur_niveaux/2;
    SDL_BlitSurface( LevelsSurface[4], NULL, Screen, &PosiLevels);
    PosiLevels.x=HAUTEUR_FENETRE/2-longueur_niveaux/2+320;//Posi. 6
    PosiLevels.y=LARGEUR_FENETRE/2-largeur_niveaux/2;
    SDL_BlitSurface( LevelsSurface[5], NULL, Screen, &PosiLevels);
    PosiLevels.x=HAUTEUR_FENETRE/3-longueur_niveaux/2-100;//Posi. 7
    PosiLevels.y=2*LARGEUR_FENETRE/3-largeur_niveaux/2+40;
    SDL_BlitSurface( LevelsSurface[6], NULL, Screen, &PosiLevels);
    PosiLevels.x=HAUTEUR_FENETRE/2-longueur_niveaux/2;//Posi. 8
    PosiLevels.y=2*LARGEUR_FENETRE/3-largeur_niveaux/2+40;
    SDL_BlitSurface( LevelsSurface[7], NULL, Screen, &PosiLevels);
    PosiLevels.x=HAUTEUR_FENETRE/2-longueur_niveaux/2+320;//Posi. 9
    PosiLevels.y=2*LARGEUR_FENETRE/3-largeur_niveaux/2+40;
    SDL_BlitSurface( LevelsSurface[8], NULL, Screen, &PosiLevels);
    SDL_Flip(Screen);

		cheminInfo=0;
    	SDL_WaitEvent(&event);
    	switch(event.type)
    	{
    		case SDL_QUIT:
    		    *continuer=0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                fprintf(stderr, "%d\n", SDL_GetTicks()-actualTicks);
                if(SDL_GetTicks()-actualTicks>1000)
                {
                    identifier=buttonUp(canClic,event.button.x,event.button.y,event.button.button);
                    if(canClic[identifier-1]==1)
                        cheminInfo=identifier;
                    break;
                }
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_m:
                        ContinueInMenu=0;
                        break;
                    case SDLK_ESCAPE:
                        ContinueInMenu=0;
                        break;
                	case SDLK_KP1:
                	    identifier=1;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_1:
                	    identifier=1;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_KP2:
                	    identifier=2;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_2:
                	    identifier=2;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_KP3:
                	    identifier=3;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_3:
                	    identifier=3;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_KP4:
                	    identifier=4;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_4:
                	    identifier=4;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_KP5:
                	    identifier=5;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_5:
                	    identifier=5;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_KP6:
                	    identifier=6;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_6:
                	    identifier=6;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_KP7:
                	    identifier=7;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_7:
                	    identifier=7;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_KP8:
                	    identifier=8;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_8:
                	    identifier=8;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_KP9:
                	    identifier=9;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                	case SDLK_9:
                	    identifier=9;
                	    if(canClic[identifier-1]==1)
                	    	cheminInfo=identifier;
                	    break;
                }
                break;
    	}
    	if(cheminInfo!=0)
        {
            play(Screen, cheminInfo , ownSprites[identifier-1] , &ContinueInMenu , continuer, system,mainFont);
        }
            
        }
	SDL_FreeSurface(LevelsFond);
}




int buttonUp(int canClic[9] , int x , int y,int button)
{
    if(button!=SDL_BUTTON_LEFT)
        return 0;
    fprintf(stderr, "%d %d\n", x , y);
    if(x>HAUTEUR_FENETRE/3-longueur_niveaux/2-100 && x<HAUTEUR_FENETRE/3-longueur_niveaux/2-100+longueur_niveaux && y>LARGEUR_FENETRE/3-largeur_niveaux/2-40 && y<LARGEUR_FENETRE/3-largeur_niveaux/2-40+largeur_niveaux)
        return 1;
    if(x>HAUTEUR_FENETRE/2-longueur_niveaux/2 && x<HAUTEUR_FENETRE/2-longueur_niveaux/2+longueur_niveaux && y>LARGEUR_FENETRE/3-largeur_niveaux/2-40 && y<LARGEUR_FENETRE/3-largeur_niveaux/2-40+largeur_niveaux)
        return 2;


}