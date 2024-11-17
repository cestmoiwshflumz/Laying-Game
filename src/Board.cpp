#include "../include/Board.h"
#include <random>
#include <iostream>

Board::Board(int numPlayers) {
    size = (numPlayers <= 4) ? 20 : 30;  // Grille 20x20 pour 2-4 joueurs, 30x30 pour 5-9 joueurs
    grid = std::vector<std::vector<char>>(size, std::vector<char>(size, '.')); // Initialise la grille avec des cases vides
}

void Board::display() const {
    // Affiche les indices horizontaux
    std::cout << "   ";
    for (int col = 0; col < size; ++col) {
        std::cout << (col % 10) << ' ';  // Affiche les numéros de colonne
    }
    std::cout << '\n';

    // Affiche les lignes de la grille avec indices
    for (int row = 0; row < size; ++row) {
        std::cout << (row % 10) << "  ";  // Affiche le numéro de la ligne
        for (char cell : grid[row]) {
            std::cout << cell << ' ';
        }
        std::cout << '\n';
    }
}


bool Board::canPlaceTile(int x, int y, const std::vector<std::vector<int>>& tileShape, char playerSymbol) {
    int tileHeight = tileShape.size();
    int tileWidth = tileShape[0].size();

    // Vérifie que la tuile ne dépasse pas les limites de la grille
    if (x + tileHeight > size || y + tileWidth > size) {
        std::cout << "Erreur : La tuile dépasse les limites de la grille.\n";
        return false;
    }

    bool touchesStartingPoint = false;

    for (int i = 0; i < tileHeight; ++i) {
        for (int j = 0; j < tileWidth; ++j) {
            if (tileShape[i][j] == 1) {
                // Vérifie si la case est déjà occupée
                if (grid[x + i][y + j] != '.') {
                    std::cout << "Erreur : La case (" << (x + i) << ", " << (y + j) << ") est déjà occupée.\n";
                    return false;
                }

                // Vérifie si cette cellule touche un point de départ du joueur
                for (const auto& point : startingPoints) {
                    int startX = point.first;
                    int startY = point.second;

                    if (grid[startX][startY] == playerSymbol) {
                        if ((x + i == startX && y + j == startY - 1) ||  // Gauche
                            (x + i == startX && y + j == startY + 1) ||  // Droite
                            (x + i == startX - 1 && y + j == startY) ||  // Haut
                            (x + i == startX + 1 && y + j == startY)) {  // Bas
                            touchesStartingPoint = true;
                            }
                    }
                }
            }
        }
    }

    if (!touchesStartingPoint) {
        std::cout << "Erreur : La tuile ne touche pas un côté du point de départ du joueur.\n";
    }

    return touchesStartingPoint;
}







bool Board::placeTile(int x, int y, const std::vector<std::vector<int>>& tileShape, char playerSymbol) {
    if (!canPlaceTile(x, y, tileShape, playerSymbol)) return false;

    for (int i = 0; i < tileShape.size(); ++i) {
        for (int j = 0; j < tileShape[0].size(); ++j) {
            if (tileShape[i][j] == 1) {
                grid[x + i][y + j] = playerSymbol;
            }
        }
    }
    return true;
}

void Board::initializeStartingPoints(int numPlayers) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, size - 1); // Limites de la grille

    startingPoints.clear();

    for (int player = 1; player <= numPlayers; ++player) {
        bool validPoint = false;
        int x, y;

        // Trouver un point unique aléatoire
        while (!validPoint) {
            x = dis(gen); // Ligne
            y = dis(gen); // Colonne

            // Vérifie que la case est vide
            if (grid[x][y] == '.') {
                validPoint = true;
                grid[x][y] = '0' + player; // Marquer avec le numéro du joueur
                startingPoints.emplace_back(x, y);
            }
        }

        // Afficher le point de départ pour chaque joueur
        std::cout << "Point de départ du joueur " << player << " : (" << x << ", " << y << ")\n";
    }
}


