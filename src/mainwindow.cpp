#include "mainwindow.h"

float Desktop::k_x()
{
    return permission().x / 1600;
}

float Desktop::k_y()
{
     return permission().y / 900;
}

sf::Vector2f Desktop::permission()
{
    static sf::Vector2f _permission = sf::Vector2f(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height);
    return _permission;
}

sf::RenderWindow *get_window()
{
    static sf::RenderWindow window(sf::VideoMode(sf::VideoMode::getDesktopMode()), "Window", sf::Style::Fullscreen);
    static bool was_init = false;

    if(!was_init){
        window.setVerticalSyncEnabled(true);
        window.setMouseCursorVisible(true);
        window.setFramerateLimit(60);
        was_init = true;
    }

    return &window;
    
}
