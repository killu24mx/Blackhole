#include "background.h"

Background::Background(): 
    first(new sf::Sprite(Textures::_background()))
    ,second(new sf::Sprite(Textures::_background()))
{
    first->setPosition(0, -1080 * Desktop::k_y());
    second->setPosition(0,0);
}

float Background::speed = 0.01;


Background::~Background()
{
    delete first;
    delete second;
}


void Background::update(int delta)
{
    first->move(0,speed * delta);
    second->move(0,speed* delta);

    if (first->getPosition().y >= 0)
    {
        second->setPosition(0, -1200 * Desktop::k_y());//????
        swap_sprites();
    }
}

void Background::swap_sprites()
{
    std::swap(first,second);
}

void draw_background(Background *back, sf::RenderWindow *window)
{
    window->draw(*back->first);
    window->draw(*back->second);
}
