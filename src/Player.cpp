#include "../include/Player.h"

Player::Player(const std::string& name, char symbol) : name(name), symbol(symbol), score(0) {}

const std::string& Player::getName() const {
    return name;
}

char Player::getSymbol() const {
    return symbol;
}

int Player::getScore() const {
    return score;
}

void Player::incrementScore(int points) {
    score += points;
}
