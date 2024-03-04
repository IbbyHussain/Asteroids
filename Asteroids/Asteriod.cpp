#include "Asteriod.h"
#include <iostream>
#include <cstdlib>

Asteroid::Asteroid(AsteroidSize size) : Size(size)

{
    Speed = 150;

    SetAsteroidPosition();

    UpdateAsteroidSize(size);

    //std::cout << "Asteroid constructor called with size: " << static_cast<int>(size) << std::endl;
}

void Asteroid::Update(sf::RenderWindow& window, float deltaTime)
{

    // Asteriod moves withdirection and speed
    AsteroidSprite.move(Direction.x * Speed * deltaTime, Direction.y * Speed * deltaTime);

    // Get Current position
    sf::Vector2f AsteroidPosition = AsteroidSprite.getPosition();

    // if the Asteroid has gone off the screen
    // Wrap to the right side
    if (AsteroidPosition.x < 0) 
    {
        AsteroidPosition.x = 800; 
    }

    // Wrap to the left side
    else if (AsteroidPosition.x > 800) 
    {
        AsteroidPosition.x = 0;   
    }

    // Wrap to the bottom
    if (AsteroidPosition.y < 0) 
    {
        AsteroidPosition.y = 800; 
    }

    // Wrap to the top
    else if (AsteroidPosition.y > 800) 
    {
        AsteroidPosition.y = 0;   
    }

    AsteroidSprite.setPosition(AsteroidPosition);
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
        //std::cout << "The asteroid is small." << std::endl;
        AsteroidSprite.setScale(sf::Vector2f(1.0f, 1.0f));
        break;

    case MEDIUM:
        //std::cout << "The asteroid is medium." << std::endl;
        AsteroidSprite.setScale(sf::Vector2f(1.5f, 1.5f));
        break;

    case LARGE:
        //std::cout << "The asteroid is large." << std::endl;
        AsteroidSprite.setScale(sf::Vector2f(2.0f, 2.0f));
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

std::vector<Asteroid*> Asteroid::Split(sf::RenderWindow& window)
{
    std::vector<Asteroid*> newAsteroids;

    //std::cout << "Asteroid split! Current size: " << static_cast<int>(Size) << std::endl;

    // Create new asteroids based on the current size
    if (Size == AsteroidSize::LARGE)
    {
        // Split into two medium asteroids
        newAsteroids.push_back(new Asteroid(MEDIUM));
        newAsteroids.push_back(new Asteroid(MEDIUM));
    }

    else if (Size == AsteroidSize::MEDIUM)
    {
        // Split into two small asteroids
        newAsteroids.push_back(new Asteroid(SMALL));
        newAsteroids.push_back(new Asteroid(SMALL));
    }
    

    return newAsteroids;
}



