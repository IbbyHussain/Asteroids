#include "Projectile.h"

Projectile::Projectile(float PositionX, float PositionY, float rotation, float DirX)
{
    Speed = 250;
    ProjectileSprite.setPosition(PositionX, PositionY);
    ProjectileSprite.setRotation(rotation);
    ProjectileSprite.setScale(0.5f, 0.5f);

    

    DirecionX = DirX;
}


void Projectile::Update(sf::RenderWindow& window, float deltaTime)
{
    // Allows x direction to be modified
    ProjectileSprite.move(DirecionX, -Speed * deltaTime);
    window.draw(ProjectileSprite);
}



void Projectile::Render(sf::RenderWindow& window)
{
    ProjectileTexture.loadFromFile("Assets/Ship.png");
    ProjectileSprite.setTexture(ProjectileTexture);
    window.draw(ProjectileSprite);
}

