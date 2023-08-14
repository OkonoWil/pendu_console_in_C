/**
 *
 * Programme pour l'application du jeu du Pendu
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "header/pendu.h"
#include "header/stringPendu.h"

/**
 * Entree du programme.
 * \return EXIT_SUCCESS - Arret normal du programme.
 */
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    int partie = 0;
    char choix = 0;
    // Le Nom du jeux c'est Idriss Pendu (IP)
    printf("\n");
    logo();
    printf("\nBienvenue dans le Pendu !\n");

    do
    {
        printf("\nJouer une nouvelle partie ? (o/n) : ");
        scanf("%c", &choix);
        while (getchar() != '\n')
            ;

        if (choix == 'o' || choix == 'O')
        {
            partie = 1;
            loop_partie();
        }
        else if (choix == 'n' || choix == 'N')
            partie = 0;
        else
        {
            partie = -1;
            printf("%c n'est pas un choix valide !\n", choix);
        }
    } while (partie);

    printf("\nA une prochaine !\n");
    logo();
    return EXIT_SUCCESS;
}
