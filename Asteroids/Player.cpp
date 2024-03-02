#include "Player.h"
#include <iostream>

Player::Player() 
{
    PlayerLives = 3;
    PlayerScore = 0;

    
}

void Player::Update(sf::RenderWindow& window)
{
    // Get the current mouse position
    sf::Vector2f MousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
    PlayerSprite.setPosition(MousePosition.x, MousePosition.y); // Set the player position to the mouse position
    window.draw(PlayerSprite);
}

void Player::Render(sf::RenderWindow& window) 
{
    PlayerTexture.loadFromFile("Assets/Ship.png");
    PlayerSprite.setTexture(PlayerTexture);

    window.draw(PlayerSprite);
}


void Player::SetLives(int Lives)
{
    PlayerLives = Lives;
}

void Player::SetScore(int Score) {
    PlayerScore = Score;
}