#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "entity.h"
#include "game_parametrs.h"
#include <functional>

class Animation{
public:
    Animation(Entity* entity, std::size_t frames_count,unsigned int time_between_frames);
   
    bool load_from_directory(const std::string& dirpath);

    bool play(unsigned int delta);

    Entity* get_entity(){return entity;}

private:
    Entity* entity;
    std::size_t frames_count;
    std::vector<sf::Texture> textures;
    int time_between_frames;
    int timer;
    int number;

    static std::string get_image_path(const std::string& dirpath,std::size_t number);
};



class EnemyAnimation : public Animation{
public:
    EnemyAnimation(Entity* entity);
};

class SpaceshipAnimation : public Animation{
public:
    SpaceshipAnimation(Entity* entity);
};



#endif