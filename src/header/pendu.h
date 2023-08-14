#ifndef _PENDU_H_
#define _PENDU_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "stringPendu.h"

// Constante Globale
#define DICTIONNAIRE "assets/dictionnaire.txt"
#define TAILLE_MAX_CHAINE 50

// Prototype des fonctions
char lireCaractere();
char *mot_Mystere();
void loop_partie();
void clear_term();
void logo();
void affichage_pendu(int x);

#endif