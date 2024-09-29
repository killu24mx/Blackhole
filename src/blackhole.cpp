#include <SFML/Graphics.hpp>

#include "blackhole.h"

Blackhole::Blackhole(const sf::Vector2f& pos) : 
	Entity(DefaultEntitysSpeed::blackhole_default_speed)
	,rotation_speed(DefaultEntitysSpeed::portal_rotation_speed)
{
	sprite.setTexture(Textures::_blackhole());
	sprite.setOrigin(103 * Desktop::k_x(), 110*Desktop::k_x()); // 60 64
	sprite.setPosition(pos);
	sprite.setRotation(0.0f);
	
	sprite.setPosition(pos);
}
void Blackhole::update(int delta)
{
	move(0,speed * delta);
	rotate(rotation_speed * delta);
}
void Blackhole::rotate(float phi)
{
	sprite.setRotation(phi + sprite.getRotation());
}



