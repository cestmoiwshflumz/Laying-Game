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
    if (y + tileHeight > size || x + tileWidth > size) {
        std::cout << "Erreur : La tuile dépasse les limites de la grille.\n";
        return false;
    }

    bool touchesTerritory = false;

    for (int i = 0; i < tileHeight; ++i) {
        for (int j = 0; j < tileWidth; ++j) {
            if (tileShape[i][j] == 1) {
                // Vérifie si la case est déjà occupée
                if (grid[x + i][y + j] != '.') {
                    std::cout << "Erreur : La case (" << (x + i) << ", " << (y + j) << ") est déjà occupée.\n";
                    return false;
                }

                // Vérifie si cette cellule touche un territoire ou le point de départ du joueur
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (abs(dx) + abs(dy) != 1) continue; // Ignore les diagonales et la case elle-même

                        int adjX = x + i + dx;
                        int adjY = y + j + dy;

                        if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                            /*
                            //LOGS
                            std::cout << "Coordonnées vérifiées : (" << x + i << ", " << y + j << ")\n";
                            std::cout << "Case adjacente : (" << adjX << ", " << adjY << ")\n";
                            std::cout << "Contenu de la grille : " << grid[adjX][adjY] << "\n";
                            */


                            // Vérifie si la case adjacente appartient au joueur
                            if (grid[adjX][adjY] == playerSymbol) {
                                touchesTerritory = true;
                            }

                            // Vérifie si la case adjacente est le point de départ du joueur
                            for (const auto& point : startingPoints) {
                                int startY = point.first;
                                int startX = point.second;

                                if (startX == adjY && startY == adjX && grid[startY][startX] == '0' + (playerSymbol - 'A' + 1)) {
                                    touchesTerritory = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (!touchesTerritory) {
        std::cout << "Erreur : La tuile ne touche pas le territoire ou le point de départ du joueur.\n";

    }

    return touchesTerritory;
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
    for (int i = 0; i < numPlayers; ++i) {
        int startX, startY;
        do {
            startX = rand() % size;
            startY = rand() % size;
        } while (grid[startY][startX] != '.'); // Assure que la case est vide

        startingPoints.emplace_back(startY, startX); // Ajoute le point de départ (ligne, colonne)
        grid[startY][startX] = '0' + (i + 1); // Place le symbole du joueur sur la grille
    }


    // Ajoute ce log pour vérifier les coordonnées enregistrées
    for (size_t i = 0; i < startingPoints.size(); ++i) {
        std::cout << "Point de départ enregistré pour le joueur " << i + 1
                  << ": (" << startingPoints[i].first << ", " << startingPoints[i].second << ")\n";
    }
}




