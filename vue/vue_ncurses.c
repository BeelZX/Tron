#include "vue_ncurses.h"

// Menu principal avec les options de démarrage
int displayMenuStart() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);  // getch() ne bloque pas
    curs_set(0);            // Cache le curseur

    const char *options[] = {"Jouer", "Quitter", "Choisir SDL"};
    int n_options = 3;  // Nombre d'options
    int choice = 0;     // Choix de l'utilisateur
    int ch;             // Caractère entré par l'utilisateur

    while (1) {
        mvprintw(2, 10, "=== Bienvenue dans Tron ===");
        for (int i = 0; i < n_options; i++) {
            if (i == choice) {
                attron(A_REVERSE);  // Mettre en surbrillance l'option sélectionnée
                mvprintw(5 + i, 10, "%s", options[i]);
                attroff(A_REVERSE);
            } else {                // Sinon, afficher l'option normalement
                mvprintw(5 + i, 10, "%s", options[i]);
            }
        }
        refresh();

        ch = getch();               // Attendre une entrée utilisateur
        switch (ch) {
            case KEY_UP:            // Flèche haut
                choice = (choice - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:          // Flèche bas
                choice = (choice + 1) % n_options;
                break;
            case '\n':              // Touche Entrée
                return choice;
        }
    }
}

// Menu affiché à la fin de la partie
int displayMenuReStart() {
    const char *options[] = {"Rejouer", "Jouer sous SDL", "Quitter"};
    int n_options = 3;  // Nombre d'options
    int choice = 0;     // Choix de l'utilisateur
    int ch;             // Caractère entré par l'utilisateur

    while (1) {
        mvprintw(2, 10, "=== Partie Terminée ===");
        for (int i = 0; i < n_options; i++) {
            if (i == choice) {
                attron(A_REVERSE);      // Mettre en surbrillance l'option sélectionnée
                mvprintw(5 + i, 10, "%s", options[i]);
                attroff(A_REVERSE);
            } else {                    // Sinon, afficher l'option normalement
                mvprintw(5 + i, 10, "%s", options[i]);
            }
        }
        refresh();

        ch = getch();           // Attendre une entrée utilisateur
        switch (ch) {
            case KEY_UP:        // Flèche haut
                choice = (choice - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:      // Flèche bas
                choice = (choice + 1) % n_options;
                break;
            case '\n':          // Touche Entrée
                return choice;
        }
    }
}

// Affiche le plateau de jeu et les joueurs
void display_board(Game *game) {
    start_color();                              // Initialiser les couleurs
    init_pair(1, COLOR_RED, COLOR_BLACK);       // Pour la bordure
    init_pair(2, COLOR_GREEN, COLOR_BLACK);     // Pour les motos

    Board *board = game->board;
    int x_offset = 2;                           // Décalage horizontal pour ajouter de la marge
    int y_offset = 2;                           // Décalage vertical pour ajouter de la marge

    clear();                                    // Efface l'écran avant de redessiner

    // Dessine les bords du plateau
    for (int y = -1; y <= board->height; y++) {                             // -1 pour la bordure supérieure
        for (int x = -1; x <= board->width; x++) {                          // -1 pour la bordure gauche
            if (y == -1 || y == board->height || x == -1 || x == board->width) { 
                attron(COLOR_PAIR(1));                                      // Mettre en surbrillance la bordure
                mvprintw(y + y_offset + 1, x + x_offset + 1, "+ ");         // Dessine la bordure
                attroff(COLOR_PAIR(1));                                     // Arrête de mettre en surbrillance la bordure
            }
        }
    }   

    // Affiche le plateau
    for (int y = 0; y < board->height; y++) {                       // On commence à 0 pour éviter les bords
        for (int x = 0; x < board->width; x++) { 
            if (board->grid[y][x] == 0)                             // Si la case est vide
                mvprintw(y + y_offset + 1, x + x_offset + 1, " ");  // Affiche un espace
            else 
                mvprintw(y + y_offset + 1, x + x_offset + 1, "#");  // Affiche la trace de la moto
        }
    }

    // Affiche les motos des joueurs
    for (int i = 0; i < game->nbPlayers; i++) {
        Player *player = game->players[i];
        if (player->isAlive) {
            attron(COLOR_PAIR(2));                                                              // Mettre en surbrillance les motos
            mvprintw(player->bike->y + y_offset + 1, player->bike->x + x_offset + 1, "O");      // Affiche la moto
            attroff(COLOR_PAIR(2));                                                             // Arrête de mettre en surbrillance les motos
        }
    }

    refresh(); // Met à jour l'affichage
}


// Initialisation du jeu
void initGame(Game *game) {
        
    // Boucle principale
    while (!game->isGameOver) {
        handle_input(game);                                 // Gère les entrées utilisateur

        // Déplace les motos et met à jour le plateau
        for (int i = 0; i < game->nbPlayers; i++) {
            Player *player = game->players[i];
            if (player->isAlive) {
                leave_trace(game->board, player->bike);     // Laisse une trace
                move_bike(player->bike);                    // Déplace la moto
                if (check_collision(game->board, player->bike)) {
                    player->isAlive = false;                // Collision détectée
                }
                // Mise à jour du score si le joueur est en vie
                if (player->isAlive) {
                    player->score++;
                }
            }
        }

        game->isGameOver = check_game_over(game);           // Vérifie si le jeu est terminé

        display_board(game);                                // Affiche le plateau mis à jour
        displayScore(game);

        usleep(100000);                                     // Pause pour ralentir le jeu (100 ms)
    }

    int winner = check_game_over(game);
    displayWinner(game);
    endwin();                                               // Ferme la fenêtre ncurses
}

// Affiche le score des joueurs en haut a droite de l'écran
void displayScore(Game *game) {
    int x = game->board->width + 10;                        // Afficher à droite du plateau
    mvprintw(0, x, "Scores :");
    for (int i = 0; i < game->nbPlayers; i++) {
        mvprintw(1 + i, x, "Joueur %d: %d", i + 1, game->players[i]->score);
    }
}

// Trouve le gagnant en fonction des scores
int findWinner(Game *game, int *maxScore, bool *tie) {
    int winner = -1;                                        // Aucun gagnant
    *maxScore = -1;                                         // Score maximum
    *tie = false;                                           // Pas de match nul

    for (int i = 0; i < game->nbPlayers; i++) {
        if (game->players[i]->score > *maxScore) {
            *maxScore = game->players[i]->score;             // Mise à jour du score maximum
            winner = i;
            *tie = false;
        } else if (game->players[i]->score == *maxScore) {  // Egalité
            *tie = true;
        }
    }
    return winner;
}

// Affiche le gagnant ou une égalité
void displayWinner(Game *game) {
    clear();
    int maxScore;
    bool tie;
    
    // Trouver le gagnant
    int winnerIndex = findWinner(game, &maxScore, &tie);

    // Afficher le résultat
    if (tie) {
        mvprintw(10, 10, "Egalite : Aucun gagnant !");
    } else {
        mvprintw(10, 10, "Le joueur %d a gagne avec un score de %d !", winnerIndex + 1, maxScore);
    }

    mvprintw(12, 10, "Appuyez sur une touche pour continuer...");
    refresh();
    getch();                                                    // Attente d'une touche
}

void loopGame(){
    // Lancer Ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    while (1) {
        int start_choice = displayMenuStart();                  // Menu de démarrage Ncurses
        if (start_choice == 1) {                                // Quitter
            endwin();
            return;
        } else if (start_choice == 2) {                         // SDL depuis Ncurses
            sdlInitia();
            clear();
            return;
        } else if (start_choice == 0) {                         // Jouer
            Game *game = init_game(20, 20);                     // Initialisation du jeu
            initGame(game);                                     // Lancement du jeu avec Ncurses

            // Affichage du menu de redémarrage
            int restart_choice = displayMenuReStart();
            if (restart_choice == 0) {                          // Rejouer
                free_game(game);
                clear();
                continue;                                       // Retourne au menu startMenu
            } else if (restart_choice == 1) {                   // SDL
                sdlInitia();
                free_game(game);
                endwin();
                return;
            } else if (restart_choice == 2) {                   // Quitter
                free_game(game);
                endwin();
                return;
            }
        }
    }
}