#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constante.h"
#include "howTo.h"

int howTo(SDL_Surface *Screen , int *continuer)
{
    SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0));
    SDL_Surface *Image = NULL;
    Image = IMG_Load("resources/imgs/HowTo.jpg");
    SDL_Rect pos;
    SDL_Event event;
    pos.x=0;
    pos.y=0;
    SDL_BlitSurface(Image , NULL , Screen , &pos);
    SDL_Flip(Screen);
    int ContinueInMenu=1;
    while(*continuer && ContinueInMenu)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                *continuer=0;
                break;
            case SDL_KEYDOWN:
                if(event.key.keysym.sym==SDLK_ESCAPE || event.key.keysym.sym==SDLK_m)
                {
                    ContinueInMenu=0;
                }
                break;
        }
    }
    SDL_FreeSurface(Image);
    return 1;
}