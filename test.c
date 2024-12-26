#include <ncurses.h>

int main() {
    initscr();                 // Initialise Ncurses
    printw("Hello, Ncurses!"); // Affiche un message
    refresh();                 // Rafraîchit l'écran
    getch();                   // Attend une touche
    endwin();                  // Quitte Ncurses
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

