tron: main.c ./controleur/controleur.c ./modele/modele.c ./vue/vue_ncurses.c ./vue/vue_sdl.c
	gcc -o tron main.c ./controleur/controleur.c ./modele/modele.c ./vue/vue_ncurses.c ./vue/vue_sdl.c -lncurses -lSDL2 -lSDL2_ttf 
	./tron