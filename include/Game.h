#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Tiles.h"
#include <vector>

/**
 * @class Game
 * @brief Gère la logique générale et les étapes du jeu.
 */
class Game {
public:
    /**
     * @brief Constructeur pour initialiser le jeu.
     * @param numPlayers Nombre de joueurs participant au jeu.
     * @param tileFile Chemin du fichier JSON contenant les tuiles.
     */
    Game(int numPlayers, const std::string& tileFile);

    /**
     * @brief Démarre le jeu et exécute les tours des joueurs.
     */
    void start();

    /**
     * @brief Termine la partie et affiche les résultats.
     */
    void endGame();

private:
    Board board;                ///< Plateau de jeu.
    Tiles tiles;                ///< Collection des tuiles disponibles.
    std::vector<Player> players; ///< Liste des joueurs.
    int currentPlayerIndex;     ///< Index du joueur actuellement actif.

    /**
     * @brief Gère un tour pour un joueur spécifique.
     * @param player Référence vers le joueur dont c'est le tour.
     */
    void takeTurn(Player& player);
};

#endif // GAME_H
