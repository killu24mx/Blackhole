

#include "enemy.h"


Enemy::Enemy(const sf::Vector2f& pos) : Entity(DefaultEntitysSpeed::enemy_default_speed)
{
    sprite.setTexture(Textures::_enemy());

    sprite.setPosition(pos);

    was_exploid = false;

}
