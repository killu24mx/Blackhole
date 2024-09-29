#ifndef _BLACKHOLE_H_
#define _BLACKHOLE_H_

#include "spaceship.h"

class Blackhole : public Entity
{
public:
	Blackhole(const sf::Vector2f& pos);

	void rotate(float phi);
	

	virtual void update(int time)override;
	
private:
	const float rotation_speed = 3;
};

#endif