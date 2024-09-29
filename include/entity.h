#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "mainwindow.h"
#include "game_parametrs.h"

struct Textures{
    static sf::Texture& _background();
    static sf::Texture& _blackhole();
    static sf::Texture& _bullet();
    static sf::Texture& _clockslow();
    static sf::Texture& _enemy();
    static sf::Texture& _hard();
    static sf::Texture& _portal();
    static sf::Texture& _spaceship();
    
    static sf::Texture get_texture(const std::string& path);
};


class Blackhole;
class Bullet;
class Clockslow;
class Enemy;
class Portal;
class Hard;
class Spaceship;

class Entity
{
public:

    Entity(float speed);
   
    void set_texture(sf::Texture& texture);

    virtual  ~Entity(){};

    bool check_conflict(Entity* other);

    sf::Vector2f get_position();

    void set_position(sf::Vector2f position);

    void move(float dx,float dy);

    virtual void update(int delta);

    bool overcame_the_lower_border();
    bool overcame_the_upper_border();

    
    float get_speed();

    void set_speed(float speed);

    friend void draw_entity(Entity* entity,sf::RenderWindow* window);

    friend class Animation;


protected:
    sf::Sprite sprite;
    sf::Texture texture;
    
    float speed = 0;

};

void draw_entity(Entity* entity,sf::RenderWindow* window);


#endif