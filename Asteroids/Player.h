#pragma once

#include <SFML/Graphics.hpp>

class Player 
{

public:

    // A basic Constructor
    Player();

    void Update(sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);

    // Player Movement
    void MoveForward(float deltaTime);
    void MoveBackward(float deltaTime);
    void MoveLeft(float deltaTime);
    void MoveRight(float deltaTime);

    int Speed;

    // Getter functions
    int GetLives() const { return PlayerLives; }
    int GetScore() const { return PlayerScore; }
    sf::Sprite GetPlayerSprite() const { return PlayerSprite; }

    // Setter functions
    void SetLives(int Lives);
    void SetScore(int Score);

private:

    int PlayerLives;
    int PlayerScore;

    sf::Texture PlayerTexture;
    sf::Sprite PlayerSprite;

};