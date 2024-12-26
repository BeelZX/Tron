#include "./modele/modele.h"       // Pour le modèle
#include "./controleur/controleur.h" // Pour le contrôleur
#include "./vue/vue_ncurses.h" // La vue Ncurses
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h> // Pour usleep

int main() {
    // Initialisation du jeu
    Game *game = init_game(20, 15);

    // Initialisation de Ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE); // getch() ne bloque pas
    curs_set(0); // Cache le curseur

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
            }
        }

        game->isGameOver = check_game_over(game); // Vérifie si le jeu est terminé

        // Affiche le plateau mis à jour
        display_board(game);

        usleep(100000); // Pause pour ralentir le jeu (100 ms)
    }

    // Fin de Ncurses
    endwin();

    // Libération de la mémoire
    free_game(game);

    return 0;
}


