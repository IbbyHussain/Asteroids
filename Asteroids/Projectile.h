#pragma once

#include <SFML/Graphics.hpp>

class Projectile 
{

public:
    // A basic Constructor that sets the initial position
    Projectile(float PositionX, float PositionY);

    void Update(sf::RenderWindow& window, float deltaTime);
    void Render(sf::RenderWindow& window);

    // Getter functions
    sf::Sprite GetProjectileSprite() const { return ProjectileSprite; }

private:

    sf::Texture ProjectileTexture;
    sf::Sprite ProjectileSprite;
    int Speed;
};