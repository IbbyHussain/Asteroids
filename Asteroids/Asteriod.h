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
    Asteroid(AsteroidSize NewSize);

    void Update(sf::RenderWindow& window, float deltaTime);
    void Render(sf::RenderWindow& window);

    void UpdateAsteroidSize(AsteroidSize NewSize);

    void SetAsteroidPosition();

    std::vector<Asteroid*> Split(sf::RenderWindow& window);

    // Getter functions
    sf::Sprite GetAsteroidSprite() const { return AsteroidSprite; }

    // Get the sprites bounding box
    sf::FloatRect GetBoundingBox() const { return AsteroidSprite.getGlobalBounds(); }

    sf::Vector2f GetPosition() const { return AsteroidSprite.getPosition(); }

private:

    AsteroidSize Size;

    int Speed;

    sf::Texture AsteroidTexture;
    sf::Sprite AsteroidSprite;

    sf::Vector2f Direction;



};