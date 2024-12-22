#include <stdbool.h>

#ifndef MODEL_H
#define MODEL_H

typedef struct {
    int x;              // Position x de la moto
    int y;              // Position y de la moto
    int direction;      // Direction (haut, bas, gauche, ou droite)
    char controls[4];   // Les touches directionnelles
} Bike;

typedef struct {
    int width;          // Largeur du plateau  
    int height;         // Hauteur du plateau
    short **grid;       // Tableau représentant le plateau
} Board;

typedef struct {
    Bike bike;          // La moto du joueur 
    int score;          // Le score du joueur
    bool IsAlive;       // True si la moto est en vie, false sinon
} Player;

typedef struct {
    Board board;        // Plateau du jeu
    Player *players;    // Tableau contenant tous les joueurs
    int nbPlayers;      // Nombre de joueurs
    bool isGameOver;    // True si partie est finie, false sinon
} Game;

#endif 