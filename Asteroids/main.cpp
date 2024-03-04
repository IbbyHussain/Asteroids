#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>
#include "Player.h"
#include "Projectile.h"
#include "Asteriod.h"

//@TODO - Shoot projectiles in player direction
//@TODO - Screen Wrapping
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
    NewPlayer->SetLives(5);
    NewPlayer->Render(window);

    Asteroid* A = new Asteroid();
    A->Render(window);

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

        // Handle player movement inputs, using W,A,S,D
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            NewPlayer->MoveForward(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            NewPlayer->MoveBackward(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            NewPlayer->MoveLeft(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            NewPlayer->MoveRight(dt.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            NewPlayer->SpawnProjectile(dt.asSeconds());
        }

        // Update the player sprite and the projectiles
        NewPlayer->Update(window);
        NewPlayer->UpdateProjectiles(window, dt.asSeconds());
        NewPlayer->RenderProjectiles(window);

        A->Update(window, dt.asSeconds());

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

