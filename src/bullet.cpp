
#include "bullet.h"

Bullet::Bullet(const sf::Vector2f& position ): Entity(DefaultEntitysSpeed::bullet_default_speed)
{
    sprite.setTexture(Textures::_bullet());

    sprite.setPosition(position);
}

void Bullet::update(int delta)
{
    move(0,-speed * delta);
}
