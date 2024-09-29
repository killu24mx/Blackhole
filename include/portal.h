#ifndef _PORTAL_H_
#define _PORTAL_H_

#include "entity.h"
class Portal:public Entity
{
public:
	Portal(const sf::Vector2f& pos);
	void rotate(float phi);

	virtual void update(int delta)override;
	
private:
	const float rotation_speed = DefaultEntitysSpeed::portal_rotation_speed;


};

#endif