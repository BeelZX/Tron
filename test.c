#include <ncurses.h>
#include <stdio.h>
int displayMenuStart() {
    const char *options[] = {"Jouer", "Quitter", "Choisir SDL"};
    int n_options = 3;
    int choice = 0;
    int ch;

    while (1) {
        clear();
        mvprintw(2, 10, "=== Bienvenue dans Tron ===");
        for (int i = 0; i < n_options; i++) {
            if (i == choice) {
                attron(A_REVERSE); // Mettez en surbrillance l'option sélectionnée
                mvprintw(5 + i, 10, "%s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(5 + i, 10, "%s", options[i]);
            }
        }
        refresh();

        ch = getch();
        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % n_options;
                break;
            case '\n': // Touche Entrée
                return choice;
        }
    }
}

int displayMenuReStart() {
    const char *options[] = {"Rejouer", "Jouer sous SDL", "Quitter"};
    int n_options = 3;
    int choice = 0;
    int ch;

    while (1) {
        clear();
        mvprintw(2, 10, "=== Partie Terminée ===");
        for (int i = 0; i < n_options; i++) {
            if (i == choice) {
                attron(A_REVERSE); // Mettez en surbrillance l'option sélectionnée
                mvprintw(5 + i, 10, "%s", options[i]);
                attroff(A_REVERSE);
            } else {
                mvprintw(5 + i, 10, "%s", options[i]);
            }
        }
        refresh();

        ch = getch();
        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + n_options) % n_options;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % n_options;
                break;
            case '\n': // Touche Entrée
                return choice;
        }
    }
}
int main() {
    // Initialisation de Ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    int choice;

    // Affiche le menu principal
    choice = displayMenuStart();
    if (choice == 1) { // Quitter
        endwin();
        printf("Vous avez choisi de quitter.\n");
        return 0;
    } else if (choice == 2) { // Choisir SDL
        endwin();
        printf("Vous avez choisi de jouer avec SDL (non implémenté ici).\n");
        return 0;
    }

    // Simule la fin de la partie et affiche le menu de redémarrage
    int restart_choice = displayMenuReStart();
    if (restart_choice == 0) { // Rejouer
        endwin();
        printf("Vous avez choisi de rejouer.\n");
    } else if (restart_choice == 1) { // Jouer sous SDL
        endwin();
        printf("Vous avez choisi de jouer avec SDL (non implémenté ici).\n");
    } else if (restart_choice == 2) { // Quitter
        endwin();
        printf("Vous avez choisi de quitter.\n");
    }

    // Fin de Ncurses
    endwin();
    return 0;
}


//j'ai voulu test ncurse mais je capte pas l'include fonctionne pas mais ca compile et affiche bien le truc
/*
ca c'est pour toi l'installe
sudo apt update
sudo apt install libncurses5-dev libncursesw5-dev

pour compiler/ test
gcc test.c -o test -lncurses
./test
*/

