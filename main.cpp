#include "include/Tiles.h"
#include <iostream>

int main() {
    Tiles tiles("D:/C++/Laying_Game/data/tiles.json");  // Assurez-vous que le chemin est correct

    // Affiche le nombre total de tuiles
    std::cout << "Total de tuiles chargées : " << tiles.getTotalTiles() << std::endl;

    // Affiche la première tuile pour vérifier le chargement
    const Tile& tile = tiles.getTile(0);
    std::cout << "ID de la première tuile : " << tile.id << std::endl;
    std::cout << "Forme de la première tuile :" << std::endl;
    for (const auto& row : tile.shape) {
        for (int cell : row) {
            std::cout << (cell ? "#" : " ");
        }
        std::cout << "\n";
    }

    return 0;
}
