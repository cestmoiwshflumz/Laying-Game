#ifndef PLAYER_H
#define PLAYER_H

#include <string>

/**
 * @class Player
 * @brief Représente un joueur dans le jeu.
 */
class Player {
public:
    /**
     * @brief Constructeur pour initialiser un joueur avec son nom et son symbole.
     * @param name Nom du joueur.
     * @param symbol Symbole représentant le joueur (ex: 'A', 'B', ...).
     */
    Player(const std::string& name, char symbol);

    /**
     * @brief Récupère le nom du joueur.
     * @return Le nom du joueur.
     */
    const std::string& getName() const;

    /**
     * @brief Récupère le symbole du joueur.
     * @return Le symbole du joueur.
     */
    char getSymbol() const;

    /**
     * @brief Récupère le score actuel du joueur.
     * @return Le score du joueur.
     */
    int getScore() const;

    /**
     * @brief Augmente le score du joueur.
     * @param points Nombre de points à ajouter au score.
     */
    void incrementScore(int points);

private:
    std::string name;   ///< Nom du joueur.
    char symbol;        ///< Symbole représentant le joueur (ex: 'A', 'B', ...).
    int score;          ///< Score actuel du joueur.
};

#endif // PLAYER_H
