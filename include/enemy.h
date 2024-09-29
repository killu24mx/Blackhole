#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "entity.h"

class Enemy :public Entity
{
public:
    Enemy(const sf::Vector2f& position);

    friend class Game;
    

private:
    bool was_exploid = false;
    
    
  
};

#endif