#include "Projectile.h"

Projectile::Projectile(float PositionX, float PositionY)
{
    Speed = 150;
    ProjectileSprite.setPosition(PositionX, PositionY);
    ProjectileSprite.setScale(0.5f, 0.5f);
}

void Projectile::Update(sf::RenderWindow& window, float deltaTime)
{
    ProjectileSprite.move(0.0f, -Speed * deltaTime);
    window.draw(ProjectileSprite);
}

void Projectile::Render(sf::RenderWindow& window)
{
    ProjectileTexture.loadFromFile("Assets/Ship.png");
    ProjectileSprite.setTexture(ProjectileTexture);
    window.draw(ProjectileSprite);
}

