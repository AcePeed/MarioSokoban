#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <fmod/fmod.h>
#include <fmod/fmod_errors.h>
#include "jeu.h"
#include "constante.h"
#include "levels.h"
#include "fichier.h"

void deplacerCaisse(int *premiereCase, int *secondeCase, FMOD_SYSTEM *system,FMOD_SOUND *woodPush);

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, SDL_Rect *posiPortal, int direction, FMOD_SYSTEM *system,FMOD_SOUND *woodPush,FMOD_SOUND *portalSound);


int play(SDL_Surface *ecran , int LevelSelected , int ownSprites, int *ContinueInMenu, int *continuer, FMOD_SYSTEM *system,TTF_Font *mainFont)
{
	fprintf(stderr, "jeu\n");
    SDL_Surface *mario[4] = {NULL}; 
    SDL_Surface *portal[2] = {NULL};
    SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL , *imageFond = NULL,*finishLevels = NULL;
    SDL_Surface *finishAll = NULL, *noir=NULL, *finishText=NULL;
    SDL_Color blackColor = {0,0,0};
    int justPassed = 0;
    FMOD_SOUND *levelUpSound,*finishAllSound,*restartSound;
    FMOD_SOUND *woodPush;
    FMOD_SOUND *portalSound;
    FMOD_System_CreateSound(system, "resources/sounds/tp.mp3",FMOD_CREATESAMPLE, 0, &portalSound);
    FMOD_System_CreateSound(system, "resources/sounds/caisseMoving.wav", FMOD_CREATESAMPLE, 0, &woodPush);
    FMOD_System_CreateSound(system, "resources/sounds/levelUp.mp3", FMOD_CREATESAMPLE, 0, &levelUpSound);
    FMOD_System_CreateSound(system, "resources/sounds/crowdclaps.wav",  FMOD_CREATESAMPLE, 0, &finishAllSound);
    FMOD_System_CreateSound(system, "resources/sounds/menu_popup.wav", FMOD_CREATESAMPLE, 0, &restartSound);
    const SDL_VideoInfo *videoInfo;
    videoInfo=SDL_GetVideoInfo();
    int willStart=1;
    int repeat = 0;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
    SDL_Rect position, positionJoueur, pos, posiPortal;
    SDL_Event event;
    int objectifsRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    char LevelSelectedFile[] = "resources/lvl/class9/";
    strcpy(LevelSelectedFile , "");
    char LevelSelectedFileLVL[]="resources/lvl/class9/niveaux.lvl";
    char LevelSelectedFileIMG[]="resources/lvl/class9/IMG_Fond.jpg";
    strcpy(LevelSelectedFileIMG , "");
    strcpy(LevelSelectedFileLVL , "");
    switch(LevelSelected)
    {
        case 1:
            strcpy(LevelSelectedFile , "resources/lvl/class1/");
            break;
        case 2:
            strcpy(LevelSelectedFile , "resources/lvl/class2/");
            break;
        case 3:
            strcpy(LevelSelectedFile , "resources/lvl/class3/");
            break;
        case 4:
            strcpy(LevelSelectedFile , "resources/lvl/class4/");
            break;
        case 5:
            strcpy(LevelSelectedFile , "resources/lvl/class5/");
            break;
        case 6:
            strcpy(LevelSelectedFile , "resources/lvl/class6/");
            break;
        case 7:
            strcpy(LevelSelectedFile , "resources/lvl/class7/");
            break;
        case 8:
            strcpy(LevelSelectedFile , "resources/lvl/class8/");
            break;
        case 9:
            strcpy(LevelSelectedFile , "resources/lvl/class9/");
            break;
    }
    if(ownSprites==0)
    {
        mur = IMG_Load("resources/imgs/mur.jpg");
        caisse = IMG_Load("resources/imgs/caisse.jpg");
        caisseOK = IMG_Load("resources/imgs/caisse_ok.jpg");
        objectif = IMG_Load("resources/imgs/objectif.png");
        mario[BAS] = IMG_Load("resources/imgs/mario_bas.gif");
        mario[GAUCHE] = IMG_Load("resources/imgs/mario_gauche.gif");
        mario[HAUT] = IMG_Load("resources/imgs/mario_haut.gif");
        mario[DROITE] = IMG_Load("resources/imgs/mario_droite.gif");
        portal[ENTRY] = IMG_Load("resources/imgs/portal1.jpg");
        portal[EXIT] = IMG_Load("resources/imgs/portal2.jpg");
    }
    finishLevels = IMG_Load("resources/imgs/next.jpg");
    finishAll = IMG_Load("resources/imgs/finishLevels.jpg");
    noir = IMG_Load("resources/imgs/acranNoir.jpg");
    SDL_SetAlpha(noir, SDL_SRCALPHA, 128);
    strcpy(LevelSelectedFileLVL , LevelSelectedFile);
    strcat(LevelSelectedFileLVL , "niveaux.lvl");
    strcpy(LevelSelectedFileIMG , LevelSelectedFile);
    strcat(LevelSelectedFileIMG , "IMG_Fond.jpg");
    imageFond = IMG_Load(LevelSelectedFileIMG);
    FILE* source = fopen(LevelSelectedFileLVL , "r");
    // Désactivation de la répétition des touches (remise à 100)
    willStart=1;
    int next=1;
    int boolCharge = 0;
    int ContinueInChoiceLVL = 1;
    while(*continuer && *ContinueInMenu && ContinueInChoiceLVL)
    {
        FMOD_System_Update(system);
        next=1;
        if(repeat==0)
            strcpy(ligneFichier , "");
        repeat=0;
        boolCharge = chargerNiveau(carte , source , ligneFichier);
        if( boolCharge && willStart==0 && !justPassed)
        {
            pos.x=0;
            pos.y=0;
            SDL_BlitSurface( noir , NULL ,ecran ,&pos);
            pos.x=videoInfo->current_w/2-finishLevels->w/2;
            pos.y=videoInfo->current_h/2-finishLevels->h/2;
            SDL_BlitSurface( finishLevels , NULL , ecran , &pos);
            finishText = TTF_RenderText_Solid(mainFont,"Niveau Termine",blackColor);
            pos.x=videoInfo->current_w/2-finishText->w/2;
            pos.y=videoInfo->current_h/2-finishText->h/2-4;
            SDL_BlitSurface( finishText , NULL , ecran , &pos);
            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, levelUpSound, 0, NULL);
        }
        if( !boolCharge && willStart==0 && !justPassed)
        {
            pos.x=0;
            pos.y=0;
            SDL_BlitSurface( noir , NULL ,ecran ,&pos);
            pos.x=videoInfo->current_w/2-finishLevels->w/2;
            pos.y=videoInfo->current_h/2-finishLevels->h/2;
            SDL_BlitSurface( finishAll , NULL , ecran , &pos);
            finishText = TTF_RenderText_Solid(mainFont,"Tous Les Niveaux Termines",blackColor);
            pos.x=videoInfo->current_w/2-finishText->w/2;
            pos.y=videoInfo->current_h/2-finishText->h/2-4;
            SDL_BlitSurface( finishText , NULL , ecran , &pos);
            FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, finishAllSound, 0, NULL);
        }
        if(willStart==0)
        {
            SDL_Flip(ecran);
            fprintf(stderr, "%d %d %d %d\n" , continuer,ContinueInMenu,ContinueInChoiceLVL,next );
            while(*continuer && *ContinueInMenu && ContinueInChoiceLVL && next)
            {
            SDL_WaitEvent(&event);
            switch(event.type)
            {
                case SDL_QUIT:
                    *continuer=0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_m:
                            *ContinueInMenu=0;
                            break;
                        case SDLK_ESCAPE:
                            ContinueInChoiceLVL=0;
                            break;
                        case SDLK_n:
                            next=0;
                            break;
                        case SDLK_RIGHT:
                            next=0;
                            break;
                        case SDLK_UP:
                            next=0;
                            break;
                        case SDLK_LEFT:
                            next=0;
                            break;
                        case SDLK_DOWN:
                            next=0;
                            break;
                        case SDLK_1:
                            next=0;
                            break;
                        case SDLK_KP1:
                            next=0;
                            break;
                    }
                    break;

            }
            }
        }
        SDL_EnableKeyRepeat(150, 70);
        if(!boolCharge)
            ContinueInChoiceLVL=0;
        willStart=1;


        // Recherche de la position de Mario au départ
        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
                {
                    positionJoueur.x = i;
                    positionJoueur.y = j;
                    carte[i][j] = VIDE;
                }
                if (carte[i][j] == PORT_EXIT) // Si Mario se trouve à cette position sur la carte
                {
                    posiPortal.x = i;
                    posiPortal.y = j;
                }
            }
        }
        willStart=1;
 
        marioActuel = mario[BAS];

        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        position.x=0;
        position.y=0;
        SDL_BlitSurface(imageFond, NULL, ecran, &position);
        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        objectifsRestants = 1;
                        break;
                    case PORT_ENTRY:
                        SDL_BlitSurface(portal[ENTRY], NULL, ecran, &position);
                        break;
                    case PORT_EXIT:
                        SDL_BlitSurface(portal[EXIT], NULL, ecran, &position);
                        break;
                }
            }
        }

        // On place le joueur à la bonne position
        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;
        SDL_BlitSurface(marioActuel, NULL, ecran, &position);



        SDL_Flip(ecran);
        justPassed=0;
        while(((*continuer && *ContinueInMenu && objectifsRestants!=0 && ContinueInChoiceLVL) || (willStart && *continuer && *ContinueInMenu && ContinueInChoiceLVL)) && repeat==0 && !justPassed)
        {
        	justPassed=0;
            willStart=0;
            SDL_WaitEvent(&event);
            willStart=0;
switch(event.type)
{
    case SDL_QUIT:
        *continuer=0;
        break;
    case SDL_KEYDOWN:
        switch(event.key.keysym.sym)
        {
            case SDLK_h:
                *ContinueInMenu=0;
                break;
            case SDLK_r:
                repeat=1;
                willStart=1;
                FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, restartSound, 0, NULL);
                break;
            case SDLK_ESCAPE:
                ContinueInChoiceLVL=0;
                break;
            case SDLK_UP:
                marioActuel = mario[HAUT];
                deplacerJoueur(carte, &positionJoueur, &posiPortal, HAUT, system,woodPush,portalSound);
                break;
            case SDLK_n:
                justPassed=1;
                willStart = 1;
                break;
            case SDLK_DOWN:
                marioActuel = mario[BAS];
                deplacerJoueur(carte, &positionJoueur, &posiPortal, BAS, system,woodPush,portalSound);
                break;
            case SDLK_RIGHT:
                marioActuel = mario[DROITE];
                deplacerJoueur(carte, &positionJoueur, &posiPortal, DROITE, system,woodPush,portalSound);
                break;
            case SDLK_LEFT:
                marioActuel = mario[GAUCHE];
                deplacerJoueur(carte, &positionJoueur, &posiPortal, GAUCHE, system,woodPush,portalSound);
                break;
        }
        break;
}

        // Effacement de l'écran
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
        position.x=0;
        position.y=0;
        SDL_BlitSurface(imageFond, NULL, ecran, &position);

        // Placement des objets à l'écran

        objectifsRestants = 0;

        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        objectifsRestants = 1;
                        break;
                    case PORT_ENTRY:
                        SDL_BlitSurface(portal[ENTRY], NULL, ecran, &position);
                        break;
                    case PORT_EXIT:
                        SDL_BlitSurface(portal[EXIT], NULL, ecran, &position);
                        break;
                }
            }
        }

        // On place le joueur à la bonne position
        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;
        SDL_BlitSurface(marioActuel, NULL, ecran, &position);



        SDL_Flip(ecran);

    }

        // Désactivation de la répétition des touches (remise à 0)
        SDL_EnableKeyRepeat(0, 0);
    }

    fclose(source);
    FMOD_Sound_Release(finishAllSound);
    FMOD_Sound_Release(levelUpSound);
    FMOD_Sound_Release(restartSound);
    FMOD_Sound_Release(portalSound);
    FMOD_Sound_Release(woodPush);


    // Libération des surfaces chargées
    SDL_FreeSurface(imageFond);
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(objectif);
    for (i = 0 ; i < 4 ; i++)
        SDL_FreeSurface(mario[i]);

return 1;
}




void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, SDL_Rect *posiPortal, int direction, FMOD_SYSTEM *system,FMOD_SOUND *woodPush,FMOD_SOUND *portalSound)
{
    switch(direction)
    {
        case HAUT:
            if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
                break;
            if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
                break;
            if (carte[pos->x][pos->y - 1] == PORT_ENTRY) // S'il y a un portail, on tp
            {
            	pos->x = posiPortal->x;
            	pos->y = posiPortal->y;
            	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, portalSound, 0, NULL);
            	break;
            }
            // Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
            if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
                (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
                carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK
                 || carte[pos->x][pos->y-2] == PORT_ENTRY|| carte[pos->x][pos->y - 2] == PORT_EXIT ))
                break;

            // Si on arrive là, c'est qu'on peut déplacer le joueur !
            // On vérifie d'abord s'il y a une caisse à déplacer
            deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2], system,woodPush);

            pos->y--; // On peut enfin faire monter le joueur (oufff !)
            break;


        case BAS:
            if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
                break;
            if (carte[pos->x][pos->y + 1] == MUR)
                break;
            if (carte[pos->x][pos->y + 1] == PORT_ENTRY) // S'il y a un portail, on tp
            {
            	pos->x = posiPortal->x;
            	pos->y = posiPortal->y;
            	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, portalSound, 0, NULL);
            	break;
            }
            if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
                (pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
                carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK
                 || carte[pos->x][pos->y+2] == PORT_ENTRY|| carte[pos->x][pos->y + 2] == PORT_EXIT))
                break;


            deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2], system,woodPush);

            pos->y++;
            break;


        case GAUCHE:
            if (pos->x - 1 < 0)
                break;
            if (carte[pos->x - 1][pos->y] == MUR)
                break;
            if (carte[pos->x - 1][pos->y] == PORT_ENTRY) // S'il y a un portail, on tp
            {
            	pos->x = posiPortal->x;
            	pos->y = posiPortal->y;
            	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, portalSound, 0, NULL);
            	break;
            }
            if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
                (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
                carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK||
                 carte[pos->x - 2][pos->y] == PORT_ENTRY|| carte[pos->x - 2][pos->y] == PORT_EXIT))
                break;


            deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y], system,woodPush);

            pos->x--;
            break;


        case DROITE:
            if (pos->x + 1 >= NB_BLOCS_LARGEUR)
                break;
            if (carte[pos->x + 1][pos->y] == MUR)
                break;
            if (carte[pos->x + 1][pos->y] == PORT_ENTRY) // S'il y a un portail, on tp
            {
            	pos->x = posiPortal->x;
            	pos->y = posiPortal->y;
            	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, portalSound, 0, NULL);
            	break;
            }
            if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
                (pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
                carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK || 
                carte[pos->x + 2][pos->y] == PORT_ENTRY|| carte[pos->x + 2][pos->y] == PORT_EXIT))
                break;

            deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y], system,woodPush);

            pos->x++;
            break;
    }
}



void deplacerCaisse(int *premiereCase, int *secondeCase, FMOD_SYSTEM *system,FMOD_SOUND *woodPush)
{
    if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
    {
        if (*secondeCase == OBJECTIF)
            *secondeCase = CAISSE_OK;
        else
            *secondeCase = CAISSE;

        if (*premiereCase == CAISSE_OK)
            *premiereCase = OBJECTIF;
        else
            *premiereCase = VIDE;
        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, woodPush, 0, NULL);
        FMOD_System_Update(system);
    }
}