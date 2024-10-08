#ifndef _GAMEPARAMETRS_H_
#define _GAMEPARAMETRS_H_

#include <functional>



inline constexpr int sec(int count){
    return count * 1000;
}

struct GameParametrs{

    static const int default_game_speed = 10;


    static const unsigned int blackholes_geberation_times = sec(10) * default_game_speed;
    static const unsigned int clocks_generation_time = sec(30) * default_game_speed;
    static const unsigned int portal_generation_time = sec(30) * default_game_speed;
    static const unsigned int enemyes_generation_time = sec(5) * default_game_speed;

    static const unsigned int slowning_time = sec(15) * default_game_speed;

    static const int max_count_of_enemies = 3;
    static const int slowing_factor = 5;
    static constexpr float default_boost = 0.003;
};

inline constexpr int fps(int count){
    return 1000 / count;
}

struct DefaultEntitysSpeed{
    static constexpr float background_default_speed = 0.01;
    static constexpr float blackhole_default_speed = 0.03;
    static constexpr float bullet_default_speed = 0.1;
    static constexpr float clockslow_default_speed = 0.01;
    static constexpr float enemy_default_speed = 0.03;
    static constexpr float hard_default_speed = 0.01;
    static constexpr float portal_default_speed = 0.01;
    static constexpr float spaceship_offset = 0.1;
    static constexpr float background_rotaation_speed = 0.01;
    static constexpr float portal_rotation_speed = 0.01;
};


struct AnimationParameters{
    struct SpaceshipAnimation{
        static const std::size_t frames_count = 6;
        static const unsigned int time_between_frames = fps(3) * GameParametrs::default_game_speed;
    };
    struct EnemyAnimation{
        static const std::size_t frames_count = 16;
        static const unsigned int time_between_frames = fps(30) * GameParametrs::default_game_speed;
    };
};


#endif