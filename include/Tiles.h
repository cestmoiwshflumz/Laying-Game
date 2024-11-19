#ifndef TILES_H
#define TILES_H

#include <vector>
#include <string>
#include <iostream>
#include "../nlohmann/json.hpp" // Inclure la bibliothèque JSON

/**
 * @struct Tile
 * @brief Représente une tuile avec un identifiant et une forme.
 */
struct Tile {
    int id; ///< Identifiant unique de la tuile.
    std::vector<std::vector<int>> shape; ///< Forme de la tuile représentée sous forme de matrice.
};

/**
 * @class Tiles
 * @brief Gère le chargement, la transformation et la gestion des tuiles dans le jeu.
 */
class Tiles {
public:
    /**
     * @brief Constructeur pour charger les tuiles depuis un fichier JSON.
     * @param filename Nom du fichier contenant les données des tuiles.
     */
    Tiles(const std::string& filename);

    /**
     * @brief Accède à une tuile par son index.
     * @param index Index de la tuile dans la collection.
     * @return Référence constante vers la tuile correspondante.
     */
    [[nodiscard]] const Tile& getTile(int index) const;

    /**
     * @brief Renvoie le nombre total de tuiles chargées.
     * @return Le nombre total de tuiles.
     */
    int getTotalTiles() const;

    /**
     * @brief Pivote une tuile de 90° dans le sens horaire.
     * @param tileShape Forme actuelle de la tuile.
     * @return Nouvelle forme de la tuile après rotation.
     */
    std::vector<std::vector<int>> rotateTile(const std::vector<std::vector<int>>& tileShape);

    /**
     * @brief Retourne une tuile verticalement.
     * @param tileShape Forme actuelle de la tuile.
     * @return Nouvelle forme de la tuile après retournement.
     */
    std::vector<std::vector<int>> flipTile(const std::vector<std::vector<int>>& tileShape);

private:
    std::vector<Tile> tiles; ///< Collection de toutes les tuiles chargées.

    /**
     * @brief Charge les tuiles depuis un fichier JSON.
     * @param filename Nom du fichier contenant les données des tuiles.
     */
    void loadTiles(const std::string& filename);
};

#endif // TILES_H
