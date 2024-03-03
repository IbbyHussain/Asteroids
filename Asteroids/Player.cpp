#include "Player.h"
#include <iostream>

Player::Player() 
{
    PlayerLives = 3;
    PlayerScore = 0;
    Speed = 200;
}

void Player::Update(sf::RenderWindow& window)
{
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

void Player::SpawnProjectile()
{
    // Spawn projectile and add to array
    ProjectilesArray.emplace_back(PlayerSprite.getPosition().x, PlayerSprite.getPosition().y);
}

void Player::RenderProjectiles(sf::RenderWindow& window)
{
    // Render all projectiles
    for (auto& Projectile : ProjectilesArray) 
    {
        Projectile.Render(window);
    }
}

void Player::UpdateProjectiles(sf::RenderWindow& window, float deltaTime)
{
    // Update all projectiles
    for (auto& Projectile : ProjectilesArray)
    {
        Projectile.Update(window, deltaTime);
    }
}

#pragma endregion

void Player::SetLives(int Lives)
{
    PlayerLives = Lives;
}

void Player::SetScore(int Score) {
    PlayerScore = Score;
}