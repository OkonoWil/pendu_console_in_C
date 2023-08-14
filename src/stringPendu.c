#include "header/stringPendu.h"

/**
 * Mode 1 : supprime le premier element et decale vers la gauche
 *        Mode 0 : supprime le dernier element
 *
 */
void chaine_pop(char chaine[], int mode)
{

    if (mode == 1)
    {
        for (unsigned int i = 0; i < strlen(chaine) - 1; i++)
        {
            chaine[i] = chaine[i + 1];
        }
    }

    chaine[strlen(chaine) - 1] = '\0';
}

/**
 * \brief Verifie le nombre de fois q'une lettre 'c' est presente dans 'mot' modifie 'recherche' en consequance
 * \return entier valant 1 si rien n'a ete trouve et 0 sinon
 */
int verifie_lettre(char mot[], char recherche[], char c)
{
    char tmp[strlen(mot) + 1];
    char *suite = tmp;
    int res = 1;

    strcpy(tmp, mot);

    while (suite != NULL)
    {
        suite = strchr(suite, c);

        if (suite != NULL)
        {
            recherche[strlen(recherche) - strlen(suite)] = c;
            chaine_pop(suite, 1);
            res = 0;
        }
    }

    return res;
}

/**
 * \brief Applique toupper sur une chaine complete
 *
 */
void str_toupper(char str[])
{
    for (unsigned int i = 0; i < strlen(str); i++)
    {
        str[i] = toupper(str[i]);
    }
}