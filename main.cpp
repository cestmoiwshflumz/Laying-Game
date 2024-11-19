#include <windows.h>
#include "include/Game.h"
#include <iostream>

/**
 * @mainpage Documentation du projet Laying Game
 *
 * @section intro_section Introduction
 *
 * Ce projet est un jeu stratégique où les joueurs placent des tuiles sur un plateau.
 * Chaque joueur commence à partir d'un point de départ, et le but est de former
 * le plus grand carré possible ou d'occuper un maximum de cases.
 *
 * @section rules_section Règles du jeu
 *
 * - Chaque joueur a 9 tours pour jouer.
 * - Les tuiles doivent être placées adjacentes à leurs propres cases ou à leur point de départ.
 * - Les points sont calculés en fonction des cases occupées et de la taille du plus grand carré.
 *
 * @section structure_section Structure du projet
 *
 * - `Board`: Gère le plateau de jeu.
 * - `Game`: Contrôle la logique du jeu.
 * - `Player`: Représente un joueur.
 * - `Tiles`: Gère les tuiles disponibles.
 *
 * @section usage_section Utilisation
 *
 * 1. Lancez le programme.
 * 2. Entrez vos actions lors de chaque tour.
 * 3. Consultez les scores finaux après 9 manches.
 */


/**
 * @brief Point d'entrée principal du programme.
 * Initialise le jeu avec deux joueurs et charge les tuiles depuis un fichier JSON.
 *
 * @return Code de sortie (0 en cas de succès).
 */
int main() {
    // Configure la console pour supporter l'encodage UTF-8 (Windows spécifique)
    SetConsoleOutputCP(CP_UTF8);

    // Initialise la graine pour la génération aléatoire
    std::srand(std::time(nullptr));

    // Demande à l'utilisateur d'entrer le nombre de joueurs
    int numPlayers;
    std::cout << "Entrez le nombre de joueurs (2 à 9) : ";
    while (true) {
        std::cin >> numPlayers;
        if (numPlayers >= 2 && numPlayers <= 9) {
            break;
        }
        std::cout << "Nombre de joueurs invalide. Veuillez entrer un nombre entre 2 et 4 : ";
    }

    // Crée une instance de jeu avec le nombre de joueurs choisi et charge les tuiles depuis un fichier JSON
    Game game(numPlayers, "../data/tiles.json");

    // Démarre le jeu
    game.start();

    return 0;
}