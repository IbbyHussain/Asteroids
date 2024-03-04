#include "Asteriod.h"

Asteroid::Asteroid()
{
    Speed = 30;

    Size = AsteroidSize::LARGE;
}

void Asteroid::Update(sf::RenderWindow& window)
{
	window.draw(AsteroidSprite);
}

void Asteroid::Render(sf::RenderWindow& window)
{
    AsteroidTexture.loadFromFile("Assets/Asteroid.png");
    AsteroidSprite.setTexture(AsteroidTexture);
    AsteroidSprite.setPosition(400, 400);

    window.draw(AsteroidSprite);
}

void Asteroid::UpdateAsteroidSize(AsteroidSize NewSize)
{

}
