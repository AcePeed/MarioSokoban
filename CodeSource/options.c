#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <windows.h>
#include <string.h>
#include <fmod/fmod.h>
#include <fmod/fmod_errors.h>

#include "constante.h"
#include "OpenLevel.h"
#include "options.h"
#include "howTo.h"

int sliderPushed(SDL_Event event,SDL_Surface *MusicVolumeBarreSlider,SDL_Surface *MusicVolumeBarreSliderButton, SDL_Rect position, SDL_Rect posiButton);

int applyButtonActif(SDL_Event event,SDL_Surface *button,SDL_Rect positionB);

int optionBoard(FMOD_SYSTEM *system,SDL_Surface *Screen, int *quit,FMOD_CHANNEL *channelMainMusic,float volume, TTF_Font *mainFont,int *restart)
{
    int sliderPushedValue=0;
    float musicVolume = 100;
    SDL_Event event;
    SDL_Color blackColor =  {0,0,0};
    SDL_Color whiteColor= {255,255,255};
    int continuer=1;
    int sliderActif=0;
    int applyButtonMouOns=0;

    FILE *musicVolFile=NULL;
    musicVolFile = fopen("resources/settings/musicVLM.set","r");
    fscanf(musicVolFile,"%f\n",&musicVolume);
    fclose(musicVolFile);



    const SDL_VideoInfo *videoInfo;
    videoInfo=SDL_GetVideoInfo();
    SDL_Rect position, positionButton,positionApplyButton;
    SDL_Surface *fond=NULL, *MusicVolumeBarreSlider=NULL, *MusicVolumeBarreSliderButton=NULL, *applyText=NULL, *button=NULL, *volumeText=NULL;
    MusicVolumeBarreSlider = IMG_Load("resources/imgs/BarreOptionSlider.png");
    MusicVolumeBarreSliderButton = IMG_Load("resources/imgs/BarreOptionSliderButton.png");
    button =  IMG_Load("resources/imgs/button.png");
    fond = IMG_Load("resources/imgs/optionbackground.jpg");
    applyText = TTF_RenderText_Solid(mainFont,"Retour",blackColor);
    char volumeChar[4];
    fprintf(stderr, "1\n");
 
 


    while(continuer && *quit && !*restart)
    {
        position.x=0;
        position.y=0;
        SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0));
        SDL_BlitSurface( fond, NULL, Screen, &position);//Collage du fond

        
        sprintf(volumeChar,"%d",(int)musicVolume);
        volumeText = TTF_RenderText_Solid(mainFont,volumeChar,whiteColor);
        position.x = (videoInfo->current_w/2)-volumeText->w/2;
        position.y = (videoInfo->current_h/6); 
        SDL_BlitSurface( volumeText, NULL, Screen, &position);//Collage du slider


        position.x = (videoInfo->current_w/2)-MusicVolumeBarreSlider->w/2;
        position.y = (videoInfo->current_h/4);
        SDL_BlitSurface( MusicVolumeBarreSlider, NULL, Screen, &position);//Collage du slider

        positionButton.x = (videoInfo->current_w/2)-MusicVolumeBarreSlider->w/2+((musicVolume/100)*(MusicVolumeBarreSlider->w))-MusicVolumeBarreSliderButton->w/2;
        positionButton.y = (videoInfo->current_h/4)-MusicVolumeBarreSliderButton->h/2+MusicVolumeBarreSlider->h/2;
        SDL_BlitSurface( MusicVolumeBarreSliderButton, NULL, Screen, &positionButton);//Collage du slider

        positionApplyButton.x = (videoInfo->current_w/10);
        positionApplyButton.y = (videoInfo->current_h/10);
        SDL_BlitSurface( button, NULL, Screen, &positionApplyButton);//Collage du bouton
        positionApplyButton.x = (videoInfo->current_w/10)+button->w/2-applyText->w/2;
        positionApplyButton.y = (videoInfo->current_h/10)+button->h/2-applyText->h/2;
        SDL_BlitSurface( applyText, NULL, Screen, &positionApplyButton);//Collage du text
        positionApplyButton.x = (videoInfo->current_w/10);
        positionApplyButton.y = (videoInfo->current_h/10);


        SDL_Flip(Screen);

        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_VIDEORESIZE:
                Screen = SDL_SetVideoMode( event.resize.w,event.resize.h,32,SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);//Ouverture de l'onglet
                break;
            case SDL_QUIT://Quitter le programme
                *quit = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                }
            case SDL_MOUSEBUTTONDOWN :
                if(applyButtonMouOns)
                {
                    continuer=0;
                }
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    sliderPushedValue = sliderPushed(event,MusicVolumeBarreSlider,MusicVolumeBarreSliderButton,position,positionButton);
                    if(sliderPushedValue==-2)
                        break;
                    sliderActif=1;
                    musicVolume = (sliderPushedValue-position.x)*100/MusicVolumeBarreSlider->w+9;
                    FMOD_Channel_SetVolume(channelMainMusic,musicVolume/100);
                    musicVolFile = fopen("resources/settings/musicVLM.set","w+");
                    fprintf(musicVolFile, "%f\n", musicVolume);
                    fclose(musicVolFile);
                }
                break;
            case SDL_MOUSEBUTTONUP :
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    if(sliderActif)
                    {
                        musicVolFile = fopen("resources/settings/musicVLM.set","w+");
                        fprintf(musicVolFile, "%f\n", musicVolume);
                        fclose(musicVolFile);
                        sliderActif=0;
                    }
                }
                break;
            case SDL_MOUSEMOTION :
                if(sliderActif)
                {
                    sliderPushedValue=event.motion.x - MusicVolumeBarreSliderButton->w/2;
                    musicVolume = (sliderPushedValue-position.x)*100/MusicVolumeBarreSlider->w+9 - MusicVolumeBarreSliderButton->w/8;
                    if(musicVolume<0)
                        musicVolume=0;
                    if(musicVolume>100)
                        musicVolume=100;
                    FMOD_Channel_SetVolume(channelMainMusic,musicVolume/100);
                    musicVolFile = fopen("resources/settings/musicVLM.set","w+");
                    fprintf(musicVolFile, "%f\n", musicVolume);
                    fclose(musicVolFile);
                }
                if(applyButtonActif(event,button,positionApplyButton))
                {
                    applyButtonMouOns=1;
                    button=IMG_Load("resources/imgs/buttonActif.png");
                }
                else
                {
                    applyButtonMouOns=0;
                    button=IMG_Load("resources/imgs/button.png");
                }
                break;
        }
    }
    return 0;
}




int sliderPushed(SDL_Event event,SDL_Surface *MusicVolumeBarreSlider,SDL_Surface *MusicVolumeBarreSliderButton, SDL_Rect position, SDL_Rect posiButton)
{
    int xRight,yRight,x,y,xRight2,yRight2;
    xRight=0;
    yRight=0;
    xRight2=0;
    yRight2=0;
    x = event.button.x;
    y = event.button.y;

    if(x>position.x && x<position.x+MusicVolumeBarreSlider->w)
    {
        xRight=1;
    }
    if(y>position.y && y<position.y+MusicVolumeBarreSlider->h)
    {
        yRight=1;
    }
    if(x>posiButton.x && x<posiButton.x+MusicVolumeBarreSliderButton->w && x<position.x+MusicVolumeBarreSlider->w && x>position.x)
    {
        xRight2=1;
    }
    if(y>posiButton.y && y<posiButton.y+MusicVolumeBarreSliderButton->h)
    {
        yRight2=1;
    }
    if((xRight && yRight) || (xRight2 && yRight2))
    {
        return event.button.x - MusicVolumeBarreSliderButton->w;
    }
    return -2;
}

int applyButtonActif(SDL_Event event,SDL_Surface *button,SDL_Rect positionB)
{
    int xRight=0, yRight=0;
    int x,y;
    x = event.motion.x;
    y = event.motion.y;
    if(x>positionB.x && x<positionB.x+button->w)
    {
        xRight=1;
    }
    if(y>positionB.y && y<positionB.y+button->h)
    {
        yRight=1;
    }
    if(xRight && yRight)
    {
        return 1;
    }
    return 0;
}
