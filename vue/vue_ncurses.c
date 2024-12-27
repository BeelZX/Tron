#include "vue_ncurses.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // Pour usleep
#include "../modele/modele.h"
#include "../controleur/controleur.h"
#include <ncurses.h>
// Menu start
int displayMenuStart() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // getch() ne bloque pas
    curs_set(0); // Cache le curseur

    const char *options[] = {"Jouer", "Quitter", "Choisir SDL"};
    int n_options = 3;
    int choice = 0;
    int ch;

    while (1) {
        clear();
        mvprintw(2, 10, "=== Bienvenue dans Tron ===");
        for (int i = 0; i < n_options; i++) {
            if (i == choice) {
                attron(A_REVERSE); // Mettez en surbrillance l'option sélectionnée
                mvprintw(5 + i, 10, "%s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(5 + i, 10, "%s", options[i]);
            }
        }
        refresh();

        ch = getch();
        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % n_options;
                break;
            case '\n': // Touche Entrée
                return choice;
        }
    }
}

int displayMenuReStart() {
    const char *options[] = {"Rejouer", "Jouer sous SDL", "Quitter"};
    int n_options = 3;
    int choice = 0;
    int ch;

    while (1) {
        clear();
        mvprintw(2, 10, "=== Partie Terminée ===");
        for (int i = 0; i < n_options; i++) {
            if (i == choice) {
                attron(A_REVERSE); // Mettez en surbrillance l'option sélectionnée
                mvprintw(5 + i, 10, "%s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(5 + i, 10, "%s", options[i]);
            }
        }
        refresh();

        ch = getch();
        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % n_options;
                break;
            case '\n': // Touche Entrée
                return choice;
        }
    }
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

void initGame(Game *game) {

    // Boucle principale
    while (!game->isGameOver) {
        handle_input(game); // Gère les entrées utilisateur

        // Déplace les motos et met à jour le plateau
        for (int i = 0; i < game->nbPlayers; i++) {
            Player *player = game->players[i];
            if (player->isAlive) {
                leave_trace(game->board, player->bike); // Laisse une trace
                move_bike(player->bike); // Déplace la moto
                if (check_collision(game->board, player->bike)) {
                    player->isAlive = false; // Collision détectée
                }
                // Mise à jour du score si le joueur est en vie
                if (player->isAlive) {
                    player->score++;
                }
            }
        }

        game->isGameOver = check_game_over(game); // Vérifie si le jeu est terminé

        // Affiche le plateau mis à jour
        display_board(game);
        displayScore(game);

        usleep(100000); // Pause pour ralentir le jeu (100 ms)
    }
    int winner = check_game_over(game);
    displayWinner(winner);
    // Fin de Ncurses
    endwin();
}

void displayScore(Game *game) {
    int x = game->board->width + 5; // Afficher à droite du plateau
    mvprintw(0, x, "Scores :");
    for (int i = 0; i < game->nbPlayers; i++) {
        mvprintw(1 + i, x, "Joueur %d: %d", i + 1, game->players[i]->score);
    }
    refresh();
}

void displayWinner(int winner) {
    clear();
    if (winner != -1) {
        mvprintw(10, 10, "Le joueur %d a gagne !", winner + 1);
    } else {
        mvprintw(10, 10, "Egalite : Aucun gagnant !");
    }
    mvprintw(12, 10, "Appuyez sur une touche pour continuer...");
    refresh();
    getch(); // Attente d'une touche
}
