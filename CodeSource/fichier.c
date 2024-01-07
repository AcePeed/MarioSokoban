#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constante.h"
#include <SDL/SDL.h>
#include "jeu.h"
#include "fichier.h"


int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR] , FILE *source , char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1])
{
    int i = 0, j = 0;

    if(strcmp(ligneFichier , "")==0)
    	fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, source);
    if(strcmp(ligneFichier , "")==0)
    	return 0;
    

    for (i = 0 ; i < NB_BLOCS_HAUTEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_LARGEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
				case '5':
                    niveau[j][i] = 5;
                    break;
				case '6':
                    niveau[j][i] = 6;
                    break;
                case '7':
                    niveau[j][i] = 7;
                    break;
                case ' ':
                    niveau[j][i] = 0;
                    break;
            }
        }
    }
    return 1;
}

int chargerNiveauEdit(int niveau[][NB_BLOCS_HAUTEUR] )
{
    FILE *source = fopen("resources/lvl/class1/niveaux.lvl" , "r");
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
    int i = 0, j = 0;


    for (i = 0 ; i < NB_BLOCS_HAUTEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_LARGEUR ; j++)
        {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
            {
                case '0':
                    niveau[j][i] = 0;
                    break;
                case '1':
                    niveau[j][i] = 1;
                    break;
                case '2':
                    niveau[j][i] = 2;
                    break;
                case '3':
                    niveau[j][i] = 3;
                    break;
                case '4':
                    niveau[j][i] = 4;
                    break;
            }
        }
    }
    fclose(source);
    return 1;
}


int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR])
{
    FILE* fichier = NULL;
    int i = 0, j = 0;

    fichier = fopen("niveaux.lvl", "w");
    if (fichier == NULL)
        return 0;

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            fprintf(fichier, "%d", niveau[j][i]);
        }
    }

    fclose(fichier);
    return 1;
}