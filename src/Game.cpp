#include "../include/Game.h"
#include <iostream>
#include <random>

std::random_device rd;  // Source de vraie randomisation (si disponible)
std::mt19937 gen(rd()); // Générateur Mersenne Twister

Game::Game(int numPlayers, const std::string& tileFile)
    : board(numPlayers), tiles(tileFile), currentPlayerIndex(0) {
    for (int i = 0; i < numPlayers; ++i) {
        char symbol = 'A' + i; // Chaque joueur a un symbole unique
        std::string name = "Player " + std::to_string(i + 1);
        players.emplace_back(name, symbol);
    }
}

void Game::start() {
    std::cout << "Démarrage du jeu !" << std::endl;

    // Affiche le plateau initial avant le début du jeu
    std::cout << "Plateau initial :" << std::endl;

    // 9 tours de jeu
    for (int round = 0; round < 9; ++round) {
        std::cout << "=== Tour " << (round + 1) << " ===\n";
        board.display();
        for (auto& player : players) {
            takeTurn(player);
        }
    }

    // Fin du jeu
    std::cout << "Fin du jeu !" << std::endl;
    for (const auto& player : players) {
        std::cout << player.getName() << " - Score : " << player.getScore() << "\n";
    }
}


void Game::takeTurn(Player& player) {
    std::cout << player.getName() << " (" << player.getSymbol() << "), c'est votre tour.\n";

    // Génère un nombre aléatoire pour choisir une tuile
    std::uniform_int_distribution<> dis(0, tiles.getTotalTiles() - 1);
    const Tile& tile = tiles.getTile(dis(gen));

    // Affiche la forme de la tuile
    std::cout << "Forme de la tuile à placer :" << std::endl;
    for (const auto& row : tile.shape) {
        for (int cell : row) {
            std::cout << (cell ? '#' : ' ');
        }
        std::cout << std::endl;
    }

    int x, y;
    bool validPlacement = false;
    do {
        std::cout << "Entrez les coordonnées pour placer la tuile (x y) : ";
        std::cin >> x >> y;

        if (board.canPlaceTile(x, y, tile.shape, player.getSymbol())) {
            validPlacement = true;
        } else {
            std::cout << "Placement invalide : la tuile touche les cases d'un autre joueur ou dépasse la grille.\n";
        }
    } while (!validPlacement);

    // Place la tuile sur le plateau et incrémente le score
    board.placeTile(x, y, tile.shape, player.getSymbol());
    player.incrementScore(tile.shape.size());  // Calcul du score

    // Affiche la grille mise à jour
    std::cout << "Plateau mis à jour :" << std::endl;
    board.display();
}

