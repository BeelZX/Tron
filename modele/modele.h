#ifndef MODEL_H
#define MODEL_H
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h> // Pour usleep

// Définition des directions possibles pour la moto
typedef enum {
    UP = 0,                 // Vers le haut
    DOWN = 1,               // Vers le bas
    LEFT = 2,               // Vers la gauche
    RIGHT = 3               // Vers la droite
} Direction;

// Structure représentant une moto
typedef struct {
    int x;                  // Position x de la moto
    int y;                  // Position y de la moto
    Direction direction;    // Direction (haut, bas, gauche, ou droite)
    char controls[4];       // Les touches directionnelles
} Bike;

// Structure représentant le plateau de jeu
typedef struct {
    int width;              // Largeur du plateau  
    int height;             // Hauteur du plateau
    short **grid;           // Tableau a deux dimensions représentant les cases du plateau
} Board;

// Structure représentant un joueur
typedef struct {
    Bike *bike;             // La moto du joueur 
    int score;              // Le score du joueur
    bool isAlive;           // True si la moto est en vie, false sinon
} Player;

// Structure représentant l'état du jeu
typedef struct {
    Board *board;            // Plateau du jeu
    Player **players;        // Tableau contenant tous les joueurs
    int nbPlayers;          // Nombre de joueurs
    bool isGameOver;        // True si partie est finie, false sinon
} Game;

Board *init_board(int width, int height);
Player *init_player(int x, int y, Direction direction, const char controls[4]);
Game *init_game(int boardWidth, int boardHeight);
void free_board(Board *board);
void free_players(Player **players, int nb_players);
void free_game(Game *game);
void move_bike(Bike *bike);
bool change_direction(Bike *bike, Direction newDirection);
bool check_collision(Board *board, Bike *bike);
void leave_trace(Board *board, Bike *bike);
int check_game_over(Game *game);
int check_game_over_(Game *game);
#endif 