#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

class Board {
public:
    Board(int numPlayers);  // Constructeur qui initialise la taille de la grille en fonction du nombre de joueurs
    void display() const;   // Méthode pour afficher le plateau

    // Méthodes pour placer les tuiles et gérer les bonus
    bool placeTile(int x, int y, const std::vector<std::vector<int>>& tileShape, int playerID);
    void placeBonus(int x, int y, char bonusType);

private:
    int size;  // Taille du plateau (20x20 ou 30x30)
    std::vector<std::vector<char>> grid;  // Grille de caractères représentant le plateau
};

#endif // BOARD_H
