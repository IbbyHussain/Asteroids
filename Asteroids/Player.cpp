#include "Player.h"
#include <iostream>

Player::Player() 
{
    PlayerLives = 3;
    PlayerScore = 0;
    Speed = 200;
    ShootCooldown = 0.0f; // Initial cooldown needs to be 0

    bGracePeriodActive = false;
}

void Player::Update(sf::RenderWindow& window)
{
    // Get Current player position
    sf::Vector2f PlayerPosition = PlayerSprite.getPosition();

    // if the Player has gone off the screen
    // Wrap to the right side
    if (PlayerPosition.x < 0)
    {
        PlayerPosition.x = 800;
    }

    // Wrap to the left side
    else if (PlayerPosition.x > 800)
    {
        PlayerPosition.x = 0;
    }

    // Wrap to the bottom
    if (PlayerPosition.y < 0)
    {
        PlayerPosition.y = 800;
    }

    // Wrap to the top
    else if (PlayerPosition.y > 800)
    {
        PlayerPosition.y = 0;
    }

    PlayerSprite.setPosition(PlayerPosition);
    window.draw(PlayerSprite);
}

void Player::Render(sf::RenderWindow& window) 
{
    PlayerTexture.loadFromFile("Assets/Ship.png");
    PlayerSprite.setTexture(PlayerTexture);
    PlayerSprite.setPosition(400, 400);

    window.draw(PlayerSprite);
}

void Player::MoveForward(float deltaTime)
{
    PlayerSprite.move(0.f, -Speed * deltaTime);
}

void Player::MoveBackward(float deltaTime)
{
    PlayerSprite.move(0.f, Speed * deltaTime);
}

void Player::MoveLeft(float deltaTime)
{
    PlayerSprite.move(-Speed * deltaTime, 0.f);
}

void Player::MoveRight(float deltaTime)
{
    PlayerSprite.move(Speed * deltaTime, 0.f);
}

#pragma region Projectiles

void Player::SpawnProjectile(float deltaTime)
{
    // Ensures player can only shoot a projectile once every 0.15 seconds
    if (TimeSinceLastShot >= ShootCooldown) 
    {
        // Spawn projectile and add to array
        ProjectilesArray.emplace_back(PlayerSprite.getPosition().x, PlayerSprite.getPosition().y);

        //Reset timer
        TimeSinceLastShot = 0.0f; 
        ShootCooldown = 0.15f;
    }

    // Update the time since the last shot
    TimeSinceLastShot += deltaTime;
}

void Player::RenderProjectiles(sf::RenderWindow& window)
{
    // Render all projectiles
    for (auto& Projectile : ProjectilesArray) 
    {
        Projectile.Render(window);
    }
}

void Player::IncreaseScore(int IncreaseAmount)
{
    PlayerScore += IncreaseAmount;
}

void Player::DecreasePlayerLives()
{
    PlayerLives--;

    //Respawn
    PlayerSprite.setPosition(400, 400);

    
    bGracePeriodActive = true;

    std::cout << "activate grace period";
    
    
    
   

    // Reset the grace period timer
    GracePeriodTimer.restart();

    // Player has died
    if(PlayerLives == 0)
    {
        PlayerLives = 0;
    }
}

void Player::UpdateProjectiles(sf::RenderWindow& window, float deltaTime)
{
    // Update all projectiles
    for (auto& Projectile : ProjectilesArray)
    {
        Projectile.Update(window, deltaTime);
    }

    // Despawn projectiles that go off the screen 
    ProjectilesArray.erase(std::remove_if(ProjectilesArray.begin(), ProjectilesArray.end(), [](const Projectile& projectile)
        {
            return projectile.GetProjectileSprite().getPosition().y < 0;
        }), ProjectilesArray.end());
}

#pragma endregion

void Player::SetLives(int Lives)
{
    PlayerLives = Lives;
}

void Player::SetScore(int Score) {
    PlayerScore = Score;
}

void Player::SetGracePeriod(bool bIsActive)
{
    bGracePeriodActive = bIsActive;
    GracePeriodTimer.restart();
}
