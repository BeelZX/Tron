#ifndef VUE_NCURSES_H
#define VUE_NCURSES_H

#include "../modele/modele.h"
int displayMenuStart();
int displayMenuReStart();
void display_board(Game *game);
void initGame(Game *game);
void displayWinner(int winner);
void displayScore(Game *game);

#endif // VUE_NCURSES_H
