#ifndef _GAME_H_
#define _GAME_H_

#include <deque>

#include "blackhole.h"
#include "bullet.h"
#include "enemy.h"
#include "entity.h"
#include "hard.h"
#include "health.h"
#include "mainwindow.h"
#include "portal.h"
#include "spaceship.h"
#include "clockslow.h"
#include "sounds.h"
#include "game_parametrs.h"
#include "background.h"
#include "score.h"
#include "animation.h"
#include "menu.h"

int rand_num(int start,int end);
bool random(int count);


class Game{
public:
    void play();

    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    ~Game();

private:
    sf::RenderWindow* window = get_window();
    int health = 3;
    Spaceship* spaceship = new Spaceship(sf::Vector2f(500 * Desktop::k_x(), 775 * Desktop::k_y()));
    bool is_slowing = false;
    float game_speed = GameParametrs::default_game_speed;
    int score = 0;
    float boost = GameParametrs::default_boost;
    bool was_stoped = false;
    bool gameover = false;
    bool game_is_going = true;

    
    //list of entities
    std::vector<Bullet*> list_of_bullets;
    std::vector<Enemy*> list_of_enemys;
    std::vector<Hard*> list_of_hard;
    std::vector<Blackhole*> list_of_blackholes;
    std::vector<Portal*> list_of_portals;
    std::vector<Clockslow*> list_of_clocks;


    std::size_t get_entity_count(){
        return list_of_bullets.size()
            + list_of_enemys.size()
            + list_of_hard.size()
            + list_of_blackholes.size()
            + list_of_portals.size()
            + list_of_clocks.size();
    }


    Background background;
    Health h_indicator = Health(health);
    Score score_text = Score("./fonts/font.ttf",score);

    //sounds
    SoundPlayer player;


    //generate entities
    void generate_portals(unsigned int time);
    void generate_blackhouls(unsigned int time);
    void generate_enemys(unsigned int time);
    void generate_clocks(unsigned int time);
    void generate_bullets();


    //spaceship moving

    void spaceship_move_left(unsigned int delta);
    void spaceship_move_right(unsigned int delta);

    //animation
    void animate(unsigned int delta);
    std::deque<SpaceshipAnimation> spceship_animations;
    std::deque<EnemyAnimation> enemy_animations;

    //check_colision
    void check_collision();

    //release colisions 
    void collision(Spaceship* spaceship,Enemy* enemy, std::size_t pos);
    void collision(Spaceship *spaceship, Portal *portal, std::size_t pos);
    void collision(Spaceship *spceship, Hard *hard, std::size_t pos);
    void collision(Spaceship *spceship, Clockslow *clock, std::size_t pos);

    template<typename T>
    void collision(Blackhole* blackhole, std::vector<T>& entity_cont,size_t pos);
    void collision(Blackhole* blackhole);
    void collision(Enemy* enemy, Bullet* bullet, size_t enemy_pos,size_t bullet_pos);

   
    template<typename _EntityPtr>
    void kill_entity(std::vector<_EntityPtr>& entity_c,  _EntityPtr& entity);

    template<typename _EntityPtr>
    void kill_entity(std::vector<_EntityPtr>& entity_c, std::size_t pos);

    template<typename _EntityPtr>
    void kill_entity_f(std::vector<_EntityPtr>& entity_c, Entity* entity);

    void kill_spaceship();
    
    //control_of_the_game_process
  
    void slow(unsigned int time);
    void stop();
    Lose_menu::LoseMenuExitCode game_over();

    

    //drawing entities
    void draw_entities();

    //update entities
    void update(unsigned int delta);
};




template <typename _EntityPtr>
void Game::collision(Blackhole *blackhole,std::vector<_EntityPtr> &entity_c, size_t pos)
{
    _EntityPtr entity = entity_c[pos];
    delete entity;
    entity_c.erase(entity_c.begin() + pos);
    player.death_in_blackhole.play();
}

template <typename _EntityPtr>
void Game::kill_entity(std::vector<_EntityPtr> &entity_c,  _EntityPtr &entity)
{
    std::size_t pos = &entity - &(*entity_c.begin());
    kill_entity(entity_c,pos);
    std::cout << "killed" << std::endl;
}

template <typename _EntityPtr>
void Game::kill_entity(std::vector<_EntityPtr> &entity_c, std::size_t pos)
{
    _EntityPtr entity = entity_c[pos];
    delete entity;
    entity_c.erase(entity_c.begin() + pos);
    
}

template <typename _EntityPtr>
void Game::kill_entity_f(std::vector<_EntityPtr> &entity_c, Entity* entity)
{
    auto it  = std::find(entity_c.begin(),entity_c.end(),entity);
    entity_c.erase(it);
    delete entity;
}

template<typename _EntityPtr>
void kill_all_entity(const std::vector<_EntityPtr>& vec){
    for(auto* entity : vec)
        delete entity;
}
#endif

