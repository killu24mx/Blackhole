#include "hard.h"



Hard::Hard(const sf::Vector2f &position) : Entity(DefaultEntitysSpeed::hard_default_speed)
{
	sprite.setTexture(Textures::_hard());
	set_position(position);
}
