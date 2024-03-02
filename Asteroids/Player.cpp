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

void Player::SetLives(int Lives)
{
    PlayerLives = Lives;
}

void Player::SetScore(int Score) {
    PlayerScore = Score;
}