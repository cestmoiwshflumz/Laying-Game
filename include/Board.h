#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

class Board {
public:
    Board(int numPlayers);  // Constructeur qui initialise la taille de la grille en fonction du nombre de joueurs
    void display() const;   // Méthode pour afficher le plateau

    bool placeTile(int x, int y, const std::vector<std::vector<int>>& tileShape, char playerSymbol); // Place une tuile
    bool canPlaceTile(int x, int y, const std::vector<std::vector<int>>& tileShape, char playerSymbol); // Vérifie si une tuile peut être placée
    void initializeStartingPoints(int numPlayers);


private:
    int size;  // Taille du plateau (20x20 ou 30x30)
    std::vector<std::vector<char>> grid;  // Grille de caractères représentant le plateau
    std::vector<std::pair<int, int>> startingPoints;

};

#endif // BOARD_H
