#include "Asteriod.h"
#include <iostream>
#include <cstdlib>

Asteroid::Asteroid()
{
    Speed = 150;

    Size = AsteroidSize::LARGE;

    SetAsteroidPosition();
}

void Asteroid::Update(sf::RenderWindow& window, float deltaTime)
{
    AsteroidSprite.move(Direction.x * Speed * deltaTime, Direction.y * Speed * deltaTime);
    //AsteroidSprite.move(1 * Speed * deltaTime, 1 * Speed * deltaTime);

	window.draw(AsteroidSprite);
}

void Asteroid::Render(sf::RenderWindow& window)
{
    AsteroidTexture.loadFromFile("Assets/Asteroid.png");
    AsteroidSprite.setTexture(AsteroidTexture);
    //AsteroidSprite.setPosition(400, 400);

    window.draw(AsteroidSprite);
}

void Asteroid::UpdateAsteroidSize(AsteroidSize NewSize)
{
    switch (NewSize) 
    {
    case SMALL:
        std::cout << "The asteroid is small." << std::endl;
        break;

    case MEDIUM:
        std::cout << "The asteroid is medium." << std::endl;
        break;

    case LARGE:
        std::cout << "The asteroid is large." << std::endl;
        break;

    }
}

void Asteroid::SetAsteroidPosition()
{
    // Set asteriod position off screen with random x and y coord
    float SpawnX = float(rand() % 100); // Convert to float
    float SpawnY = -float(rand() % 100); 

    AsteroidSprite.setPosition(SpawnX, SpawnY);

    std::cout << SpawnX;
    std::cout << SpawnY;

    // Set a random direction for the asteroid to move
    Direction.x = float(rand() % 5 - 2); 
    Direction.y = float(rand() % 5 - 2); 

    // Normalise so constant velocity
    float length = std::sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
    if (length != 0) {
        Direction.x /= length;
        Direction.y /= length;
    }

    std::cout << Direction.x;
    std::cout << Direction.y;
    
   
    

    
}

