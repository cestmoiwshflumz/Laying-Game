#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>

/**
 * @class Board
 * @brief Représente le plateau de jeu pour le placement des tuiles.
 */
class Board {
public:
    /**
     * @brief Constructeur qui initialise la taille de la grille en fonction du nombre de joueurs.
     * @param numPlayers Nombre de joueurs dans la partie (détermine la taille du plateau).
     */
    Board(int numPlayers);

    /**
     * @brief Affiche le plateau de jeu dans la console.
     */
    void display() const;

    /**
     * @brief Place une tuile sur le plateau si possible.
     * @param x Coordonnée x (ligne) où placer la tuile.
     * @param y Coordonnée y (colonne) où placer la tuile.
     * @param tileShape Forme de la tuile sous forme de matrice 2D.
     * @param playerSymbol Symbole du joueur plaçant la tuile.
     * @return True si la tuile a été placée avec succès, False sinon.
     */
    bool placeTile(int x, int y, const std::vector<std::vector<int>>& tileShape, char playerSymbol);

    /**
     * @brief Vérifie si une tuile peut être placée à une position donnée.
     * @param x Coordonnée x (ligne) où tester le placement.
     * @param y Coordonnée y (colonne) où tester le placement.
     * @param tileShape Forme de la tuile sous forme de matrice 2D.
     * @param playerSymbol Symbole du joueur essayant de placer la tuile.
     * @return True si le placement est valide, False sinon.
     */
    bool canPlaceTile(int x, int y, const std::vector<std::vector<int>>& tileShape, char playerSymbol);

    /**
     * @brief Initialise les points de départ pour chaque joueur.
     * @param numPlayers Nombre de joueurs dans la partie.
     */
    void initializeStartingPoints(int numPlayers);

    /**
     * @brief Calcule la taille du plus grand carré occupé par un joueur.
     * @param playerSymbol Symbole du joueur.
     * @return Taille en cases du plus grand carré occupé.
     */
    int calculateLargestSquare(char playerSymbol);

    /**
     * @brief Calcule le nombre total de cases occupées par un joueur.
     * @param playerSymbol Symbole du joueur.
     * @return Nombre total de cases occupées.
     */
    int calculateTotalTiles(char playerSymbol);

private:
    int size;  ///< Taille du plateau (20x20 ou 30x30 selon le nombre de joueurs).
    std::vector<std::vector<char>> grid;  ///< Grille représentant le plateau, chaque case contient un caractère.
    std::vector<std::pair<int, int>> startingPoints;  ///< Points de départ des joueurs (coordonnées).

};

#endif // BOARD_H
