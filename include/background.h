#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "entity.h"

class Background{
public:
    Background();
    ~Background();

    void update(int delta);

    friend void draw_background(Background* back,sf::RenderWindow* window);

private:
    sf::Sprite* first;
    sf::Sprite* second;
    static float speed;

    void swap_sprites();
};
void draw_background(Background* back,sf::RenderWindow* window);
#endif