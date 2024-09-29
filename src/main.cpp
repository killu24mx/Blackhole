#include <iostream>

#include "entity.h"
#include "menu.h"
#include "game.h"

int main(int argc,char** argv){
    
    while(true){
        StartMenu& menu = StartMenu::get_instance();
        auto code = menu.update();
        if(code == StartMenu::StartMenuExitCode::EXIT){
            return 0;
        }
        if(code == StartMenu::StartMenuExitCode::START){
            Game game;
            game.play();
        }
    }
   
    get_window()->close();
    
    return 0;
}