#include "/model.h"
#include <stdlib.h>
#include <string.h>

Board init_board(int width, int height) {
    Board board;
    board.width = width;
    board.height = height;

    board.grid = malloc(height * sizeof(short *));
    for (int i = 0; i < height; i++) {
        board.grid[i] = calloc(width, sizeof(short));
    }
    return board;
}// Initialise le plateau

void free_board(Board *board) {
    for (int i = 0; i < board->height; i++) {
        free(board->grid[i]);
    }
    free(board->grid);
    board->grid = NULL;
}// libere la memoire du plateau

Player init_player(int x, int y, Direction direction, const char controls[4]) {
    Player player;
    player.bike.x = x;
    player.bike.y = y;
    player.bike.direction = direction;
    player.score = 0;
    player.isAlive = true;
    memcpy(player.bike.controls, controls, sizeof(char) * 4); // Les touches pour jouer

    return player;
}// Initialise le joueur

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
}// Deplacement de la moto

bool check_collision(){

}// Vérifie si il y a une collision avec le bord du plateau ou avec un obstacle

void leave_trace(){

}// la trace derriere la moto

Game init_game(){

}// Initialisation du jeu

bool check_game_over(Game *game) {

}// Vérifie si le jeu est fini

void free_game(Game *game) {
    free_board(&game->board);
    free(game->players);
    game->players = NULL;
}// libere la memoire du jeu