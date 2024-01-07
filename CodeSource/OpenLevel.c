#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <windows.h>

#include "constante.h"
#include "OpenLevel.h"
#include "levels.h"

int OpenLevels(SDL_Surface *Screen , int *Continue, FMOD_SYSTEM *system,TTF_Font *mainFont)
{
	SDL_Surface *LevelsSurface[9]={NULL};
	SDL_Rect pos;
	int canClic[9];
	int ownSprites[9]={0};
	SDL_Surface *version=NULL, *not=NULL;
	int Continue2,ContinueInMenu2;
	int i=0;
	int detectVersion=1;
	int yesORnoBool=0;
	yesORnoBool=0;
	version=IMG_Load("resources/imgs/errorVersion.bmp");
	not = IMG_Load("resources/imgs/notHere.bmp");
	FILE* yesORno = NULL;
	FILE* classe = NULL;
	i=0;
	yesORno = fopen("resources/lvl/class1/yes.bool" , "r");
	fscanf(yesORno , "%d" , &yesORnoBool);
	fclose(yesORno);
	if(yesORnoBool)
	{
		classe = fopen("resources/lvl/class1/level.lvl" , "r");
		fscanf( classe, "%d\n%d", &detectVersion , &ownSprites[i]);
		if(detectVersion>Version)
		{
			LevelsSurface[i]=version;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 200);
		    canClic[i]=0;
		    fclose(classe);
		}
		else
		{
			canClic[i]=1;
			LevelsSurface[i] = IMG_Load("resources/lvl/class1/imgClasse.bmp");
			fclose(classe);
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 230);
		}
	}
	if(yesORnoBool==0)
		{
			LevelsSurface[i]=not;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 130);
		}
	fclose(yesORno);
	yesORnoBool=0;
	i=1;
	yesORno = fopen("resources/lvl/class2/yes.bool" , "r");
	fscanf(yesORno , "%d" , &yesORnoBool);
	fclose(yesORno);
	if(yesORnoBool)
	{
		classe = fopen("resources/lvl/class2/level.lvl" , "r");
		fscanf( classe, "%d\n%d", &detectVersion , &ownSprites[i]);
		if(detectVersion>Version)
		{
			LevelsSurface[i]=version;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 200);
		    canClic[i]=0;
		    fclose(classe);
		}
		else
		{
			LevelsSurface[i] = IMG_Load("resources/lvl/class2/imgClasse.bmp");
			canClic[i]=1;
			fclose(classe);
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 230);
		}
	}
	if(yesORnoBool==0)
		{
			LevelsSurface[i]=not;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 130);
		}
	yesORnoBool=0;
	i=2;
	yesORno = fopen("resources/lvl/class3/yes.bool" , "r");
	fscanf(yesORno , "%d" , &yesORnoBool);
	fclose(yesORno);
	if(yesORnoBool)
	{
		classe = fopen("resources/lvl/class3/level.lvl" , "r");
		fscanf( classe, "%d\n%d", &detectVersion , &ownSprites[i]);
		if(detectVersion>Version)
		{
			LevelsSurface[i]=version;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 200);
		    canClic[i]=0;
		    fclose(classe);
		}
		else
		{
			LevelsSurface[i] = IMG_Load("resources/lvl/class3/imgClasse.bmp");
			canClic[i]=1;
			fclose(classe);
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 230);
		}
	}
	if(yesORnoBool==0)
		{
			LevelsSurface[i]=not;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 130);
		}
	yesORnoBool=0;
	i=3;
	yesORno = fopen("resources/lvl/class4/yes.bool" , "r");
	fscanf(yesORno , "%d" , &yesORnoBool);
	fclose(yesORno);
	if(yesORnoBool)
	{
		classe = fopen("resources/lvl/class4/level.lvl" , "r");
		fscanf( classe, "%d\n%d", &detectVersion , &ownSprites[i]);
		if(detectVersion>Version)
		{
			LevelsSurface[i]=version;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 200);
		    canClic[i]=0;
		    fclose(classe);
		}
		else
		{
			LevelsSurface[i] = IMG_Load("resources/lvl/class4/imgClasse.bmp");
			canClic[i]=1;
			fclose(classe);
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 230);
		}
	}
	if(yesORnoBool==0)
		{
			LevelsSurface[i]=not;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 130);
		}
	yesORnoBool=0;
	i=4;
	yesORno = fopen("resources/lvl/class5/yes.bool" , "r");
	fscanf(yesORno , "%d" , &yesORnoBool);
	fclose(yesORno);
	if(yesORnoBool)
	{
		classe = fopen("resources/lvl/class5/level.lvl" , "r");
		fscanf( classe, "%d\n%d", &detectVersion , &ownSprites[i]);
		if(detectVersion>Version)
		{
			LevelsSurface[i]=version;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 200);
		    canClic[i]=0;
		    fclose(classe);
		}
		else
		{
			LevelsSurface[i] = IMG_Load("resources/lvl/class5/imgClasse.bmp");
			canClic[i]=1;
			fclose(classe);
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 230);
		}
	}
	if(yesORnoBool==0)
		{
			LevelsSurface[i]=not;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 130);
		}
	yesORnoBool=0;
	i=5;
	yesORno = fopen("resources/lvl/class6/yes.bool" , "r");
	fscanf(yesORno , "%d" , &yesORnoBool);
	fclose(yesORno);
	if(yesORnoBool)
	{
		classe = fopen("resources/lvl/class6/level.lvl" , "r");
		fscanf( classe, "%d\n%d", &detectVersion , &ownSprites[i]);
		if(detectVersion>Version)
		{
			LevelsSurface[i]=version;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 200);
		    canClic[i]=0;
		    fclose(classe);
		}
		else
		{
			LevelsSurface[i] = IMG_Load("resources/lvl/class6/imgClasse.bmp");
			canClic[i]=1;
			fclose(classe);
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 230);
		}
	}
	if(yesORnoBool==0)
		{
			LevelsSurface[i]=not;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 130);
		}
	yesORnoBool=0;
	i=6;
	yesORno = fopen("resources/lvl/class7/yes.bool" , "r");
	fscanf(yesORno , "%d" , &yesORnoBool);
	fclose(yesORno);
	if(yesORnoBool)
	{
		classe = fopen("resources/lvl/class7/level.lvl" , "r");
		fscanf( classe, "%d\n%d", &detectVersion , &ownSprites[i]);
		if(detectVersion>Version)
		{
			LevelsSurface[i]=version;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 200);
		    canClic[i]=0;
		    fclose(classe);
		}
		else
		{
			LevelsSurface[i] = IMG_Load("resources/lvl/class7/imgClasse.bmp");
			canClic[i]=1;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 230);
			fclose(classe);
		}
	}
	if(yesORnoBool==0)
		{
			LevelsSurface[i]=not;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 130);
		}
	yesORnoBool=0;
	i=7;
	yesORno = fopen("resources/lvl/class8/yes.bool" , "r");
	fscanf(yesORno , "%d" , &yesORnoBool);
	fclose(yesORno);
	if(yesORnoBool)
	{
		classe = fopen("resources/lvl/class8/level.lvl" , "r");
		fscanf( classe, "%d\n%d", &detectVersion , &ownSprites[i]);
		if(detectVersion>Version)
		{
			LevelsSurface[i]=version;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 200);
		    canClic[i]=0;
		    fclose(classe);
		}
		else
		{
			LevelsSurface[i] = IMG_Load("resources/lvl/class8/imgClasse.bmp");
			canClic[i]=1;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 230);
			fclose(classe);
		}
	}
	if(yesORnoBool==0)
		{
			LevelsSurface[i]=not;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 130);
		}
	yesORnoBool=0;
	i=8;
	yesORno = fopen("resources/lvl/class9/yes.bool" , "r");
	fscanf(yesORno , "%d" , &yesORnoBool);
	fclose(yesORno);
	if(yesORnoBool)
	{
		classe = fopen("resources/lvl/class9/level.lvl" , "r");
		fscanf( classe, "%d\n%d", &detectVersion , &ownSprites[i]);
		if(detectVersion>Version)
		{
			LevelsSurface[i]=version;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 200);
		    canClic[i]=0;
		    fclose(classe);
		}
		else
		{
			LevelsSurface[i] = IMG_Load("resources/lvl/class9/imgClasse.bmp");
			canClic[i]=1;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 230);
			fclose(classe);
		}
	}
	if(yesORnoBool==0)
		{
			LevelsSurface[i]=not;
			SDL_SetAlpha(LevelsSurface[i], SDL_SRCALPHA, 130);
		}
	

	
	choiceLevel(Screen , LevelsSurface , ownSprites ,canClic , Continue, system, mainFont);
	for(i=0;i<9;i++)
	{
		if(LevelsSurface[i]!=version && LevelsSurface[i]!=not)
		{
			SDL_FreeSurface(LevelsSurface[i]);
		}
	}
	SDL_FreeSurface(version);
	SDL_FreeSurface(not);
}