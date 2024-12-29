t: main.c ./controleur/controleur.c ./modele/modele.c ./vue/vue_ncurses.c
	gcc -o tron.exe main.c ./controleur/controleur.c ./modele/modele.c ./vue/vue_ncurses.c -lncurses
	./tron

run: ./vue/vue_sdl.c ./modele/modele.c
	gcc -Isrc/include -Lsrc/lib -o sdl_test ./vue/vue_sdl.c ./modele/modele.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
	./sdl_test.exe