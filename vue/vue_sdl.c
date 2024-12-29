#include "./vue_sdl.h"

// Affiche du texte sur une fenêtre SDL aux coordonnées choisi
void sdl_DisplayText(SDL_Surface* surface, TTF_Font *font, char *text, SDL_Color color, int x, int y) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, text, color);
    SDL_Rect rect = {x, y, textSurface->w, textSurface->h};
    SDL_BlitSurface(textSurface, NULL, surface, &rect);
    SDL_FreeSurface(textSurface);
}

// Initialise SDL
void init_SDL(SDL_Window **window, SDL_Surface **surface) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    *window = SDL_CreateWindow("Tron", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN);
    *surface = SDL_GetWindowSurface(*window);
}

// Affiche le menu principal
int sdl_DisplayMenuStart(SDL_Window *window, SDL_Surface* screenSurface) {
    bool quit = false;
    SDL_Event event;
    SDL_Point cursor;
    SDL_Rect rect = {415, 200, 225, 90};
    SDL_Rect rect2 = {415, 340, 225, 90};
    SDL_Rect rect3 = {415, 480, 225, 90};
    TTF_Font *font = TTF_OpenFont("./vue/georgia.ttf", 60);
    // Affiche les choix
    SDL_FillRect(screenSurface, NULL, 0xC70039);
    SDL_FillRect(screenSurface, &rect, 0xe7e7e7);
    SDL_FillRect(screenSurface, &rect2, 0xe7e7e7);
    SDL_FillRect(screenSurface, &rect3, 0xe7e7e7);
    sdl_DisplayText(screenSurface, font, "Jouer", (SDL_Color) {0, 0, 0, 255}, rect.x+35, rect.y+5);
    sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {0, 0, 0, 255}, rect2.x+5, rect2.y+5);
    sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {0, 0, 0, 255}, rect3.x+12, rect3.y+5);
    SDL_UpdateWindowSurface(window);
    while(!quit) {
        SDL_FillRect(screenSurface, NULL, 0xC70039);
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEMOTION:
                    cursor.x = event.motion.x;
                    cursor.y = event.motion.y;
                    // Vérifie si le curseur est au dessus d'un des boutons, si oui l'assombrit
                    if(SDL_PointInRect(&cursor, &rect)) {
                        SDL_Rect rectSelect = {rect.x-10, rect.y-10, rect.w+20, rect.h+20};
                        SDL_FillRect(screenSurface, &rectSelect, 0x000000);
                        SDL_FillRect(screenSurface, &rect, 0x000000);
                        SDL_FillRect(screenSurface, &rect2, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect3, 0xe7e7e7);
                        sdl_DisplayText(screenSurface, font, "Jouer", (SDL_Color) {255, 255, 255, 255}, rect.x+35, rect.y+5);
                        sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {0, 0, 0, 255}, rect2.x+5, rect2.y+5);
                        sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {0, 0, 0, 255}, rect3.x+12, rect3.y+5);
                        SDL_UpdateWindowSurface(window);
                    } else if(SDL_PointInRect(&cursor, &rect2)) {
                        SDL_Rect rectSelect = {rect2.x-10, rect2.y-10, rect2.w+20, rect2.h+20};
                        SDL_FillRect(screenSurface, &rectSelect, 0x000000);
                        SDL_FillRect(screenSurface, &rect, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect2, 0x000000);
                        SDL_FillRect(screenSurface, &rect3, 0xe7e7e7);
                        sdl_DisplayText(screenSurface, font, "Jouer", (SDL_Color) {0, 0, 0, 255}, rect.x+35, rect.y+5);
                        sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {255, 255, 255, 255}, rect2.x+5, rect2.y+5);
                        sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {0, 0, 0, 255}, rect3.x+12, rect3.y+5);
                        SDL_UpdateWindowSurface(window);
                    } else if(SDL_PointInRect(&cursor, &rect3)) {
                        SDL_Rect rectSelect = {rect3.x-10, rect3.y-10, rect3.w+20, rect3.h+20};
                        SDL_FillRect(screenSurface, &rectSelect, 0x000000);
                        SDL_FillRect(screenSurface, &rect, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect2, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect3, 0x000000);
                        sdl_DisplayText(screenSurface, font, "Jouer", (SDL_Color) {0, 0, 0, 255}, rect.x+35, rect.y+5);
                        sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {0, 0, 0, 255}, rect2.x+5, rect2.y+5);
                        sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {255, 255, 255, 255}, rect3.x+12, rect3.y+5);
                        SDL_UpdateWindowSurface(window);
                    } else {
                        SDL_FillRect(screenSurface, &rect, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect2, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect3, 0xe7e7e7);
                        sdl_DisplayText(screenSurface, font, "Jouer", (SDL_Color) {0, 0, 0, 255}, rect.x+35, rect.y+5);
                        sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {0, 0, 0, 255}, rect2.x+5, rect2.y+5);
                        sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {0, 0, 0, 255}, rect3.x+12, rect3.y+5);
                        SDL_UpdateWindowSurface(window);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    cursor.x = event.motion.x;
                    cursor.y = event.motion.y;
                    if(SDL_PointInRect(&cursor, &rect)) {
                        TTF_CloseFont(font);
                        return 0;
                    } else if(SDL_PointInRect(&cursor, &rect2)) {
                        TTF_CloseFont(font);
                        return 1;
                    } else if(SDL_PointInRect(&cursor, &rect3)) {
                        TTF_CloseFont(font);
                        return 2;
                    }
                    break;
            }
        }
    }
}

// Affiche le menu pour recommencer
int sdl_DisplayMenuRestart(SDL_Window *window, SDL_Surface *screenSurface, int score, char *winner) {
    bool quit = false;
    SDL_Event event;
    SDL_Point cursor;
    SDL_Rect rect = {415, 200, 225, 90};
    SDL_Rect rect2 = {415, 340, 225, 90};
    SDL_Rect rect3 = {415, 480, 225, 90};
    TTF_Font *font = TTF_OpenFont("./vue/georgia.ttf", 60);
    char win[1000] = "Le gagnant est: ";
    strcat(win, winner);
    char score_[1000] = "Score: ";
    char nb[1000];
    strcat(score_, SDL_itoa(score, nb, 10));
    // Affichage des choix, score et nom du gagnant s'il y a, sinon affiche pour le gagnant "Personne"
    SDL_FillRect(screenSurface, NULL, 0xC70039);
    SDL_FillRect(screenSurface, &rect, 0xe7e7e7);
    SDL_FillRect(screenSurface, &rect2, 0xe7e7e7);
    SDL_FillRect(screenSurface, &rect3, 0xe7e7e7);
    sdl_DisplayText(screenSurface, font, win, (SDL_Color) {255, 255, 255, 255}, 40, 60);
    sdl_DisplayText(screenSurface, font, score_, (SDL_Color) {255, 255, 255, 255}, 40, 620);
    sdl_DisplayText(screenSurface, font, "Rejouer", (SDL_Color) {0, 0, 0, 255}, rect.x+7, rect.y+5);
    sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {0, 0, 0, 255}, rect2.x+5, rect2.y+5);
    sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {0, 0, 0, 255}, rect3.x+12, rect3.y+5);
    SDL_UpdateWindowSurface(window);
    while(!quit) {
        SDL_FillRect(screenSurface, NULL, 0xC70039);
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_MOUSEMOTION:
                    cursor.x = event.motion.x;
                    cursor.y = event.motion.y;
                    // Bouton devient noir si le curseur passe au dessus
                    if(SDL_PointInRect(&cursor, &rect)) {
                        SDL_Rect rectSelect = {rect.x-10, rect.y-10, rect.w+20, rect.h+20};
                        SDL_FillRect(screenSurface, &rectSelect, 0x000000);
                        SDL_FillRect(screenSurface, &rect, 0x000000);
                        SDL_FillRect(screenSurface, &rect2, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect3, 0xe7e7e7);
                        sdl_DisplayText(screenSurface, font, win, (SDL_Color) {255, 255, 255, 255}, 40, 60);
                        sdl_DisplayText(screenSurface, font, score_, (SDL_Color) {255, 255, 255, 255}, 40, 620);
                        sdl_DisplayText(screenSurface, font, "Rejouer", (SDL_Color) {255, 255, 255, 255}, rect.x+7, rect.y+5);
                        sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {0, 0, 0, 255}, rect2.x+5, rect2.y+5);
                        sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {0, 0, 0, 255}, rect3.x+12, rect3.y+5);
                        SDL_UpdateWindowSurface(window);
                    } else if(SDL_PointInRect(&cursor, &rect2)) {
                        SDL_Rect rectSelect = {rect2.x-10, rect2.y-10, rect2.w+20, rect2.h+20};
                        SDL_FillRect(screenSurface, &rectSelect, 0x000000);
                        SDL_FillRect(screenSurface, &rect, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect2, 0x000000);
                        SDL_FillRect(screenSurface, &rect3, 0xe7e7e7);
                        sdl_DisplayText(screenSurface, font, win, (SDL_Color) {255, 255, 255, 255}, 40, 60);
                        sdl_DisplayText(screenSurface, font, score_, (SDL_Color) {255, 255, 255, 255}, 40, 620);
                        sdl_DisplayText(screenSurface, font, "Rejouer", (SDL_Color) {0, 0, 0, 255}, rect.x+7, rect.y+5);
                        sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {255, 255, 255, 255}, rect2.x+5, rect2.y+5);
                        sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {0, 0, 0, 255}, rect3.x+12, rect3.y+5);
                        SDL_UpdateWindowSurface(window);
                    } else if(SDL_PointInRect(&cursor, &rect3)) {
                        SDL_Rect rectSelect = {rect3.x-10, rect3.y-10, rect3.w+20, rect3.h+20};
                        SDL_FillRect(screenSurface, &rectSelect, 0x000000);
                        SDL_FillRect(screenSurface, &rect, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect2, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect3, 0x000000);
                        sdl_DisplayText(screenSurface, font, win, (SDL_Color) {255, 255, 255, 255}, 40, 60);
                        sdl_DisplayText(screenSurface, font, score_, (SDL_Color) {255, 255, 255, 255}, 40, 620);
                        sdl_DisplayText(screenSurface, font, "Rejouer", (SDL_Color) {0, 0, 0, 255}, rect.x+7, rect.y+5);
                        sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {0, 0, 0, 255}, rect2.x+5, rect2.y+5);
                        sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {255, 255, 255, 255}, rect3.x+12, rect3.y+5);
                        SDL_UpdateWindowSurface(window);
                    } else {
                        SDL_FillRect(screenSurface, &rect, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect2, 0xe7e7e7);
                        SDL_FillRect(screenSurface, &rect3, 0xe7e7e7);
                        sdl_DisplayText(screenSurface, font, win, (SDL_Color) {255, 255, 255, 255}, 40, 60);
                        sdl_DisplayText(screenSurface, font, score_, (SDL_Color) {255, 255, 255, 255}, 40, 620);
                        sdl_DisplayText(screenSurface, font, "Rejouer", (SDL_Color) {0, 0, 0, 255}, rect.x+7, rect.y+5);
                        sdl_DisplayText(screenSurface, font, "Ncurses", (SDL_Color) {0, 0, 0, 255}, rect2.x+5, rect2.y+5);
                        sdl_DisplayText(screenSurface, font, "Quitter", (SDL_Color) {0, 0, 0, 255}, rect3.x+12, rect3.y+5);
                        SDL_UpdateWindowSurface(window);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    cursor.x = event.motion.x;
                    cursor.y = event.motion.y;
                    // Vérifie le clique sur les boutons
                    if(SDL_PointInRect(&cursor, &rect)) {
                        TTF_CloseFont(font);
                        return 0;
                    } else if(SDL_PointInRect(&cursor, &rect2)) {
                        TTF_CloseFont(font);
                        return 1;
                    } else if(SDL_PointInRect(&cursor, &rect3)) {
                        TTF_CloseFont(font);
                        return 2;
                    }
                    break;
            }
        }
    }
}

// Ferme SDL
void close_SDL(SDL_Window* window, SDL_Surface* surface) {
    SDL_DestroyWindow(window);
    SDL_FreeSurface(surface);
    TTF_Quit();
    SDL_Quit();
}

// Affiche le plateau sur la fenêtre SDL
void sdl_DisplayBoard(Game *game, SDL_Window *window, SDL_Surface* screenSurface) {
    TTF_Font *font = TTF_OpenFont("./vue/georgia.ttf", 60);
    SDL_FillRect(screenSurface, NULL, 0xC70039);
    char score1[50];
    char score2[50];
    SDL_itoa(game->players[0]->score, score1, 10);
    SDL_itoa(game->players[1]->score, score2, 10);
    sdl_DisplayText(screenSurface, font, score1, (SDL_Color) {255, 255, 255, 255}, 40, 10);
    sdl_DisplayText(screenSurface, font, score2, (SDL_Color) {255, 255, 255, 255}, 40, 80);
    SDL_Rect rect = {50, 200, 980, 460};
    int incrX = 980 / game->board->width;
    int incrY = 460 / game->board->height;
    SDL_Rect square = {rect.x, rect.y, incrX, incrY};
    // Contour du plateau
    SDL_FillRect(screenSurface, &(SDL_Rect) {rect.x-5, rect.y-5, rect.w+11, rect.h+11}, 0x000000);
    SDL_FillRect(screenSurface, &rect, 0xFFFFFF);
    for(int i=0; i < game->board->height; i++) {
        for(int j=0; j < game->board->width; j++) {
            // affiche le plateau découpé en plein de carrés
            if(game->board->grid[i][j] == 1) {
                square.x = j * incrX + rect.x;
                square.y = i * incrY + rect.y;
                SDL_FillRect(screenSurface, &square, 0x000000);
            }
        }
    }
    // Affichage des motos
    square.x = game->players[0]->bike->x * incrX + rect.x;
    square.y = game->players[0]->bike->y * incrY + rect.y;
    SDL_FillRect(screenSurface, &square, 0x00e3ee);
    square.x = game->players[1]->bike->x * incrX + rect.x;
    square.y = game->players[1]->bike->y * incrY + rect.y;
    SDL_FillRect(screenSurface, &square, 0xff5656);
    SDL_UpdateWindowSurface(window);
    TTF_CloseFont(font);
}

// Initialise le jeu sur SDL
void sdl_InitGame(Game *game, SDL_Window *window, SDL_Surface *surface) {
    switch(sdl_DisplayMenuStart(window, surface)) {
        case 1:
            loopGame();
            return;
            break;
        case 2:
            return;
            break;
    }
    Player *player1 = game->players[0];
    Player *player2 = game->players[1];
    int counter = 0;
    while(!game->isGameOver) {
        sdl_DisplayBoard(game, window, surface);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            // Si une touche est pressée
            if (event.type == SDL_KEYDOWN) {
                // Vérifie si la touche pressée est l'une des touche suivantes
                switch(event.key.keysym.sym) {
                    case SDLK_z:
                        change_direction(player1->bike, (Direction) UP);
                        break;
                    case SDLK_q:
                        change_direction(player1->bike, (Direction) LEFT);
                        break;
                    case SDLK_s:
                        change_direction(player1->bike, (Direction) DOWN);
                        break;
                    case SDLK_d:
                        change_direction(player1->bike, (Direction) RIGHT);
                        break;
                    case SDLK_i:
                        change_direction(player2->bike, (Direction) UP);
                        break;
                    case SDLK_j:
                        change_direction(player2->bike, (Direction) LEFT);
                        break;
                    case SDLK_k:
                        change_direction(player2->bike, (Direction) DOWN);
                        break;
                    case SDLK_l:
                        change_direction(player2->bike, (Direction) RIGHT);
                        break;
                    }
            }
        }
        // Système de FPS
        if(counter >= 10) {     // 16 ≈ 250ms(intervalle de mouvement des motos) / (1000ms / 60(nombre de frames))
            counter = 0;
            for(int i = 0; i < game->nbPlayers; i++) {
                leave_trace(game->board, game->players[i]->bike);
                move_bike(game->players[i]->bike);
                if(check_collision(game->board, game->players[i]->bike)) {
                    game->players[i]->isAlive = false;
                    game->isGameOver = true;
                }
                game->players[i]->score++;
            }
        } else counter++;
        SDL_Delay(1000/60);
    }
    int choice;
    switch(check_game_over_(game)) {
        // Vérification de qui a gagné
        case -1:
            choice = sdl_DisplayMenuRestart(window, surface, player1->score, "Personne :'(");
            switch(choice) {
                // choix pour relancer ou non
                case 0:
                    free_game(game);
                    game = init_game(20, 20);
                    sdl_InitGame(game, window, surface);
                    break;
                case 1:
                    loopGame();
                    break;
            }
            break;
        case 0:
            choice = sdl_DisplayMenuRestart(window, surface, player1->score, "Joueur 1 !");
            switch(choice) {
                case 0:
                    free_game(game);
                    game = init_game(20, 20);
                    sdl_InitGame(game, window, surface);
                    break;
                case 1:
                    loopGame();
                    break;
            }
            break;
        case 1:
            choice = sdl_DisplayMenuRestart(window, surface, player2->score, "Joueur 2 !");
            switch(choice) {
                case 0:
                    free_game(game);
                    game = init_game(20, 20);
                    sdl_InitGame(game, window, surface);
                    break;
                case 1:
                loopGame();
                break;
            }
            break;
    }
}

// Initialise le fichier vue_sdl.c
void sdlInitia() {
    SDL_Window *window;
    SDL_Surface *screenSurface;
    init_SDL(&window, &screenSurface);
    Game *game = init_game(20, 20);
    sdl_InitGame(game, window, screenSurface);
    free_game(game);
    close_SDL(window, screenSurface);
}