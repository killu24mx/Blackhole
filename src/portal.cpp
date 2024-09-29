#include "portal.h"

Portal::Portal(const sf::Vector2f& position) : 
	Entity(DefaultEntitysSpeed::portal_default_speed)
	,rotation_speed(DefaultEntitysSpeed::portal_rotation_speed)
{
	sprite.setTexture(Textures::_portal());
	sprite.setOrigin(80 , 89); // 60 6
	sprite.setRotation(0.0f);
	sprite.setPosition(position);
}

void Portal::rotate(float phi)
{
	sprite.setRotation(phi + sprite.getRotation());
}

void Portal::update(int delta)
{
	move(0,speed * delta);
	rotate(rotation_speed * delta);
}
