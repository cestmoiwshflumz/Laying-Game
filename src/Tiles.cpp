#include "../include/Tiles.h"
#include <fstream>
#include "../nlohmann/json.hpp"

using json = nlohmann::json;

/**
 * @brief Constructeur qui charge les tuiles depuis un fichier JSON.
 * @param filename Chemin du fichier JSON contenant les tuiles.
 */
Tiles::Tiles(const std::string& filename) {
    loadTiles(filename);
}

/**
 * @brief Charge les tuiles depuis un fichier JSON.
 * Lit le fichier et initialise la liste des tuiles.
 * @param filename Chemin du fichier JSON.
 */
void Tiles::loadTiles(const std::string& filename) {
    std::cout << "Tentative d'ouverture du fichier : " << filename << std::endl;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << std::endl;
        exit(1);
    }

    json j;
    file >> j;

    // Parcourt chaque élément dans le JSON et charge les tuiles
    for (const auto& item : j) {
        Tile tile;
        tile.id = item["id"].get<int>();
        tile.shape = item["shape"].get<std::vector<std::vector<int>>>();
        tiles.push_back(tile);
    }
}

/**
 * @brief Renvoie la tuile à l'index donné.
 * @param index Index de la tuile dans la liste.
 * @return Référence constante vers la tuile.
 */
const Tile& Tiles::getTile(int index) const {
    if (index < 0 || index >= tiles.size()) {
        std::cerr << "Erreur : Index de tuile invalide" << std::endl;
        exit(1);
    }
    return tiles[index];
}

/**
 * @brief Renvoie le nombre total de tuiles disponibles.
 * @return Nombre total de tuiles.
 */
int Tiles::getTotalTiles() const {
    return tiles.size();
}

/**
 * @brief Effectue une rotation de 90° dans le sens horaire sur une tuile.
 * @param tileShape Matrice représentant la forme de la tuile.
 * @return Nouvelle matrice représentant la tuile après rotation.
 */
std::vector<std::vector<int>> Tiles::rotateTile(const std::vector<std::vector<int>>& tileShape) {
    int rows = tileShape.size();
    int cols = tileShape[0].size();
    std::vector<std::vector<int>> rotated(cols, std::vector<int>(rows, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            rotated[j][rows - 1 - i] = tileShape[i][j];
        }
    }
    return rotated;
}

/**
 * @brief Effectue un retournement horizontal de la tuile.
 * @param tileShape Matrice représentant la forme de la tuile.
 * @return Nouvelle matrice représentant la tuile après retournement.
 */
std::vector<std::vector<int>> Tiles::flipTile(const std::vector<std::vector<int>>& tileShape) {
    std::vector<std::vector<int>> flipped = tileShape;

    // Parcourt chaque ligne et inverse ses colonnes
    for (auto& row : flipped) {
        std::reverse(row.begin(), row.end());
    }

    return flipped;
}
