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

int buttonMO(SDL_Event event,SDL_Surface *buttons,SDL_Rect position);

int main(int argc, char *argv[])
{
int restart = 1;
    int executOption = 0;
    int actifButtons[4] = {0};
    FMOD_SYSTEM *system;
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 15, FMOD_INIT_NORMAL, NULL);
	SDL_Surface *Screen=NULL,*menuPricipale=NULL, *ecranNoir=NULL, *buttonInactif=NULL, *buttonActif=NULL;
	SDL_Surface *buttonText[4]={NULL}, *titleText=NULL;
	SDL_Rect PosiMenu, posiButt;
	SDL_Event event;
	SDL_Color blackColor = {0,0,0}, whiteColor={255,255,255};
	TTF_Font *mainFont = NULL;
    FMOD_SOUND *musique;
    FMOD_RESULT resultat;
	resultat=FMOD_System_CreateSound(system, "resources/sounds/mainSong.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_NORMAL | FMOD_CREATESTREAM, 0, &musique);

	if(resultat != FMOD_OK)
	{
		fprintf(stderr, "Musique incontrolable\n");
		exit(EXIT_FAILURE);
	}

    /* On active la répétition de la musique à l'infini */
    FMOD_Sound_SetLoopCount(musique, -1);

    /* On joue la musique */
    FMOD_CHANNEL *channelMainMusic;
    resultat = FMOD_System_PlaySound(system,0, musique, 0, NULL);
    if(resultat != FMOD_OK)
    {
        fprintf(stderr, "Lecture de musique Impossible : %s\n",FMOD_ErrorString(resultat));
    }
    resultat = FMOD_System_GetChannel(system,0,&channelMainMusic);
    if(resultat != FMOD_OK)
    {
        fprintf(stderr, "Lecture de musique Impossible : %s\n",FMOD_ErrorString(resultat));
    }

	int Continue=1 ;

	

	if(SDL_Init(SDL_INIT_VIDEO)==-1)//Demarage de la SDL en mode video
	{
		fprintf(stderr, "Erreur du démarrage de la SDL%s\n", SDL_GetError);//Verification du demarrage
		exit(EXIT_FAILURE);//On quitte le Programme
	}

	    TTF_Init();
	    mainFont = TTF_OpenFont("resources/fonts/arial.ttf",21);



	const SDL_VideoInfo *videoInfo;
	videoInfo=SDL_GetVideoInfo();

	SDL_WM_SetIcon(SDL_LoadBMP("resources/imgs/Mario.bmp"), NULL);//Ajout de l'icone
    SDL_WM_SetCaption("Marion Sokoban ULTIMATE",NULL);//Initialisation du non à coté de l'icone
    putenv("SDL_VIDEO_WINDOW_POS=0,25");
	Screen = SDL_SetVideoMode( videoInfo->current_w*0.99,videoInfo->current_h*0.999 ,32,SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);//Ouverture de l'onglet
	if(Screen == NULL)
	{
		fprintf(stderr, "Erreur lors du chargement de la video : %s\n", SDL_GetError);
		exit(EXIT_FAILURE);
	}
	menuPricipale = IMG_Load("resources/imgs/menu.jpg");//Modification de menuPricipale pou l'image menu.jpg
	buttonActif = IMG_Load("resources/imgs/menuButtonMO.png");
	buttonInactif = IMG_Load("resources/imgs/menuButton.png");
while(restart)
{
restart=0;




	


    buttonText[0] = TTF_RenderText_Solid(mainFont,"Jouer",blackColor);
    buttonText[1] = TTF_RenderText_Solid(mainFont,"Comment Jouer",blackColor);
    buttonText[2] = TTF_RenderText_Solid(mainFont,"Options",blackColor);
    buttonText[3] = TTF_RenderText_Solid(mainFont,"Quitter",blackColor);
    titleText = TTF_RenderText_Solid(mainFont,"Mario Sokoban 2",whiteColor);
	float volume=1;
	FILE *musicVolFile = NULL;
	musicVolFile = fopen("resources/settings/musicVLM.set","r");
	fscanf(musicVolFile, "%f\n", &volume);
	fclose(musicVolFile);
	volume /= 100;
	resultat = FMOD_Channel_SetVolume(channelMainMusic,volume);

	if(executOption)
	{
		executOption=optionBoard(system, Screen, &Continue,channelMainMusic,volume,mainFont,&restart);
	}

    while(Continue && !restart)
    {
    	SDL_FillRect(Screen, NULL, SDL_MapRGB(Screen->format, 0, 0, 0));
    	PosiMenu.x=videoInfo->current_w/2-menuPricipale->w/2 ;//Initialisation de la position du menu principale
	    PosiMenu.y=videoInfo->current_h/2-menuPricipale->h/2 ;
        SDL_BlitSurface( menuPricipale, NULL, Screen, &PosiMenu);//Collage du menu
        posiButt.x = videoInfo->current_w/2-titleText->w/2;
        posiButt.y = videoInfo->current_h/10;
        SDL_BlitSurface( titleText, NULL, Screen, &posiButt);
        posiButt.x = videoInfo->current_w/2-buttonInactif->w/2;
        posiButt.y = videoInfo->current_h/3+videoInfo->current_h/10;
        if(actifButtons[1])
        {
        	SDL_BlitSurface( buttonActif, NULL, Screen, &posiButt);
        }
        else
        {
        	SDL_BlitSurface( buttonInactif, NULL, Screen, &posiButt);
        }
        posiButt.x = videoInfo->current_w/2- buttonText[1]->w/2;
        posiButt.y = videoInfo->current_h/3+videoInfo->current_h/10-buttonActif->h/2+buttonText[1]->h-4;
        SDL_BlitSurface(buttonText[1], NULL, Screen, &posiButt);
        posiButt.x = videoInfo->current_w/2-buttonInactif->w/2;
        posiButt.y = videoInfo->current_h/3+videoInfo->current_h/10*2;
        if(actifButtons[2])
        {
        	SDL_BlitSurface( buttonActif, NULL, Screen, &posiButt);
        }
        else
        {
        	SDL_BlitSurface( buttonInactif, NULL, Screen, &posiButt);
        }
        posiButt.x = videoInfo->current_w/2- buttonText[2]->w/2;
        posiButt.y = videoInfo->current_h/3+videoInfo->current_h/10*2-buttonActif->h/2+buttonText[2]->h-4;
        SDL_BlitSurface(buttonText[2], NULL, Screen, &posiButt);
        posiButt.x = videoInfo->current_w/2-buttonInactif->w/2;
        posiButt.y = videoInfo->current_h/3+videoInfo->current_h/10*3;
        if(actifButtons[3])
        {
        	SDL_BlitSurface( buttonActif, NULL, Screen, &posiButt);
        }
        else
        {
        	SDL_BlitSurface( buttonInactif, NULL, Screen, &posiButt);
        }
        posiButt.x = videoInfo->current_w/2- buttonText[3]->w/2;
        posiButt.y = videoInfo->current_h/3+videoInfo->current_h/10*3-buttonActif->h/2+buttonText[3]->h-4;
        SDL_BlitSurface(buttonText[3], NULL, Screen, &posiButt);
        posiButt.x = videoInfo->current_w/2-buttonInactif->w/2;
        posiButt.y = videoInfo->current_h/3;
        if(actifButtons[0])
        {
        	SDL_BlitSurface( buttonActif, NULL, Screen, &posiButt);
        }
        else
        {
        	SDL_BlitSurface( buttonInactif, NULL, Screen, &posiButt);
        }
        posiButt.x = videoInfo->current_w/2- buttonText[0]->w/2;
        posiButt.y = videoInfo->current_h/3-buttonActif->h/2+buttonText[0]->h-4;
        SDL_BlitSurface(buttonText[0], NULL, Screen, &posiButt);
        posiButt.x = videoInfo->current_w/2-buttonInactif->w/2;




        SDL_Flip(Screen);//Mise à jour de notre écran
    	SDL_WaitEvent(&event);
    	switch(event.type)
    	{
    		case SDL_VIDEORESIZE:
    		    Screen = SDL_SetVideoMode( event.resize.w,event.resize.h,32,SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);//Ouverture de l'onglet
    		    break;
    		case SDL_QUIT://Quitter le programme
    		    Continue = 0;
    		    break;
    		case SDL_KEYDOWN:
    		    switch(event.key.keysym.sym)
    		    {
                    case SDLK_ESCAPE:
    		    	    Continue = 0;
    		    	    break;
                    case SDLK_1:
                        OpenLevels(Screen , &Continue, system,mainFont);
                        fprintf(stderr, "continue Main %d\n", Continue);
                        break;
                    case SDLK_KP1:
                        OpenLevels(Screen , &Continue, system,mainFont);
                        fprintf(stderr, "continue Main %d\n", Continue);
                        break;
                    case SDLK_2:
                        howTo(Screen , &Continue);
                        break;
                    case SDLK_KP2:
                        howTo(Screen , &Continue);
                        break;
                    case SDLK_3:
                        executOption=optionBoard(system, Screen, &Continue,channelMainMusic,volume,mainFont,&restart);
                        break;
                    case SDLK_KP3:
                        executOption=optionBoard(system, Screen, &Continue,channelMainMusic,volume,mainFont,&restart);
                        break;
    		    }
    		    break;
    		case SDL_MOUSEMOTION :
    		    actifButtons[0]=0;
    		    actifButtons[1]=0;
    		    actifButtons[2]=0;
    		    actifButtons[3]=0;
    		    int resultOfButtonMo=0;
    		    resultOfButtonMo=buttonMO(event,buttonActif,posiButt);
    		    if(resultOfButtonMo==0)
    		    	break;
    		    actifButtons[resultOfButtonMo-1]=1;
    		    fprintf(stderr, "%d\n", buttonMO(event,buttonActif,posiButt));
    		    break;
    		case SDL_MOUSEBUTTONDOWN :
    		    if(actifButtons[0])
    		    {
    		    	OpenLevels(Screen , &Continue, system, mainFont);
    		    }
    		    if(actifButtons[1])
    		    {
    		    	howTo(Screen , &Continue);
    		    }
    		    if(actifButtons[2])
    		    {
    		    	executOption=optionBoard(system, Screen, &Continue,channelMainMusic,volume,mainFont,&restart);
    		    }
    		    if(actifButtons[3])
    		    {
    		    	Continue=0;
    		    }
    		    break;
    	}

    }
	



}
    SDL_FreeSurface(menuPricipale);
	TTF_CloseFont(mainFont);
	SDL_Quit();//Arrestation de la SDL
	TTF_Quit();
	FMOD_System_Close(system);
    FMOD_System_Release(system);
    return EXIT_SUCCESS;
}



int buttonMO(SDL_Event event,SDL_Surface *buttons,SDL_Rect position)
{
	const SDL_VideoInfo *videoInfo;
	videoInfo=SDL_GetVideoInfo();
	int returnValue, x, y,xRight=0,yRight=0;
	x=event.motion.x;
	y=event.motion.y;
	if(!(x>position.x && x<position.x+buttons->w))
	{
		return 0;
	}
	if(y>position.y && y<position.y+buttons->h)
	{
		return 1;
	}
	else if(y>videoInfo->current_h/3+videoInfo->current_h/10 && y<videoInfo->current_h/3+videoInfo->current_h/10+buttons->h)
	{
		return 2;
	}
	else if((y>videoInfo->current_h/3+videoInfo->current_h/10*2 && y<videoInfo->current_h/3+videoInfo->current_h/10*2+buttons->h))
	{
		return 3;
	}
	else if((y>videoInfo->current_h/3+videoInfo->current_h/10*3 && y<videoInfo->current_h/3+videoInfo->current_h/10*3+buttons->h))
	{
		return 4;
	}
	else
		return 0;
}