
#include "entity.h"

Entity::Entity(float speed):speed(speed)
{}

void Entity::set_texture(sf::Texture& texture)
{
    sprite.setTexture(texture);
    
}

bool Entity::check_conflict(Entity *other)
{
    return sprite.getGlobalBounds().intersects(other->sprite.getGlobalBounds());
}

sf::Vector2f Entity::get_position()
{
    return sprite.getPosition();
}

void Entity::set_position(sf::Vector2f position)
{
    sprite.setPosition(position);
}

void Entity::move(float dx, float dy)
{
    set_position(get_position() + sf::Vector2f(dx,dy));
}

void Entity::update(int delta)
{
    this->sprite.move(0,speed * delta);
}

bool Entity::overcame_the_lower_border()
{
    sf::Vector2f position = get_position();
    return position.y >= 1000 * Desktop::k_y();
    std::cout << "overcame" << std::endl;
}

bool Entity::overcame_the_upper_border()
{
     sf::Vector2f position = get_position();
     return position.y <= -10 * Desktop::k_y();
}

float Entity::get_speed()
{
    return speed;
}

void Entity::set_speed(float speed)
{
    this->speed = speed;
}

sf::IntRect Entity::get_texture_geometry()
{
    return this->sprite.getTextureRect();
}

void draw_entity(Entity *entity, sf::RenderWindow *window)
{
    window->draw(entity->sprite);
}


sf::Texture& Textures::_background()
{
    static sf::Texture texture = get_texture("sprites/cosmos.jpg");
    return texture;
}

sf::Texture& Textures::_blackhole()
{
    static sf::Texture texture = get_texture("sprites/blackhole.png");
    return texture;
}

sf::Texture& Textures::_bullet()
{
    static sf::Texture texture = get_texture("sprites/bullet.png");
    return texture;
}

sf::Texture& Textures::_clockslow()
{
    static sf::Texture texture = get_texture("sprites/clock.png");
    return texture;
}

sf::Texture& Textures::_enemy()
{
   static sf::Texture texture = get_texture("sprites/enemy.png");
   return texture;
}

sf::Texture& Textures::_hard()
{
    static sf::Texture texture = get_texture("sprites/health.png");
    return texture;
}


sf::Texture& Textures::_portal()
{
    static sf::Texture texture = get_texture("sprites/portal.png");
    return texture;
}

sf::Texture& Textures::_spaceship()
{
    static sf::Texture texture = get_texture("sprites/spaceship.png");
    return texture;
}

sf::Texture Textures::get_texture(const std::string &path)
{
    sf::Texture texture;
    sf::Image image;
    image.loadFromFile(path);
    texture.loadFromImage(image);
    return texture;
}
