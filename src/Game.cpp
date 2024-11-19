#include "../include/Game.h"
#include <iostream>
#include <random>

// Générateurs aléatoires
std::random_device rd;  // Source de vraie randomisation (si disponible)
std::mt19937 gen(rd()); // Générateur Mersenne Twister

/**
 * @brief Constructeur de la classe Game. Initialise le jeu avec un nombre de joueurs et un fichier de tuiles.
 * @param numPlayers Nombre de joueurs dans la partie.
 * @param tileFile Chemin vers le fichier contenant les tuiles.
 */
Game::Game(int numPlayers, const std::string& tileFile)
    : board(numPlayers), tiles(tileFile), currentPlayerIndex(0) {
    for (int i = 0; i < numPlayers; ++i) {
        char symbol = 'A' + i; // Chaque joueur a un symbole unique
        std::string name = "Player " + std::to_string(i + 1);
        players.emplace_back(name, symbol);
    }
}

/**
 * @brief Démarre le jeu en initialisant le plateau et en lançant les tours.
 */
void Game::start() {
    std::cout << "Démarrage du jeu !" << std::endl;

    // Initialiser les points de départ
    board.initializeStartingPoints(players.size());

    // Affiche le plateau initial
    std::cout << "Plateau initial avec les points de départ :" << std::endl;
    board.display();

    // Boucle pour les 9 manches
    for (int round = 0; round < 9; ++round) {
        std::cout << "\n=== Tour " << (round + 1) << " ===\n";

        for (auto& player : players) {
            takeTurn(player); // Tour du joueur
        }
    }

    // Fin du jeu
    endGame();
}

/**
 * @brief Effectue le tour d'un joueur.
 * @param player Référence au joueur actif.
 */
void Game::takeTurn(Player& player) {
    std::cout << player.getName() << " (" << player.getSymbol() << "), c'est votre tour.\n";

    // Choisir une tuile aléatoire
    std::uniform_int_distribution<> dis(0, tiles.getTotalTiles() - 1);
    Tile tile = tiles.getTile(dis(gen));  // Copie locale pour modification

    char action;
    bool placing = false;

    do {
        // Affiche la tuile actuelle
        std::cout << "Forme actuelle de la tuile :" << std::endl;
        for (const auto& row : tile.shape) {
            for (int cell : row) {
                std::cout << (cell ? '#' : ' ');
            }
            std::cout << std::endl;
        }

        std::cout << "Appuyez sur 'R' pour pivoter, 'F' pour retourner ou 'P' pour placer : ";
        std::cin >> action;

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

/**
 * @brief Termine le jeu en calculant les scores et en affichant le gagnant.
 */
void Game::endGame() {
    std::cout << "\n=== Fin du jeu ===\n";

    int highestScore = 0;
    int largestSquare = 0;
    Player* winner = nullptr;
    bool tie = false;

    // Calculer les scores pour chaque joueur
    for (const auto& player : players) {
        int squareScore = board.calculateLargestSquare(player.getSymbol());
        int totalTiles = board.calculateTotalTiles(player.getSymbol());

        std::cout << player.getName() << " - Plus grand carré : " << squareScore
                  << " cases, Total de cases occupées : " << totalTiles << "\n";

        // Déterminer le gagnant
        if (squareScore > largestSquare ||
           (squareScore == largestSquare && totalTiles > highestScore)) {
            largestSquare = squareScore;
            highestScore = totalTiles;
            winner = const_cast<Player*>(&player);
            tie = false;
        } else if (squareScore == largestSquare && totalTiles == highestScore) {
            tie = true;
        }
    }

    // Afficher les résultats
    if (tie) {
        std::cout << "\nMatch nul ! Plusieurs joueurs ont atteint le score maximum.\n";
    } else if (winner) {
        std::cout << "\nLe gagnant est : " << winner->getName()
                  << " avec un carré de " << largestSquare
                  << " cases et un total de " << highestScore << " cases !\n";
    }
}
