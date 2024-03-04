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

    void Update(sf::RenderWindow& window);
    void Render(sf::RenderWindow& window);

    void UpdateAsteroidSize(AsteroidSize NewSize);



private:

    AsteroidSize Size;

    int Speed;

    sf::Texture AsteroidTexture;
    sf::Sprite AsteroidSprite;



};