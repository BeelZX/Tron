#include "./modele/modele.h"       
#include "./controleur/controleur.h"
#include "./vue/vue_ncurses.h"
#include "./vue/vue_sdl.h"
void mainMenu() {
    int choice;
    char buffer[10];                                // Tampon pour capturer l'entrée utilisateur

    while (1) {
        // Affichage du menu principal
        printf("=== Bienvenue dans Tron ===\n");
        printf("1. Jouer avec Ncurses\n");
        printf("2. Jouer avec SDL\n");
        printf("3. Quitter\n");
        printf("Votre choix : ");

        // Lire l'entrée utilisateur comme une chaîne
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            // Convertir la chaîne en entier
            if (sscanf(buffer, "%d", &choice) == 1) {
                // Vérifier si le choix est valide
                switch (choice) {
                    case 1: {
                        loopGame();
                        break;
                    }
                    case 2:
                        sdlInitia();
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


int main(int argc, char *argv[]) {
    mainMenu();
    return 0;
}

