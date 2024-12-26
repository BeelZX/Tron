#include "./controleur.h"
#include <ncurses.h>

// Gère les entrées utilisateur
void handle_input(Game *game) {
    int ch = getch();  // Lire une touche pressée
    for (int i = 0; i < game->nbPlayers; i++) {
        Player *player = game->players[i];
        if (!player->isAlive) continue;
        Bike *bike = player->bike;
        if (is_valid_input(ch, bike->controls)) {
            // Associe l'entrée utilisateur à une direction
            if (ch == bike->controls[0]) change_direction(bike, UP);
            else if (ch == bike->controls[1]) change_direction(bike, RIGHT);
            else if (ch == bike->controls[2]) change_direction(bike, DOWN);
            else if (ch == bike->controls[3]) change_direction(bike, LEFT);
        }
    }
}



// Vérifie si une touche correspond aux contrôles d’un joueur
bool is_valid_input(char input, const char controls[4]) {
    for (int i = 0; i < 4; i++) {
        if (input == controls[i]) {
            return true;
        }
    }
    return false;
}

