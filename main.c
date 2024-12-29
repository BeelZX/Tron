#include "./modele/modele.h"       // Pour le modèle
#include "./controleur/controleur.h" // Pour le contrôleur
#include "./vue/vue_ncurses.h" // La vue Ncurses
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h> // Pour usleep

void mainMenu() {
    int choice;
    char buffer[10]; // Tampon pour capturer l'entrée utilisateur

    while (1) {
        // Affichage du menu principal
        printf("=== Bienvenue dans Tron ===\n");
        printf("1. Jouer avec Ncurses\n");
        printf("2. Jouer avec SDL (non implémenté)\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");

        // Lire l'entrée utilisateur comme une chaîne
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Convertir la chaîne en entier
            if (sscanf(buffer, "%d", &choice) == 1) {
                // Vérifier si le choix est valide
                switch (choice) {
                    case 1: {
                        // Lancer Ncurses
                        initscr();
                        cbreak();
                        noecho();
                        keypad(stdscr, TRUE);
                        curs_set(0);
                        while (1) {
                            int start_choice = displayMenuStart(); // Menu de démarrage Ncurses
                            if (start_choice == 1) { // Quitter
                                endwin();
                                return;
                            } else if (start_choice == 2) { // SDL depuis Ncurses
                                endwin();
                                printf("Jouer avec SDL n'est pas encore implémenté.\n");
                                return;
                            } else if (start_choice == 0) { // Jouer
                                Game *game = init_game(30, 20); // Initialisation du jeu
                                initGame(game);         // Lancement du jeu avec Ncurses

                                // Affichage du menu de redémarrage
                                int restart_choice = displayMenuReStart();
                                if (restart_choice == 0) { // Rejouer
                                    free_game(game);
                                    clear();
                                    continue; // Retourne au menu startMenu
                                } else if (restart_choice == 1) { // SDL
                                    endwin();
                                    printf("\nJouer avec SDL n'est pas encore implémenté.\n");
                                    free_game(game);
                                    return;
                                } else if (restart_choice == 2) { // Quitter
                                    free_game(game);
                                    endwin();
                                    return;
                                }
                            }
                        }
                        break;
                    }
                    case 2:
                        printf("Jouer avec SDL n'est pas encore implémenté.\n");
                        break;
                    case 3:
                        printf("Au revoir !\n");
                        return;
                    default:
                        printf("Choix invalide. Veuillez réessayer.\n");
                        break;
                }
            } else {
                // Si l'entrée n'est pas un entier, afficher une erreur
                printf("Entrée invalide. Veuillez entrer un chiffre.\n");
            }
        } else {
            // Problème de lecture de l'entrée
            printf("Erreur de lecture de l'entrée. Veuillez réessayer.\n");
            clearerr(stdin); // Réinitialiser l'état d'erreur
        }
    }
}


int main() {
    mainMenu();
    return 0;
}

