#pragma once
#include "Projectile.h"
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

    void SpawnProjectile(float deltaTime);

    // Updates the projectiles that the player has shot
    void UpdateProjectiles(sf::RenderWindow& window, float deltaTime);
 
    void RenderProjectiles(sf::RenderWindow& window);

    void IncreaseScore(int IncreaseAmount);

    // Getter functions
    int GetLives() const { return PlayerLives; }

    int GetScore() const { return PlayerScore; }

    sf::Sprite GetPlayerSprite() const { return PlayerSprite; }

    std::vector<Projectile>& GetProjectilesArray() { return ProjectilesArray; }

    // Setter functions
    void SetLives(int Lives);
    void SetScore(int Score);

private:

    int Speed;

    int PlayerLives;
    int PlayerScore;

    sf::Texture PlayerTexture;
    sf::Sprite PlayerSprite;

    // Array of all active projectiles
    std::vector<Projectile> ProjectilesArray;

    // Time between each shot
    float ShootCooldown; 

    // Time since last projectile shot
    float TimeSinceLastShot;

};