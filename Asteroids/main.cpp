#include <SFML/Graphics.hpp>
#include "main.h"

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

        displayText(window, "Hello", sf::Color::Red);

        //-----------------------------------------------------------------------------------
        // Display the updated game state
        window.display();
    }

    return 0;
}

void displayText(sf::RenderWindow& window, const std::string& text, const sf::Color& fillColor)
{
    sf::Text sfmlText;

   // Use the ystem font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        // if font not valid
    }

    // Set the values of the text, font, text and colour
    sfmlText.setFont(font);
    sfmlText.setString(text);
    sfmlText.setFillColor(fillColor);

    // Set the position of the text to the centre of the screen
    sf::FloatRect textRect = sfmlText.getLocalBounds();
    sfmlText.setPosition((window.getSize().x - textRect.width) / 2, (window.getSize().y - textRect.height) / 2);

    window.draw(sfmlText);
}
