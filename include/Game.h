#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Tiles.h"
#include <vector>

class Game {
public:
    Game(int numPlayers, const std::string& tileFile); // Initialiser le jeu
    void start();  // Démarrer le jeu

private:
    Board board;                // Plateau de jeu
    Tiles tiles;                // Tuiles
    std::vector<Player> players; // Joueurs
    int currentPlayerIndex;     // Index du joueur actuel

    void takeTurn(Player& player);  // Gestion d'un tour
};

#endif // GAME_H
