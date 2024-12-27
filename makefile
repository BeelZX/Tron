t: main.c ./controleur/controleur.c ./modele/modele.c ./vue/vue_ncurses.c
	gcc -o tron.exe main.c ./controleur/controleur.c ./modele/modele.c ./vue/vue_ncurses.c -lncurses
	./tron