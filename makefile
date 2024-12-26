t: main.c ./controleur/controleur.c ./modele/modele.c ./vue/vue_ncurses.c
	gcc -o tron main.c ./controleur/controleur.c ./modele/modele.c ./vue/vue_ncurses.c -lncurses