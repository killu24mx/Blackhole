#include "../include/game.h"
#include "game.h"

using namespace sf;

using std::size_t;

void Game::play()
{
    Clock timer;
    unsigned int delta = 0;
    unsigned int time = 0;
    unsigned int old_time = 0;



    while(window->isOpen() && game_is_going)
    {
        unsigned int new_time = timer.getElapsedTime().asMilliseconds();
        delta = (new_time - old_time) * game_speed;
        old_time = new_time;

        time += delta;
        
        
        if(!gameover)
            check_collision();

        if(gameover){
            kill_spaceship();
            auto code = game_over();
            if(code == Lose_menu::LoseMenuExitCode::EXIT)
                window->close();
            else if(code == Lose_menu::LoseMenuExitCode::MENU)
                game_is_going = false;

            continue;
        }

        sf::Event event;

        while(window->pollEvent(event)){
            if (event.type == Event::Closed)
                window->close();

             if (event.type == Event::KeyPressed){
                if (event.key.code == Keyboard::A)
                    spaceship_move_left(delta);
                
                if (event.key.code == Keyboard::D)
                     spaceship_move_right(delta);
                
                if (event.key.code == Keyboard::W)
                    generate_bullets();

                if (event.key.code == Keyboard::Escape)
                    was_stoped = true;
            } 
        }
            
        draw_entities();

        if(was_stoped)  
            stop();
          
        
        generate_enemys(time);
        generate_blackhouls(time);
        generate_portals(time);
        generate_clocks(time);
        
        update(delta);

        animate(delta);

        slow(time);

        game_speed += GameParametrs::default_boost;

        window->display();
    }

}

Game::~Game()
{
    kill_all_entity(list_of_blackholes);
    kill_all_entity(list_of_bullets);
    kill_all_entity(list_of_clocks);
    kill_all_entity(list_of_enemys);
    kill_all_entity(list_of_hard);
    kill_all_entity(list_of_portals);

    if(spaceship) delete spaceship;
}

void Game::generate_portals(unsigned int time)
{
    static unsigned int last_generation_time = time;

    if(time < last_generation_time)
        last_generation_time = time;


    if(time - last_generation_time > GameParametrs::portal_generation_time){
        float x  = rand_num(100, 800);
        Vector2f position(x * Desktop::k_x(),800 * Desktop::k_y());
        list_of_portals.push_back(new Portal(position));
        last_generation_time = time;
    }

    
}

void Game::generate_blackhouls(unsigned int time)
{
    static unsigned int last_generation_time = time;

    if(time < last_generation_time)
        last_generation_time = time;

     if(time - last_generation_time > GameParametrs::blackholes_geberation_times){
        Vector2f pos(spaceship->get_position().x, -100* Desktop::k_y());
        list_of_blackholes.push_back(new Blackhole(pos));
        last_generation_time = time;
    }

    
}

void Game::generate_enemys(unsigned int time)
{ 
    static unsigned int last_generation_time = time;

    if(time < last_generation_time)
        last_generation_time = time;

    if(time - last_generation_time > GameParametrs::enemyes_generation_time){
        int count = rand_num(1,GameParametrs::max_count_of_enemies);
        
        for(int i = 0; i < count;i++){
            int x = rand_num(100 * Desktop::k_x(), 1400 * Desktop::k_x());
            list_of_enemys.push_back(new Enemy(Vector2f(x, -100 * Desktop::k_y())));
        }
        last_generation_time = time;
    }

}

void Game::generate_clocks(unsigned int time)
{
    static unsigned int last_generation_time = time;

    if(time < last_generation_time)
        last_generation_time = time;

    if(time - last_generation_time > GameParametrs::clocks_generation_time){
        float x = rand_num(200*Desktop::k_x(), 1400 * Desktop::k_x());
        Vector2f pos(x,-100);
        list_of_clocks.push_back(new Clockslow(pos));
        last_generation_time = time;
    }

    
}

void Game::generate_bullets()
{
    sf::Vector2f pos(spaceship->get_position().x + 42 * Desktop::k_x(),spaceship->get_position().y);
    list_of_bullets.push_back(new Bullet(pos));
    player.bullets.play();
}


void Game::check_collision()
{
    for (size_t i = 0; i < list_of_enemys.size(); i++){
        if(spaceship->check_conflict(list_of_enemys[i])){
            collision(spaceship,list_of_enemys[i],i);
            if(gameover)return;
        }
    } 
        
    
    for (size_t i = 0; i < list_of_portals.size(); i++)
        if(spaceship->check_conflict(list_of_portals[i]))
            collision(spaceship,list_of_portals[i],i);


    for (size_t i = 0; i < list_of_hard.size(); i++)
        if(spaceship->check_conflict(list_of_hard[i]))
            collision(spaceship,list_of_hard[i],i);


    for (size_t i = 0; i < list_of_clocks.size(); i++)
        if(spaceship->check_conflict(list_of_clocks[i]))
            collision(spaceship,list_of_clocks[i],i);
    


    for (size_t i = 0; i < list_of_blackholes.size(); i++)
    {
        for (size_t j = 0; j < list_of_enemys.size(); j++)
            if(list_of_blackholes[i]->check_conflict(list_of_enemys[j]))
                collision(list_of_blackholes[i],list_of_enemys,j);

        for (size_t j = 0; j < list_of_bullets.size(); j++)
            if(list_of_blackholes[i]->check_conflict(list_of_bullets[j]))
                collision(list_of_blackholes[i],list_of_bullets,j);

        for (size_t j = 0; j < list_of_clocks.size(); j++)
            if(list_of_blackholes[i]->check_conflict(list_of_clocks[j]))
                collision(list_of_blackholes[i],list_of_clocks,j);

    
        if(list_of_blackholes[i]->check_conflict(spaceship)){
            collision(list_of_blackholes[i]);
            return;
        }

    }


    for (size_t i = 0; i < list_of_enemys.size(); i++)
        for (size_t j = 0; j < list_of_bullets.size(); j++)
            if(list_of_bullets[j]->check_conflict(list_of_enemys[i]))
                collision(list_of_enemys[i],list_of_bullets[j],i,j);


    
    
}

void Game::collision(Spaceship *spaceship, Enemy *enemy, std::size_t pos)
{
    if (!enemy->was_exploid)
    {
        if (health != 0)
        {
            health--;
            kill_entity(list_of_enemys,pos);
            SpaceshipAnimation animation(spaceship);
            spceship_animations.push_back(animation);
            enemy->was_exploid = true;
        }
        else 
            gameover = true;
    }
}

void Game::collision(Spaceship *spaceship, Portal *portal, std::size_t pos)
{
    Vector2f old_pos = spaceship->get_position();
    Vector2f new_pos = Vector2f(abs(old_pos.x - 1600 * Desktop::k_x()), old_pos.y);
    spaceship->set_position(new_pos);
}

void Game::collision(Spaceship *spceship, Hard *hard, std::size_t pos)
{
      if(health < 3) 
        health++;

    kill_entity(list_of_hard,pos);
    player.healthup.play();
}

void Game::collision(Spaceship *spceship, Clockslow *clock, std::size_t pos)
{
    is_slowing = true;

    kill_entity(list_of_clocks,pos);
    player.time_dilation.play();
}

void Game::collision(Blackhole *blackhole)
{
    gameover = true;
}

void Game::collision(Enemy *enemy, Bullet *bullet, size_t enemy_pos, size_t bullet_pos)
{
    if(!enemy->was_exploid){
        kill_entity(list_of_bullets,bullet_pos);

        score++;
        player.explosion.play();
        EnemyAnimation animation(enemy);
        enemy_animations.push_back(animation);
        enemy->was_exploid = true;
        enemy->speed = DefaultEntitysSpeed::background_default_speed;
    }
}

void Game::kill_spaceship()
{
    delete spaceship;
    spaceship = nullptr;
}

void Game::slow(unsigned int time)
{
    static unsigned int start = 0;
    if(is_slowing){
        if(start == 0){
            system("clear");
            start = time;
            game_speed /= GameParametrs::slowing_factor;
            boost = 0;
            std::cout << "start slowing" << "\n";
        } 
        if(time - start > GameParametrs::slowning_time/GameParametrs::slowing_factor){
            is_slowing = false;
            game_speed *= GameParametrs::slowing_factor;
            player.time_acceleration.play();
            start = 0;
            boost = GameParametrs::default_boost;
            std::cout << "end slowing" << "\n";
        }
    }
 
}

void Game::stop()
{
    static float src_game_speed = game_speed;
    if(game_speed){
        src_game_speed = game_speed;
        game_speed = 0;
        boost = 0;
        player.pause_all();

    }
  
    Stop_menu& menu = Stop_menu::get_instance();
    auto exit = menu.update();

    switch (exit)
    {
    case Stop_menu::StopMenuExitCode::CONTINUE:
        game_speed = src_game_speed;
        was_stoped = false;
        player.resume();
        boost = GameParametrs::default_boost;
        break;
    
    case Stop_menu::StopMenuExitCode::EXIT:
        window->close();
        break;

    case Stop_menu::StopMenuExitCode::MENU:
        game_is_going = false;
        break;

    default:
        break;
    }
}

Lose_menu::LoseMenuExitCode Game::game_over()
{
    game_speed = 0;
    boost = 0;

    static bool game_over_sound_played = false;
    if(!game_over_sound_played){
        player.game_over.play();
        game_over_sound_played = true;
    }


    sf::Event event;
    while(window->pollEvent(event)){
        if(event.type == sf::Event::Closed)
                window->close();
    }

    draw_entities();
    Lose_menu& menu = Lose_menu::get_instance();
    return menu.update();
}

void Game::draw_entities()
{
    window->clear(sf::Color::Black);

    draw_background(&background,window);

    for(auto* entity : list_of_blackholes)
        draw_entity(entity,window);

    for(auto* entity : list_of_bullets)
        draw_entity(entity,window);

    for(auto* entity : list_of_clocks)
        draw_entity(entity,window);

    for(auto* entity : list_of_enemys)
        draw_entity(entity,window);

    for(auto* entity : list_of_hard)
        draw_entity(entity,window);

    for(auto* entity : list_of_portals)
        draw_entity(entity,window);

    if(!gameover)draw_entity(spaceship,window);

    draw_health_indicator(&h_indicator,window);

    draw_score_text(&score_text,window);

    //window->display();
    

}

void Game::update(unsigned int delta)
{
    for(std::size_t i = 0; i < list_of_blackholes.size(); i++){
        Blackhole* entity = list_of_blackholes[i];
        entity->update(delta);
        if(entity->overcame_the_lower_border()){
            kill_entity(list_of_blackholes,i);
            player.blackhole.stop();
        }

    }
        
    for(std::size_t i = 0; i < list_of_bullets.size(); i++){
        Bullet* entity = list_of_bullets[i];
        entity->update(delta);
        if(entity->overcame_the_upper_border()){
            kill_entity(list_of_bullets,i);
        }
    }
        

    for(std::size_t i = 0; i < list_of_clocks.size(); i++){
        Clockslow* entity = list_of_clocks[i];
        entity->update(delta);
        if(entity->overcame_the_lower_border()){
            kill_entity(list_of_clocks,i);
        }
    }
       

    for(std::size_t i = 0; i < list_of_enemys.size(); i++){
        Enemy* entity = list_of_enemys[i];
        entity->update(delta);
        if(entity->overcame_the_lower_border()){
            if(!entity->was_exploid)(list_of_enemys,i);
        }
    }
        

    for(std::size_t i = 0; i < list_of_hard.size(); i++){
        Hard* entity = list_of_hard[i];
        entity->update(delta);
        if(entity->overcame_the_lower_border()){
            kill_entity(list_of_hard,i);
        }
    }
        

    for(std::size_t i = 0; i < list_of_portals.size(); i++){
        Portal* entity = list_of_portals[i];
        entity->update(delta);
        if(entity->overcame_the_lower_border()){
            kill_entity(list_of_portals,i);
        }
    }
      

    background.update(delta);
}

int rand_num(int start, int end)
{
    static bool first_call = true;
    if(first_call){
        srand(time(nullptr));
        first_call = false;
    }
   
    return rand() % (end - start + 1) + start;
}

void Game::spaceship_move_left(unsigned int delta)
{
    float offset(is_slowing ? DefaultEntitysSpeed::spaceship_offset * GameParametrs::slowing_factor : DefaultEntitysSpeed::spaceship_offset);
    if(spaceship->get_position().x >= 100 * Desktop::k_x()) 
        spaceship->move(-static_cast<float>(delta) * offset,0);
}

void Game::spaceship_move_right(unsigned int delta)
{
    float offset(is_slowing ? DefaultEntitysSpeed::spaceship_offset * GameParametrs::slowing_factor : DefaultEntitysSpeed::spaceship_offset);
    if(spaceship->get_position().x <= 1400  * Desktop::k_x()) 
        spaceship->move(static_cast<float>(delta) * offset,0);
}

void Game::animate(unsigned int delta)
{
    for (std::size_t i = 0; i < spceship_animations.size(); i++)
    {
        if(!spceship_animations[i].play(delta)){
            spaceship->set_texture(Textures::_spaceship());
            spceship_animations.erase(spceship_animations.begin() + i);
        }
    }


    for (std::size_t i = 0; i < enemy_animations.size(); i++)
    {
        if(!enemy_animations[i].play(delta)){
            kill_entity_f(list_of_enemys,enemy_animations[i].get_entity());
            enemy_animations.erase(enemy_animations.begin() + i);
        }
    }

    
    
}
