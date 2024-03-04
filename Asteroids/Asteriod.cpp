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

    // Generate a random number (0 to 3) to determine the spawn side
    int SpawnSide = rand() % 4; // 0: top, 1: left, 2: right, 3: bottom

    float SpawnX, SpawnY;

    // Set asteroid position dependin on the spawn side
    switch (SpawnSide) {
    case 0: // Top side
        SpawnX = static_cast<float>(rand() % (800 - 10));
        SpawnY = -static_cast<float>(rand() % (100));
        break;
    case 1: // Left side
        SpawnX = -static_cast<float>(rand() % (100));
        SpawnY = static_cast<float>(rand() % (800 - 10));
        break;
    case 2: // Right side
        SpawnX = 800 + static_cast<float>(rand() % (100));
        SpawnY = static_cast<float>(rand() % (800 - 10));
        break;
    case 3: // Bottom side
        SpawnX = static_cast<float>(rand() % (800 - 10));
        SpawnY = 800 + static_cast<float>(rand() % (100));
        break;
    }

    AsteroidSprite.setPosition(SpawnX, SpawnY);

    // Set a random direction for the asteroid
    Direction.x = static_cast<float>(rand() % 5 - 2); 
    Direction.y = static_cast<float>(rand() % 5 - 2);

    // Normalise so constant velocity
    float length = std::sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
    if (length != 0) {
        Direction.x /= length;
        Direction.y /= length;
    }

    

    
}

