#include <windows.h>
#include "include/Game.h"
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);

    std::srand(std::time(nullptr)); // Initialiser la graine pour rand()

    Game game(2, "../data/tiles.json"); // 2 joueurs, tuiles chargées depuis JSON
    game.start(); // Lancer le jeu

    return 0;
}
