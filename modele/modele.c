#include "./modele.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

// Initialise le plateau
Board *init_board(int width, int height) {
    Board *board = malloc(sizeof(Board));
    if(!board) exit(EXIT_FAILURE);
    board->width = width;
    board->height = height;
    board->grid = malloc(height * sizeof(short *));
    if(!board->grid) exit(EXIT_FAILURE);
    for (int i = 0; i < height; i++) {
        board->grid[i] = calloc(width, sizeof(short));
        if(!board->grid[i]) exit(EXIT_FAILURE);
    }
    return board;
}

// Initialise le joueur
Player *init_player(int x, int y, Direction direction, const char controls[4]) {
    Player *player = (Player *) malloc(sizeof(Player));
    if(!player) exit(EXIT_FAILURE);
    player->bike = (Bike *) malloc(sizeof(Bike));
    if(!player->bike) exit(EXIT_FAILURE);
    player->bike->x = x;
    player->bike->y = y;
    player->bike->direction = direction;
    player->score = 0;
    player->isAlive = true;
    memcpy(player->bike->controls, controls, sizeof(char) * 4);         // Copie des touches pour jouer dans le tableau de bike
    return player;
}

// Initialise le jeu
Game *init_game(int boardWidth, int boardHeight){
    Game *game = (Game *) malloc(sizeof(Game));
    if(!game) exit(EXIT_FAILURE);

    game->nbPlayers = 2;
    game->isGameOver = false;

    game->board = (Board *) init_board(boardWidth, boardHeight);

    game->players = (Player **) malloc(sizeof(Player *) * game->nbPlayers);
    if(!game->players) exit(EXIT_FAILURE);
    game->players[0] = init_player(1, 1, RIGHT, (char[]){'z', 'd', 's', 'q'}); // Joueur 1
    game->players[1] = init_player(boardWidth - 2, boardHeight - 2, LEFT, (char[]){'i', 'l', 'k', 'j'});  // Joueur 2   
    return game;
}

// Libère la mémoire allouée pour le plateau
void free_board(Board *board) {
    for (int i = 0; i < board->height; i++) {
        free(board->grid[i]);
    }
    free(board->grid);
    free(board);
}

// Libère la mémoire allouée pour tous les joueurs
void free_players(Player **players, int nb_players) {
    for (int i = 0; i < nb_players; i++) {
        free(players[i]->bike);
        free(players[i]);
    }
    free(players);
}

// Libère la mémoire allouée pour le jeu
void free_game(Game *game) {
    free_board(game->board);
    free_players(game->players, game->nbPlayers);
    free(game);
}

// Déplacement de la moto
void move_bike(Bike *bike) {
    switch (bike->direction) {
        case UP:
            bike->y--;
            break;
        case DOWN:
            bike->y++;
            break;
        case LEFT:
            bike->x--;
            break;
        case RIGHT:
            bike->x++;
            break;
    }
}

// Change la direction de la moto, retourne true si changement possible et fait, false sinon
bool change_direction(Bike *bike, Direction newDirection) {
    if ((bike->direction == UP && newDirection == DOWN) ||
        (bike->direction == DOWN && newDirection == UP) ||
        (bike->direction == LEFT && newDirection == RIGHT) ||
        (bike->direction == RIGHT && newDirection == LEFT)) {
        return false;
    }
    bike->direction = newDirection;
    return true;
}

// Vérifie s'il y a une collision avec le bord du plateau ou avec un obstacle
bool check_collision(Board *board, Bike *bike){
    if (bike->x < 0 || bike->x >= board->width || bike->y < 0 || bike->y >= board->height) {
        return true; // Collision avec les bords
    }
    if (board->grid[bike->y][bike->x] != 0) {
        return true; // Collision avec une trace
    }
    return false;
}

// Place une trace derrière la moto sur le plateau
void leave_trace(Board *board, Bike *bike){
    board->grid[bike->y][bike->x] = 1;
}

// Vérifie si le jeu est fini, si c'est fini retourne l'index dans le tableau du joueur qui a gagné, sinon retourne -1
int check_game_over(Game *game) {
    for (int i = 0; i < game->nbPlayers; i++) {
        if (game->players[i]->isAlive) {
            return i;
        }
    }
    return -1;
}