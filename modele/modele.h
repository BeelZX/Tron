#ifndef MODEL_H
#define MODEL_H

typedef struct {
    int x;// pos x de la moto
    int y;// pos y de la moto
    int direction;// direction (la ou il regarde haut droite bas gauche)
    int alive;// 1 si la moto est en vie, 0 sinon
} Moto;

typedef struct {
    int width;// largeur du plateau    
    int height;// hauteur du plateau
    char **grid;//tableau representant le ^plateau
} Plateau;

typedef struct {
    Moto moto;//la moto du joueur 
    int score;//son score
    char controls[4];//les touches directionnelles
} Joueur;

typedef struct {
    Plateau plateau;// plateau de jeu
    Joueur *joueurs;// tableau de joueurs
    int nb_joueurs;//nombre de joueurs
    int game_over;//1 si partie finie, 0 sinon
} Jeu;

#endif 
