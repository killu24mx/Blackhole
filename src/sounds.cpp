#include "sounds.h"

MediaSound::MediaSound(const std::string &path): buffer(),sound()
{
    load_from_file(path);
}

void MediaSound::play()
{
    sound.play();
}

void MediaSound::pause()
{
    sound.pause();
}

void MediaSound::resume()
{
    if(sound.getStatus() == sf::Sound::Paused)
        sound.play();
}

void MediaSound::stop()
{
    sound.stop();
}

bool MediaSound::load_from_file(const std::string &path)
{
    bool was_loaded = buffer.loadFromFile(path);
    sound = sf::Sound(buffer);
    return was_loaded;
}

void SoundPlayer::stop_all()
{
    this->blackhole.stop();
    this->bullets.stop();
    this->death_in_blackhole.stop();
    this->explosion.stop();
    this->game_over.stop();
    this->healthup.stop();
    this->time_acceleration.stop();
    this->time_dilation.stop();
}

void SoundPlayer::pause_all()
{
    this->blackhole.pause();
    this->bullets.pause();
    this->death_in_blackhole.pause();
    this->explosion.pause();
    this->game_over.pause();
    this->healthup.pause();
    this->time_acceleration.pause();
    this->time_dilation.pause();
}

void SoundPlayer::resume()
{
    this->blackhole.resume();
    this->bullets.resume();
    this->death_in_blackhole.resume();
    this->explosion.resume();
    this->game_over.resume();
    this->healthup.resume();
    this->time_acceleration.resume();
    this->time_dilation.resume();
}
