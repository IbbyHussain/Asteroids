#pragma once

#include <SFML/Graphics.hpp>

class Projectile 
{

public:
    // A basic Constructor that sets the initial position
    //Projectile(float PositionX, float PositionY);

    Projectile(float startX, float startY, float rotation, float DirX);


    void Update(sf::RenderWindow& window, float deltaTime);
    void Render(sf::RenderWindow& window);

    // Getter functions
    sf::Sprite GetProjectileSprite() const { return ProjectileSprite; }

    // Get the sprites bounding box
    sf::FloatRect GetBoundingBox() const { return ProjectileSprite.getGlobalBounds(); }

private:

    sf::Texture ProjectileTexture;
    sf::Sprite ProjectileSprite;
    int Speed;


    float DirecionX;
};