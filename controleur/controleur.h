#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdbool.h>
#include "../modele/modele.h"

void handle_input(Game *game);
bool is_valid_input(char input, const char controls[4]);

#endif