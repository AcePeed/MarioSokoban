#ifndef choice
#define choice
#include <fmod/fmod.h>
#include <SDL/SDL_ttf.h>

int choiceLevel(SDL_Surface *Screen , SDL_Surface *LevelsSurface[9] , int ownSprites[9], int canClic[9], int *continuer, FMOD_SYSTEM *system,TTF_Font *mainFont);

#endif