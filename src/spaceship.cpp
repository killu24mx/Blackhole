#include "spaceship.h"

Spaceship::Spaceship(const sf::Vector2f& position): Entity(300)
{
	sprite.setTexture(Textures::_spaceship());
	set_position(position);
}

