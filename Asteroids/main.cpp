#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>
#include "Player.h"
#include "Projectile.h"
#include "Asteriod.h"
#include <algorithm>
// The player can move the ship forwards, and turn left and righ
// The player can shoot bullets, that fire forwardin the direction the ship is facing


// Once a player loses all their lives the game ends
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
    NewPlayer->SetLives(2);
    NewPlayer->SetScore(0);
    NewPlayer->Render(window);

    // Store Asteroids in an array
    const int NumOfAsteroids = 2;

    // As asteroids are destroyed and respawned need to keep track of curretn number
    int CurrentNumOfAsteroids = NumOfAsteroids;
    Asteroid* Asteroids[NumOfAsteroids];

    // Spawn 5 asteroids
    for (int i = 0; i < NumOfAsteroids; ++i) 
    {
        Asteroids[i] = new Asteroid(LARGE);
        Asteroids[i]->Render(window);
    }

    while (window.isOpen() )
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

        if(!bGameOver)
        {
            // Grace period timer 
            if (NewPlayer->bIsGracePeriodActive())
            {
                // Check if the grace period has finished (3 seconds)
                if (NewPlayer->GetGracePeriodElapsedTime() >= sf::seconds(3.0f))
                {
                    // Stops the grace period
                    NewPlayer->DisableGracePeriod();

                    std::cout << "grace period over";
                }
            }







            // Collision -> Projectile and Asteroids
            auto& projectiles = NewPlayer->GetProjectilesArray();

            // Loop over asteroids and projectiles
            for (auto& projectile : projectiles)
            {
                for (int i = 0; i < CurrentNumOfAsteroids; ++i)
                {
                    auto* asteroid = Asteroids[i];

                    // Check colliison
                    if (asteroid != nullptr && projectile.GetBoundingBox().intersects(asteroid->GetBoundingBox()))
                    {
                        // Destroy the projectile by removing from array if collided with asteroid
                        auto projectileIt = std::remove_if(projectiles.begin(), projectiles.end(), [&projectile](const auto& p)
                            {
                                return &projectile == &p;
                            });

                        projectiles.erase(projectileIt, projectiles.end());

                        // Destroy the asteroid
                        delete Asteroids[i];
                        Asteroids[i] = nullptr;

                        // Shift elements in the array as we just removed an element
                        for (int j = i; j < CurrentNumOfAsteroids - 1; ++j)
                        {
                            Asteroids[j] = Asteroids[j + 1];
                        }

                        // Set asteroids to null
                        Asteroids[CurrentNumOfAsteroids - 1] = nullptr;

                        // Decrease the number of asteroids
                        --CurrentNumOfAsteroids;

                        // Update players score
                        NewPlayer->IncreaseScore(10);
                        UpdatePlayerScoreText(window, NewPlayer);


                        // Break out of the loop 
                        break;
                    }
                }
            }









            // Collision -> Player and Asteroids

            // Can only collide with asteroids if grace period is not active
            if (!NewPlayer->bIsGracePeriodActive())
            {
                for (int i = 0; i < CurrentNumOfAsteroids; ++i)
                {
                    auto* asteroid = Asteroids[i];

                    // Check colliison
                    if (asteroid != nullptr && NewPlayer->GetBoundingBox().intersects(asteroid->GetBoundingBox()))
                    {
                        // will also handle respawning
                        NewPlayer->DecreasePlayerLives();


                        // delete the hit asteroid
                        delete Asteroids[i];
                        Asteroids[i] = nullptr;

                        // Shift elements in the array as we just removed an element
                        for (int j = i; j < CurrentNumOfAsteroids - 1; ++j)
                        {
                            Asteroids[j] = Asteroids[j + 1];
                        }

                        // Set asteroids to null
                        Asteroids[CurrentNumOfAsteroids - 1] = nullptr;

                        // Decrease the number of asteroids
                        --CurrentNumOfAsteroids;

                        // Break out of the loop 
                        break;
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
                if (Asteroids[i] != nullptr)
                {
                    Asteroids[i]->Update(window, dt.asSeconds());
                }
            }

            // Set game over
            if (NewPlayer->GetLives() <= 0)
            {
                //std::cout << "PLAYER HAS DIED";
                bGameOver = true;

                for (int i = 0; i < NumOfAsteroids; ++i)
                {
                    delete Asteroids[i];
                    Asteroids[i] = nullptr;
                }
            }



            UpdatePlayerLivesText(window, NewPlayer);
            UpdatePlayerScoreText(window, NewPlayer);
        }

        // If game over
        if(bGameOver)
        {
           // GAME OVER Text position and size 
           sf::Vector2f GameOverTextPosition = { 300.f, 340.f };
           unsigned int GameOverTextSize = 40;
           displayText(window, "GAME OVER", sf::Color::Red, GameOverTextPosition, GameOverTextSize);

           //if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
           //{
           //    // Reset game state, restart the game
           //    bGameOver = false;

           //    NewPlayer->SetLives(3);
           //    NewPlayer->SetScore(0);
           //    NewPlayer->DisableGracePeriod();

           //    for (int i = 0; i < NumOfAsteroids; ++i) 
           //    {
           //        Asteroids[i] = new Asteroid();
           //        Asteroids[i]->Render(window);
           //    }
           //}
        }


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

void UpdatePlayerLivesText(sf::RenderWindow& window, Player* PlayerToUpdate)
{
    // Lives Text position and size 
    sf::Vector2f LivesTextPosition = { 10.f, 10.f };
    unsigned int LivesTextSize = 24;
    std::string LivesString = "Lives: " + std::to_string(PlayerToUpdate->GetLives());

    displayText(window, LivesString, sf::Color::Red, LivesTextPosition, LivesTextSize);
}

void UpdatePlayerScoreText(sf::RenderWindow& window, Player* PlayerToUpdate)
{
    // Score Text position and size 
    sf::Vector2f ScoreTextPosition = { 10.f, 50.f };
    unsigned int ScoreTextSize = 24;
    std::string ScoreString = "Score: " + std::to_string(PlayerToUpdate->GetScore());

    displayText(window, ScoreString, sf::Color::Red, ScoreTextPosition, ScoreTextSize);
}

