#ifndef _SOIUNDS_H_
#define _SOIUNDS_H_

#include<SFML/Audio.hpp>

class MediaSound {
public:
    MediaSound() = default;
    explicit MediaSound(const std::string& path);

    void play();
    void pause();
    void resume();

    void stop();
    
    
private:
    sf::SoundBuffer buffer;
    sf::Sound sound;
    bool load_from_file(const std::string& path);
    


};

struct SoundPlayer{
    SoundPlayer(const SoundPlayer&) = delete;
    SoundPlayer& operator=(const SoundPlayer&) = delete;
    SoundPlayer() = default;

    void stop_all();
    void pause_all();
    void resume();

    MediaSound explosion = MediaSound("media/explosion.ogg");
    MediaSound healthup = MediaSound("media/health.ogg");
    MediaSound blackhole = MediaSound("media/blackhole.ogg");
    MediaSound death_in_blackhole = MediaSound("media/blackholeconflict.ogg");
    MediaSound time_acceleration = MediaSound("media/timefast.ogg");
    MediaSound time_dilation = MediaSound("media/timeslow.ogg");
    MediaSound game_over = MediaSound("media/gameover.ogg");
    MediaSound bullets = MediaSound("media/bullets.ogg");
};




#endif