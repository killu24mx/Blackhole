#include "animation.h"

Animation::Animation(Entity *entity, std::size_t frames_count, unsigned int time_between_frames)
    : entity(entity) 
    , frames_count(frames_count)
    , time_between_frames(time_between_frames)
    , textures(frames_count)
    , timer(0)
    , number(1)
{}



bool Animation::load_from_directory(const std::string &dirpath)
{
    bool successfull = true;

    for (std::size_t i = 1; i < frames_count + 1; i++)
    {
        std::string path = get_image_path(dirpath,i);
        sf::Image image;
        
        successfull = successfull && image.loadFromFile(path);
        textures[i-1].loadFromImage(image);
    }
    return successfull;
}

bool Animation::play(unsigned int delta)
{
    if(number > frames_count){
        return false;
    }

    timer += delta;
    if(timer > time_between_frames){
        entity->sprite.setTexture(textures[number - 1]);
        number++;
        timer = 0;
        std::cout  << number << std::endl;
    }
    return true;
}


std::string Animation::get_image_path(const std::string &dirpath, std::size_t number)
{
    return dirpath +  "/" + std::to_string(number) + ".png";
}



EnemyAnimation::EnemyAnimation(Entity* entity): Animation(
    entity,
    AnimationParameters::EnemyAnimation::frames_count,
    AnimationParameters::EnemyAnimation::time_between_frames
)
{
    bool res = load_from_directory("./sprites/animation/enemy"); 
    std::cout << (res ? "loaded" : "not loaded") << std::endl;
    
}

SpaceshipAnimation::SpaceshipAnimation(Entity* entity): Animation(
    entity,
    AnimationParameters::SpaceshipAnimation::frames_count,
    AnimationParameters::SpaceshipAnimation::time_between_frames
){load_from_directory("./sprites/damage"); }