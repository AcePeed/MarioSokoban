#ifndef games
#define games
#include <fmod/fmod.h>
#include <SDL/SDL_ttf.h>

int play(SDL_Surface *ecran , int LevelSelected , int ownSprites, int *ContinueInMenu, int *continuer , FMOD_SYSTEM *system,TTF_Font *mainFont);

#endif