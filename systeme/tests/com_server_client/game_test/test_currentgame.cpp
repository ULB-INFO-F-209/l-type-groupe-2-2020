
#include "Interface.hpp"
#include "CurrentGame.hpp"
#include <iostream>


int main(){


    Interface game_screen{};
    game_screen.init();
    game_screen.initialDraw();

    CurrentGame game(true, 80, easy, true,true,&game_screen);
    bool t =true;
    GameSetting::settingServer obj;
    while(t){
    
        game.run_test(&game_screen,&obj);
        //game_screen.display(&obj);
        t = !obj.game_over;

    }
    game_screen.close();

    return 0;
}