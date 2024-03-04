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
    int SpawnSide = rand() % 4; 

    float SpawnX = 0.0f;
    float SpawnY = 0.0f;

    // Set asteroid position depending on the spawn side
    switch (SpawnSide) 
    {
        case 0: // Top side
            SpawnX = static_cast<float>(rand() % 800); // Within the width of the screen
            SpawnY = -static_cast<float>(rand() % 100); // Above the screen
            break;
        case 1: // Left side
            SpawnX = -static_cast<float>(rand() % 100); 
            SpawnY = static_cast<float>(rand() % 800); 
            break;
        case 2: // Right side
            SpawnX = 800 + static_cast<float>(rand() % 100); 
            SpawnY = static_cast<float>(rand() % 800); 
            break;
        case 3: // Bottom side
            SpawnX = static_cast<float>(rand() % 800); 
            SpawnY = 800 + static_cast<float>(rand() % 100);
            break;
    }

    AsteroidSprite.setPosition(SpawnX, SpawnY);

    // Direction towards the center of the screen, Screen is 800x800
    sf::Vector2f CentreOfScreen(400.0f, 400.0f);  
    Direction = CentreOfScreen - AsteroidSprite.getPosition();

    // Normalise so constant velocity
    float Length = std::sqrt(Direction.x * Direction.x + Direction.y * Direction.y);
    if (Length != 0) {
        Direction.x /= Length;
        Direction.y /= Length;
    }

    

    
}

