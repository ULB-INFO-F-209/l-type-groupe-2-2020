
#include "Interface.hpp"
#include "CurrentGame.hpp"
#include <iostream>


int main(){


    Interface game_screen{};
    game_screen.init();
    game_screen.initialDraw();

    CurrentGame game(true, 80, easy, true,true);
    bool t =true;
    GameSetting::settingServer obj;
    while(t){
        //game_screen.close();
        //break;
        //std::cout << "Yo" << std::endl;
        game.run_test(&game_screen,&obj);
        //std::cout << obj.game_over << std::endl;
        //break;
        game_screen.display(&obj);
        //t = val->game_over;

    }


    return 0;
}