#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../src/include/SDL2/SDL.h"
#include "../src/include/SDL2/SDL_ttf.h"
#include "../modele/modele.h"
#include "../controleur/controleur.h"
#include "../vue/vue_ncurses.h"


void sdl_DisplayText(SDL_Surface* surface, TTF_Font *font, char *text, SDL_Color color, int x, int y);
void init_SDL(SDL_Window **window, SDL_Surface **surface);
int sdl_DisplayMenuStart(SDL_Window *window, SDL_Surface* screenSurface);
int sdl_DisplayMenuRestart(SDL_Window *window, SDL_Surface *screenSurface, int score, char *winner);
void close_SDL(SDL_Window* window, SDL_Surface* surface);
void sdl_DisplayBoard(Game *game, SDL_Window *window, SDL_Surface* screenSurface);
void sdl_InitGame(Game *game, SDL_Window *window, SDL_Surface *surface);
void sdlInitia();