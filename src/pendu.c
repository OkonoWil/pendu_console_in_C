#include "header/pendu.h"

/**
 *Lit et retourne le premier caractere saisie par l'utilisateur (Transforme en majuscule)
 */
char lireCaractere()
{
    char caractere = toupper(getchar());

    while (getchar() != '\n')
        ;

    return caractere;
}

/**
 * Renvoie un mot choisi au hazard dans le DICTIONNAIRE
 */
char *mot_Mystere()
{
    FILE *dico = NULL;
    char mot[TAILLE_MAX_CHAINE] = "";

    if ((dico = fopen(DICTIONNAIRE, "r")) != NULL)
    {
        char ligne[TAILLE_MAX_CHAINE] = "";
        int nb_ligne = 0;
        int ligneChoisi = 0;

        srand(time(NULL));

        while (fgets(ligne, TAILLE_MAX_CHAINE, dico) != NULL)
            nb_ligne++;

        rewind(dico);
        ligneChoisi = rand() % nb_ligne;

        while (ligneChoisi && fgets(ligne, TAILLE_MAX_CHAINE, dico) != NULL)
            ligneChoisi--;

        fgets(mot, TAILLE_MAX_CHAINE, dico);

        fclose(dico);
    }
    else
    {
        printf("Impossible d'ouvire le fichier %s", DICTIONNAIRE);
    }

    char *buffer = malloc(strlen(mot)); // On enleve la place du '\n'

    if (buffer != NULL)
        strcpy(buffer, mot);

    buffer[strlen(mot) - 1] = '\0'; // On remplace \n par \0 la chaine

    return buffer;
}

/**
 * \brief Boucle de deroulement d'une partie de pendu
 *
 */
void loop_partie()
{
    char choix = 0;
    int coup = 5;

    do
    {
        printf("\nMode disponible :\n");
        printf("\t1 - Solo\n");
        printf("\t2 - Duo\n");
        printf("\tq - Exit\n");
        printf("Quel mode voulez-vous ? ");
        scanf("%c", &choix);
        while (getchar() != '\n')
            ;

        if (choix == '1')
        { // Mode solo
            printf("\nVous commencer un nouvelle partie solo !\n");
            choix = 'q';
            char saisieJoueur = 0;
            char *motMystere = mot_Mystere(); // Creation du mot mystere
            char motJoueur[strlen(motMystere) + 1];
            motJoueur[0] = '\0';

            for (unsigned int i = 0; i < strlen(motMystere); i++)
                strcat(motJoueur, "_");

            motJoueur[strlen(motJoueur)] = '\0'; // Creation du mot joueur

            while (coup && strcmp(motJoueur, motMystere))
            {
                printf("\nIl vous reste %d coups a jouer\n", coup);
                printf("Quel est le mot secret ? %s\n", motJoueur);
                printf("Proposez une lettre : ");
                saisieJoueur = lireCaractere();
                coup -= verifie_lettre(motMystere, motJoueur, saisieJoueur);
                printf("\n");
                affichage_pendu(coup);
            }

            if (coup)
                printf("\nGagne ! Le mot secret etait bien : %s ( %s ) !\n", motMystere, motJoueur);
            else
                printf("\nPerdu ! Vous n'avez plus de coup a jouer. Le mot secret etait : %s ( %s ) !\n", motMystere, motJoueur);

            if (motMystere != NULL)
                free(motMystere);
        }
        else if (choix == '2')
        { // Mode duo
            printf("\nVous commencer un nouvelle partie duo !\n");
            choix = 'q';
            char saisieJoueur = 0;
            char motMystere[TAILLE_MAX_CHAINE];
            printf("\nJoueur 1 choisir le mot a trouver (%d caractere max): ", TAILLE_MAX_CHAINE);
            fgets(motMystere, TAILLE_MAX_CHAINE, stdin);
            motMystere[strlen(motMystere) - 1] = '\0';
            str_toupper(motMystere);

            char motJoueur[strlen(motMystere) + 1];
            motJoueur[0] = '\0';

            for (unsigned int i = 0; i < strlen(motMystere); i++)
                strcat(motJoueur, "_");

            motJoueur[strlen(motJoueur)] = '\0'; // Creation du mot joueur
            clear_term();

            while (coup && strcmp(motJoueur, motMystere))
            {
                printf("\nJoueur 2 Il vous reste %d coups a jouer\n", coup);
                printf("Quel est le mot secret ? %s\n", motJoueur);
                printf("Proposez une lettre : ");
                saisieJoueur = lireCaractere();
                coup -= verifie_lettre(motMystere, motJoueur, saisieJoueur);
                printf("\n");
                affichage_pendu(coup);
            }

            if (coup)
                printf("\nGagnant Joueur 2 ! Le mot secret etait bien : %s ( %s ) !\n", motMystere, motJoueur);
            else
                printf("\nGagnant Joueur 1 ! Joueur 2, vous n'avez plus de coup a jouer. Le mot secret etait : %s ( %s ) !\n", motMystere, motJoueur);
        }
        else if (choix == 'q')
            ;
        else
        {
            choix = -1;
            printf("%c n'est pas un choix valide !\n", choix);
        }

    } while (choix != 'q');
}

/**
 * Vide l'affichage du termnial
 *
 */
void clear_term()
{
#ifdef _WIN32
    system("cls");
#elif defined(unix) || defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
#else
#error "OS not supported."
#endif
}

/**
 * Affiche du logo du jeux
 *
 */
void logo()
{
    printf(" _____  _____ \n");
    printf("|_   _||  __ \\\n");
    printf("  | |  | |__) |\n");
    printf("  | |  |  ___/ \n");
    printf(" _| |_ | |   \n");
    printf("|_____||_| \n");
}

/**
 * Affiche un pendu suivant l'etat de la partie
 *
 */
void affichage_pendu(int x)
{
    if (x == 5)
    {
        printf("\t======\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t=============\n");
    }
    else if (x == 4)
    {
        printf("\t===========\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t=============\n");
    }
    else if (x == 3)
    {
        printf("\t===========\n");
        printf("\t ||\n");
        printf("\t ||\t 0\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t=============\n");
    }
    else if (x == 2)
    {
        printf("\t===========\n");
        printf("\t ||\n");
        printf("\t ||\t 0\n");
        printf("\t ||\t/|\\\n");
        printf("\t ||\n");
        printf("\t ||\n");
        printf("\t=============\n");
    }
    else if (x == 1)
    {
        printf("\t===========\n");
        printf("\t ||\n");
        printf("\t ||\t 0\n");
        printf("\t ||\t/|\\\n");
        printf("\t ||\t/ \\\n");
        printf("\t ||\n");
        printf("\t=============\n");
    }
    else if (x == 0)
    {
        printf("\t===========\n");
        printf("\t ||\t |\n");
        printf("\t ||\t 0\n");
        printf("\t ||\t/|\\\n");
        printf("\t ||\t/ \\\n");
        printf("\t ||\n");
        printf("\t=============\n");
    }
}