#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <SFML/Graphics.hpp>

sf::RenderWindow* get_window();

class Desktop{
public:
    static float k_x();
    static float k_y();
    static sf::Vector2f permission();

};





#endif