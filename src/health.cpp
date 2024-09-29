#include "health.h"

Health::Health(const int& health):
    health_list{
        Hard( sf::Vector2f((1525.0)*Desktop::k_x(), 0.0)),
        Hard(sf::Vector2f((1525.0 - 80.0)*Desktop::k_x(), 0.0)),
        Hard(sf::Vector2f((1525.0 - 160.0)*Desktop::k_x(), 0.0))
    },
    health(health)
{}


void draw_health_indicator(Health *h_indicator, sf::RenderWindow *window)
{
    for (std::size_t i = 0; i < h_indicator->health; i++)
    {
        draw_entity(&h_indicator->health_list[i],window);
    }
}
