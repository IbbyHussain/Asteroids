#pragma once

#include <SFML/Graphics.hpp>

class Player {
public:

    // A basic Constructor
    Player();

    // Getter functions
    int GetLives() const { return PlayerLives; }
    int GetScore() const { return PlayerScore; }

    // Setter functions
    void SetLives(int Lives);
    void SetScore(int Score);

private:

    int PlayerLives;
    int PlayerScore;

};