#ifndef _BULLET_H_
#define _BULLET_H_

#include "entity.h"

class Bullet : public Entity
{
public:
	Bullet(const sf::Vector2f& position);

	virtual void update(int delta);

private:
	
};

#endif 