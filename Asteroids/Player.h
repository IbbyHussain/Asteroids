#pragma once
#include "Projectile.h"
#include "Asteriod.h"
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

    void SpawnTripleProjectile(float deltaTime);

    // Updates the projectiles that the player has shot
    void UpdateProjectiles(sf::RenderWindow& window, float deltaTime);
 
    void RenderProjectiles(sf::RenderWindow& window);

    void IncreaseScore(int IncreaseAmount);

    void DecreasePlayerLives();

    sf::Time GetGracePeriodElapsedTime() const { return GracePeriodTimer.getElapsedTime(); }

    // Stops grace period
    void DisableGracePeriod() { bGracePeriodActive = false; }

    // Getter functions
    int GetLives() const { return PlayerLives; }

    int GetScore() const { return PlayerScore; }

    sf::Sprite GetPlayerSprite() const { return PlayerSprite; }

    std::vector<Projectile>& GetProjectilesArray() { return ProjectilesArray; }

    // Get the sprites bounding box
    sf::FloatRect GetBoundingBox() const { return PlayerSprite.getGlobalBounds(); }

    bool bIsGracePeriodActive() const { return bGracePeriodActive; }

    // Setter functions
    void SetLives(int Lives);
    void SetScore(int Score);
    void SetGracePeriod(bool bIsActive);

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

    bool bGracePeriodActive;

    // Timer for grace period
    sf::Clock GracePeriodTimer;


};