#include "../include/Board.h"

Board::Board(int numPlayers) {
    size = (numPlayers <= 4) ? 20 : 30;  // Grille 20x20 pour 2-4 joueurs, 30x30 pour 5-9 joueurs
    grid = std::vector<std::vector<char>>(size, std::vector<char>(size, '.')); // Initialise la grille avec des cases vides
}

void Board::display() const {
    for (const auto& row : grid) {
        for (char cell : row) {
            std::cout << cell << ' ';  // Affiche chaque cellule avec un espace entre elles
        }
        std::cout << std::endl;  // Passe à la ligne suivante après chaque rangée
    }
    std::cout << std::endl;  // Ligne vide pour séparer les affichages
}


bool Board::canPlaceTile(int x, int y, const std::vector<std::vector<int>>& tileShape, char playerSymbol) {
    int tileHeight = tileShape.size();
    int tileWidth = tileShape[0].size();

    if (x + tileHeight > size || y + tileWidth > size) return false;

    for (int i = 0; i < tileHeight; ++i) {
        for (int j = 0; j < tileWidth; ++j) {
            if (tileShape[i][j] == 1) {
                if (grid[x + i][y + j] != '.') return false;

                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        if (dx == 0 && dy == 0) continue;
                        int nx = x + i + dx;
                        int ny = y + j + dy;
                        if (nx >= 0 && nx < size && ny >= 0 && ny < size) {
                            if (grid[nx][ny] != '.' && grid[nx][ny] != playerSymbol) return false;
                        }
                    }
                }
            }
        }
    }

    return true;
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
