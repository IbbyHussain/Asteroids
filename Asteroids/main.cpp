#include <SFML/Graphics.hpp>
#include "main.h"
#include <iostream>

//@TODO - Spawn player ship in the centre of the screen
//@TODO - Display score and number of lives (score is 0 and lives is 3 by default)
//@TODO - Player movement: Left, right, forwards and backwards
//@TODO - Shoot projectiles in player direction
//@TODO - Spawn asteriods (outside of screen). Move with constant velocity
//@TODO - Screen Wrapping
//@TODO - Player collision and grace period
//@TODO - Player death (Game Over)
//@TODO - Bullet collision and player score and lives update
//@TODO - Asteriod splitting (Large -> Medium -> Small)

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "LHG Code Exercise");
    sf::Clock GameClock;

    // Grab textures and set up sprites
    sf::Texture PlayerTexture;
    sf::Texture AsteroidTexture;

    PlayerTexture.loadFromFile("Assets/Ship.png");
    AsteroidTexture.loadFromFile("Assets/Asteroid.png");

    sf::Sprite Player;
    Player.setTexture(PlayerTexture);
    sf::Sprite Asteroid;
    Asteroid.setTexture(AsteroidTexture);

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

        // Player ship follows the mouse
        sf::Vector2f MousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
        Player.setPosition(MousePosition.x, MousePosition.y);
        window.draw(Player);

        // Asteroid spins in the center of the screen
        Asteroid.setPosition(400, 400);
        float Rotation = 90.0f;
        Asteroid.rotate(Rotation * dt.asSeconds());
        window.draw(Asteroid);

        // Lives Text position and size 
        sf::Vector2f LivesTextPosition = { 10.f, 10.f };
        unsigned int LivesTextSize = 24; // Set your desired size

        // Score Text position and size 
        sf::Vector2f ScoreTextPosition = { 10.f, 50.f };
        unsigned int ScoreTextSize = 24; // Set your desired size

        displayText(window, "Lives: ", sf::Color::Red, LivesTextPosition, LivesTextSize);
        displayText(window, "Score: ", sf::Color::Red, ScoreTextPosition, ScoreTextSize);
       

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
        return; // Exit the function if the font cannot be loaded
    }

    // Set the values of the text
    sfmlText.setFont(font);
    sfmlText.setString(text);
    sfmlText.setFillColor(fillColor);
    sfmlText.setCharacterSize(characterSize);
    sfmlText.setPosition(position);

    window.draw(sfmlText);
}

