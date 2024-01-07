#ifndef DEF_CONTANTE
#define DEF_CONTANTE



       #define Version 2
       #define SizeBlock 34
       #define TAILLE_BLOC 34
       #define NbBlockHauteur 40
       #define NbBlockLargeur 25
       #define NB_BLOCS_LARGEUR 40
       #define NB_BLOCS_HAUTEUR 25
       #define LARGEUR_FENETRE NbBlockLargeur * SizeBlock
       #define HAUTEUR_FENETRE NbBlockHauteur * SizeBlock
       #define longueur_niveaux 240
       #define largeur_niveaux 120

       enum {HAUT , BAS , DROITE , GAUCHE};
       enum {VIDE , MUR , CAISSE , OBJECTIF , MARIO , CAISSE_OK , PORT_ENTRY , PORT_EXIT};
       enum {ENTRY , EXIT};
#endif