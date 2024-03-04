#pragma once
#include "Projectile.h"
#include <SFML/Graphics.hpp>

enum AsteroidSize 
{
    SMALL,
    MEDIUM,
    LARGE
};

class Asteroid
{

public:

    // A basic Constructor
    Asteroid();

    void Update(sf::RenderWindow& window, float deltaTime);
    void Render(sf::RenderWindow& window);

    void UpdateAsteroidSize(AsteroidSize NewSize);

    void SetAsteroidPosition();

    // Getter functions
    sf::Sprite GetAsteroidSprite() const { return AsteroidSprite; }

    // Get the sprites bounding box
    sf::FloatRect GetBoundingBox() const { return AsteroidSprite.getGlobalBounds(); }

private:

    AsteroidSize Size;

    int Speed;

    sf::Texture AsteroidTexture;
    sf::Sprite AsteroidSprite;

    sf::Vector2f Direction;



};