#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>
#include "Player.h"
#include "Projectile.h"
#include "Asteriod.h"
#include <algorithm>
// The player can move the ship forwards, and turn left and righ
// The player can shoot bullets, that fire forwardin the direction the ship is facing
// If the player collides with an asteroid they lose a life and respawn in the center of the screen.
// After colliison with asteroid player has grace period where asteroid cannot collide with them
// Once a player loses all their lives the game ends
// When a bullet collides with an asteroid, both are destroyed and the player earns some score
// When an asteroid is destroyed it splits into two smaller ones.

//@TODO - Shoot projectiles in player direction
//@TODO - Player collision and grace period
//@TODO - Player death (Game Over)
//@TODO - Bullet collision and player score and lives update
//@TODO - Asteriod splitting (Large -> Medium -> Small)

#include <SFML/Graphics.hpp>

int main()
{
    std::srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(800, 800), "LHG Code Exercise");
    sf::Clock GameClock;

    // Create a instance of the player 
    Player* NewPlayer = new Player();
    NewPlayer->SetLives(3);
    NewPlayer->Render(window);

    // Store Asteroids in an array
    const int NumOfAsteroids = 5;
    Asteroid* Asteroids[NumOfAsteroids];

    // Spawn 5 asteroids
    for (int i = 0; i < NumOfAsteroids; ++i) 
    {
        Asteroids[i] = new Asteroid();
        Asteroids[i]->Render(window);
    }

    while (window.isOpen())
    {
        // Get the delta time for the game update
        sf::Time dt = GameClock.restart();

        // Poll for window being closed
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Reset the window
        window.clear();

        //-----------------------------------------------------------------------------------
        // Game logic can go here

        // Loop over asteroids and projectiles
        auto& projectiles = NewPlayer->GetProjectilesArray();
        for (auto& projectile : projectiles)
        {
            for (auto* asteroid : Asteroids)
            {
                // Check colliison
                if (projectile.GetBoundingBox().intersects(asteroid->GetBoundingBox()))
                {
                   

                    // Destroy the projectile by removing from array if collided with asteroid
                    auto projectileIt = std::remove_if(projectiles.begin(), projectiles.end(), [&projectile](const auto& p) 
                        {
                            return &projectile == &p;
                        });

                    projectiles.erase(projectileIt, projectiles.end());

                    
                }
            }
        }

        // Handle player movement inputs, using W,A,S,D
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        {
            NewPlayer->MoveForward(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
        {
            NewPlayer->MoveBackward(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
        {
            NewPlayer->MoveLeft(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
        {
            NewPlayer->MoveRight(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) 
        {
            NewPlayer->SpawnProjectile(dt.asSeconds());
        }

        // Update the player sprite and the projectiles
        NewPlayer->Update(window);
        NewPlayer->UpdateProjectiles(window, dt.asSeconds());
        NewPlayer->RenderProjectiles(window);

        // Update all asteroids
        for (int i = 0; i < NumOfAsteroids; ++i)
        {
            Asteroids[i]->Update(window, dt.asSeconds());
        }

        // Lives Text position and size 
        sf::Vector2f LivesTextPosition = { 10.f, 10.f };
        unsigned int LivesTextSize = 24;
        std::string LivesString = "Lives: " + std::to_string(NewPlayer->GetLives());

        // Score Text position and size 
        sf::Vector2f ScoreTextPosition = { 10.f, 50.f };
        unsigned int ScoreTextSize = 24;
        std::string ScoreString = "Score: " + std::to_string(NewPlayer->GetScore());

        displayText(window, LivesString, sf::Color::Red, LivesTextPosition, LivesTextSize);
        displayText(window, ScoreString, sf::Color::Red, ScoreTextPosition, ScoreTextSize);
       

        //-----------------------------------------------------------------------------------
        // Display the updated game state
        window.display();
    }

    return 0;
}

void displayText(sf::RenderWindow& window, const std::string& text, const sf::Color& fillColor, const sf::Vector2f& position, unsigned int characterSize)
{
    sf::Text sfmlText;

    // Use the system font
    sf::Font font;
    if (!font.loadFromFile("Assets/arial.ttf")) {
        std::cout << "Error loading font" << std::endl;
        return;
    }

    // Set the values of the text
    sfmlText.setFont(font);
    sfmlText.setString(text);
    sfmlText.setFillColor(fillColor);
    sfmlText.setCharacterSize(characterSize);
    sfmlText.setPosition(position);

    window.draw(sfmlText);
}

