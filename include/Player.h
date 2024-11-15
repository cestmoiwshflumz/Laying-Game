#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name, char symbol); // Constructeur

    const std::string& getName() const;  // Récupère le nom du joueur
    char getSymbol() const;             // Récupère le symbole du joueur
    int getScore() const;               // Récupère le score actuel
    void incrementScore(int points);    // Augmente le score

private:
    std::string name;   // Nom du joueur
    char symbol;        // Symbole représentant le joueur (ex: 'A', 'B', ...)
    int score;          // Score du joueur
};

#endif // PLAYER_H
