#include "clockslow.h"

Clockslow::Clockslow(const sf::Vector2f& pos) : Entity(DefaultEntitysSpeed::clockslow_default_speed)
{
	sprite.setTexture(Textures::_clockslow());
	sprite.setPosition(pos);
}

