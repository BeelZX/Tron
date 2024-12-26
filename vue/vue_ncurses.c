#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../modele/modele.h"
#include <ncurses.h>

// Affiche le menu principal pour la version Ncurses
bool displayMenu() {

}

// Affiche le plateau de jeu et les joueurs
void display_board(Game *game) {
    Board *board = game->board;
    clear(); // Efface l'écran avant de redessiner

    // Affiche le plateau
    for (int y = 0; y < board->height; y++) {
        for (int x = 0; x < board->width; x++) {
            if (board->grid[y][x] == 0)
                mvprintw(y, x, " "); // Case vide
            else
                mvprintw(y, x, "#"); // Mur de lumière
        }
    }

    // Affiche les joueurs
    for (int i = 0; i < game->nbPlayers; i++) {
        Player *player = game->players[i];
        if (player->isAlive) {
            mvprintw(player->bike->y, player->bike->x, "O"); // Moto des joueurs
        }
    }

    refresh(); // Met à jour l'affichage
}
