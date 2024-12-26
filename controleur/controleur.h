#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdbool.h>
#include "../modele/modele.h"

// Gère les entrées utilisateur et met à jour les directions des joueurs
void handle_input(Game *game);

// Vérifie si une touche correspond aux contrôles d’un joueur
bool is_valid_input(char input, const char controls[4]);

#endif