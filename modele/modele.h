#include <stdbool.h>

#ifndef MODEL_H
#define MODEL_H

typedef struct {
    int x;              // position x de la moto
    int y;              // position y de la moto
    int direction;      // direction (haut, bas, gauche, ou droite)
    char controls[4];   // les touches directionnelles
} Bike;

typedef struct {
    int width;          // largeur du plateau  
    int height;         // hauteur du plateau
    short **grid;       // tableau représentant le plateau
} Board;

typedef struct {
    Bike bike;          // la moto du joueur 
    int score;          // le score du joueur
    bool IsAlive;       // true si la moto est en vie, false sinon
} Player;

typedef struct {
    Board board;        // plateau du jeu
    Player *players;    // tableau contenant tous les joueurs
    int nbPlayers;      // nombre de joueurs
    bool isGameOver;    // true si partie est finie, false sinon
} Game;

#endif 