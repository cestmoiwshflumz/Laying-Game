#include "../include/Board.h"

// Constructeur qui initialise le plateau en fonction du nombre de joueurs
Board::Board(int numPlayers) {
    if (numPlayers <= 4) {
        size = 20;  // Grille 20x20 pour 2 à 4 joueurs
    } else {
        size = 30;  // Grille 30x30 pour 5 à 9 joueurs
    }

    // Initialise la grille avec des cases vides ('.')
    grid = std::vector<std::vector<char>>(size, std::vector<char>(size, '.'));
}

// Affiche la grille
void Board::display() const {
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}

// Place une tuile sur le plateau
bool Board::placeTile(int x, int y, const std::vector<std::vector<int>>& tileShape, int playerID) {
    char tileChar = 'A' + playerID;  // Utilise une lettre différente pour chaque joueur (A, B, C, etc.)

    // Vérifie si la tuile peut être placée sans dépasser les bords
    int tileHeight = tileShape.size();
    int tileWidth = tileShape[0].size();

    if (x + tileHeight > size || y + tileWidth > size) {
        return false; // La tuile dépasse la grille
    }

    // Place la tuile en vérifiant les règles (pas de chevauchement avec d'autres tuiles)
    for (int i = 0; i < tileHeight; ++i) {
        for (int j = 0; j < tileWidth; ++j) {
            if (tileShape[i][j] == 1) { // Partie de la tuile
                if (grid[x + i][y + j] != '.') { // Vérifie si la case est déjà occupée
                    return false;
                }
                grid[x + i][y + j] = tileChar;  // Place la partie de la tuile
            }
        }
    }
    return true;
}

// Place un bonus sur le plateau
void Board::placeBonus(int x, int y, char bonusType) {
    if (x >= 0 && x < size && y >= 0 && y < size) {
        grid[x][y] = bonusType;  // Place un caractère spécifique pour représenter le bonus
    }
}
