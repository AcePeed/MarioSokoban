#ifndef file
#define file
#include "constante.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR] , FILE *source , char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] );
int chargerNiveauEdit(int niveau[][NB_BLOCS_HAUTEUR] );
int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR]);

#endif