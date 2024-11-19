#include "../include/Board.h"
#include <random>
#include <iostream>

/**
 * @brief Constructeur qui initialise la taille de la grille et le plateau de jeu.
 * @param numPlayers Nombre de joueurs dans la partie (détermine la taille de la grille).
 */
Board::Board(int numPlayers) {
    size = (numPlayers <= 4) ? 20 : 30;  // Grille 20x20 pour 2-4 joueurs, 30x30 pour 5-9 joueurs
    grid = std::vector<std::vector<char>>(size, std::vector<char>(size, '.')); // Initialise la grille avec des cases vides
}

/**
 * @brief Affiche le plateau de jeu avec les indices des lignes et colonnes.
 */
void Board::display() const {
    std::cout << "   ";
    for (int col = 0; col < size; ++col) {
        if (col < 10)
            std::cout << " " << col << " ";
        else
            std::cout << col << " ";
    }
    std::cout << "\n";

    for (int row = 0; row < size; ++row) {
        if (row < 10)
            std::cout << " " << row << " ";
        else
            std::cout << row << " ";

        for (int col = 0; col < size; ++col) {
            std::cout << " " << grid[row][col] << " ";
        }
        std::cout << "\n";
    }
}

/**
 * @brief Vérifie si une tuile peut être placée sur la grille.
 * @param x Ligne de placement.
 * @param y Colonne de placement.
 * @param tileShape Forme de la tuile (matrice).
 * @param playerSymbol Symbole du joueur plaçant la tuile.
 * @return `true` si la tuile peut être placée, `false` sinon.
 */
bool Board::canPlaceTile(int x, int y, const std::vector<std::vector<int>>& tileShape, char playerSymbol) {
    int tileHeight = tileShape.size();
    int tileWidth = tileShape[0].size();

    if (x < 0 || y < 0 || x + tileHeight > size || y + tileWidth > size) {
        std::cout << "Erreur : La tuile dépasse les limites de la grille. Dimensions de la grille : "
                  << size << "x" << size << ", Position demandée : (" << x << ", " << y << ").\n";
        return false;
    }

    bool touchesTerritory = false;

    for (int i = 0; i < tileHeight; ++i) {
        for (int j = 0; j < tileWidth; ++j) {
            if (tileShape[i][j] == 1) {
                if (grid[x + i][y + j] != '.') {
                    std::cout << "Erreur : La case (" << (x + i) << ", " << (y + j) << ") est déjà occupée.\n";
                    return false;
                }

                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (abs(dx) + abs(dy) != 1) continue;

                        int adjX = x + i + dx;
                        int adjY = y + j + dy;

                        if (adjX >= 0 && adjX < size && adjY >= 0 && adjY < size) {
                            if (grid[adjX][adjY] == playerSymbol) touchesTerritory = true;

                            for (const auto& point : startingPoints) {
                                int startY = point.first;
                                int startX = point.second;

                                if (startX == adjY && startY == adjX &&
                                    grid[startY][startX] == '0' + (playerSymbol - 'A' + 1)) {
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

/**
 * @brief Place une tuile sur la grille.
 * @param x Ligne de placement.
 * @param y Colonne de placement.
 * @param tileShape Forme de la tuile (matrice).
 * @param playerSymbol Symbole du joueur plaçant la tuile.
 * @return `true` si la tuile a été placée, `false` sinon.
 */
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

/**
 * @brief Initialise les points de départ pour chaque joueur.
 * @param numPlayers Nombre de joueurs.
 */
void Board::initializeStartingPoints(int numPlayers) {
    for (int i = 0; i < numPlayers; ++i) {
        int startX, startY;
        do {
            startX = rand() % size;
            startY = rand() % size;
        } while (grid[startY][startX] != '.');

        startingPoints.emplace_back(startY, startX);
        grid[startY][startX] = '0' + (i + 1);
    }

    for (size_t i = 0; i < startingPoints.size(); ++i) {
        std::cout << "Point de départ enregistré pour le joueur " << i + 1
                  << ": (" << startingPoints[i].first << ", " << startingPoints[i].second << ")\n";
    }
}

/**
 * @brief Calcule la taille du plus grand carré continu occupé par un joueur.
 * @param playerSymbol Symbole du joueur.
 * @return Taille du plus grand carré (en nombre de cases).
 */
int Board::calculateLargestSquare(char playerSymbol) {
    int maxSize = 0;
    std::vector<std::vector<int>> dp(size, std::vector<int>(size, 0));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (grid[i][j] == playerSymbol) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = std::min(dp[i - 1][j], std::min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
                }
                maxSize = std::max(maxSize, dp[i][j]);
            }
        }
    }

    return maxSize * maxSize;
}

/**
 * @brief Calcule le nombre total de cases occupées par un joueur.
 * @param playerSymbol Symbole du joueur.
 * @return Nombre total de cases occupées.
 */
int Board::calculateTotalTiles(char playerSymbol) {
    int total = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (grid[i][j] == playerSymbol) {
                ++total;
            }
        }
    }

    return total;
}
