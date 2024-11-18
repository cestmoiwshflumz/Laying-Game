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

    // Initialiser les points de départ pour les joueurs
    board.initializeStartingPoints(players.size());

    // Affiche le plateau initial avec les points de départ
    std::cout << "Plateau initial avec les points de départ :" << std::endl;
    board.display();

    // 9 tours de jeu
    for (int round = 0; round < 9; ++round) {
        std::cout << "=== Tour " << (round + 1) << " ===\n";
        for (auto& player : players) {
            takeTurn(player);
        }
    }
    // Fin du jeu
    endGame();
}




void Game::takeTurn(Player& player) {
    std::cout << player.getName() << " (" << player.getSymbol() << "), c'est votre tour.\n";

    // Génère un nombre aléatoire pour choisir une tuile
    std::uniform_int_distribution<> dis(0, tiles.getTotalTiles() - 1);
    Tile tile = tiles.getTile(dis(gen));  // Copie locale de la tuile pour permettre les modifications

    char action;
    bool placing = false;

    do {
        std::cout << "Forme actuelle de la tuile :" << std::endl;
        for (const auto& row : tile.shape) {
            for (int cell : row) {
                std::cout << (cell ? '#' : ' ');
            }
            std::cout << std::endl;
        }

        std::cout << "Appuyez sur 'R' pour pivoter, 'F' pour retourner ou 'P' pour placer : ";
        std::cin >> action;

        // Valide les actions reconnues
        if (action == 'R' || action == 'r') {
            tile.shape = tiles.rotateTile(tile.shape);
            std::cout << "Tuile pivotée !" << std::endl;
        } else if (action == 'F' || action == 'f') {
            tile.shape = tiles.flipTile(tile.shape);
            std::cout << "Tuile retournée !" << std::endl;
        } else if (action == 'P' || action == 'p') {
            int x, y;
            std::cout << "Entrez les coordonnées pour placer la tuile (x y) : ";
            std::cin >> y >> x;

            if (board.canPlaceTile(x, y, tile.shape, player.getSymbol())) {
                board.placeTile(x, y, tile.shape, player.getSymbol());
                player.incrementScore(tile.shape.size());
                placing = true;
            } else {
                std::cout << "Placement invalide : la tuile touche les cases d'un autre joueur ou dépasse la grille.\n";
            }
        } else {
            std::cout << "Action non reconnue. Essayez encore.\n";
        }
    } while (!placing);


    // Affiche la grille mise à jour
    std::cout << "Plateau mis à jour :" << std::endl;
    board.display();
}

void Game::endGame() {
    std::cout << "\n=== Fin du jeu ===\n";
    std::cout << "Scores finaux :\n";

    Player* winner = nullptr;
    int highestScore = 0;
    bool tie = false; // Indique s'il y a une égalité

    for (const auto& player : players) {
        std::cout << player.getName() << " - Score : " << player.getScore() << "\n";

        if (player.getScore() > highestScore) {
            highestScore = player.getScore();
            winner = const_cast<Player*>(&player);
            tie = false; // Réinitialise l'égalité
        } else if (player.getScore() == highestScore) {
            tie = true; // Égalité
        }
    }

    if (tie) {
        std::cout << "\nMatch nul ! Plusieurs joueurs ont le score le plus élevé : " << highestScore << "\n";
    } else if (winner) {
        std::cout << "\nLe gagnant est : " << winner->getName() << " avec un score de " << highestScore << " !\n";
    }
}


