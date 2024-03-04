#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include <string>

//Display text to the screen
void displayText(sf::RenderWindow& window, const std::string& text, const sf::Color& fillColor, const sf::Vector2f& position, unsigned int characterSize);

void UpdatePlayerLivesText(sf::RenderWindow& window, Player* PlayerToUpdate);

void UpdatePlayerScoreText(sf::RenderWindow& window, Player* PlayerToUpdate);

bool bGameOver = false;