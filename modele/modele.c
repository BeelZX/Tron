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
    board->grid = (int **) malloc(height * sizeof(short *));
    if(!board->grid) exit(EXIT_FAILURE);
    for (int i = 0; i < height; i++) {
        board->grid[i] = (int *) calloc(width, sizeof(short));
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
    player->bike->direction = (char *) malloc(sizeof(char) * 4);
    if(!player->bike->direction) exit(EXIT_FAILURE);
    memcpy(player->bike->controls, controls, sizeof(char) * 4);         // Copie des touches pour jouer dans le tableau de bike
    return player;
}

// Initialise le jeu
Game *init_game(int boardWidth, int boardHeight){
    Game *game = (Game *) malloc(sizeof(game));
    if(!game) exit(EXIT_FAILURE);
    game->nbPlayers = 2;
    game->isGameOver = false;
    game->players = (Player **) malloc(sizeof(Player) * game->nbPlayers);
    if(!game->players) exit(EXIT_FAILURE);
    game->board = (Board *) init_board(boardWidth, boardHeight);
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
        free(players[i]);
    }
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
        case RIGHT:
            bike->x++;
            break;
        case DOWN:
            bike->y++;
            break;
        case LEFT:
            bike->x--;
            break;
    }
}

// Change la direction de la moto, retourne true si changement possible et fait, false sinon
bool change_direction(Bike *bike, Direction direction) {
    
}

// Vérifie s'il y a une collision avec le bord du plateau ou avec un obstacle
bool check_collision(){

}

// Place une trace derrière la moto sur le plateau
void leave_trace(){

}

// Vérifie si le jeu est fini
bool check_game_over(Game *game) {

}