#ifndef _SPACESHIP_H_
#define _SPACESHIP_H_

#include "entity.h"

class Spaceship: public Entity
{
public:
	Spaceship(const sf::Vector2f& position);
	friend class Game;

private:
	bool was_damaged = false;
};


#endif