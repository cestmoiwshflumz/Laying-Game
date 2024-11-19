#include "../include/Player.h"

/**
 * @brief Constructeur de la classe Player.
 * Initialise le joueur avec son nom, son symbole, et un score initial de 0.
 * @param name Nom du joueur.
 * @param symbol Symbole utilisé pour représenter le joueur sur le plateau.
 */
Player::Player(const std::string& name, char symbol) : name(name), symbol(symbol), score(0) {}

/**
 * @brief Récupère le nom du joueur.
 * @return Référence constante au nom du joueur.
 */
const std::string& Player::getName() const {
    return name;
}

/**
 * @brief Récupère le symbole du joueur.
 * @return Le symbole du joueur sous forme de caractère.
 */
char Player::getSymbol() const {
    return symbol;
}

/**
 * @brief Récupère le score actuel du joueur.
 * @return Le score du joueur sous forme d'entier.
 */
int Player::getScore() const {
    return score;
}

/**
 * @brief Augmente le score du joueur.
 * @param points Nombre de points à ajouter au score du joueur.
 */
void Player::incrementScore(int points) {
    score += points;
}
