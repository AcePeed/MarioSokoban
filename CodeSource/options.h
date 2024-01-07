#ifndef option
#define option
#include <fmod/fmod.h>

int optionBoard(FMOD_SYSTEM *system,SDL_Surface *Screen, int *quit,FMOD_CHANNEL *channelMainMusic,float volume, TTF_Font *mainFont,int *restart);

#endif