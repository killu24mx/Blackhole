#ifndef _HEALTH_H_
#define _HEALTH_H_

#include "hard.h"
#include "mainwindow.h"

class Health{
public:
    Health(const int& health);
    
    friend void draw_health_indicator(Health* h_indicator,sf::RenderWindow* window);
private:
    Hard health_list[3];
    const int& health;
    

};

void draw_health_indicator(Health* h_indicator,sf::RenderWindow* window);



#endif