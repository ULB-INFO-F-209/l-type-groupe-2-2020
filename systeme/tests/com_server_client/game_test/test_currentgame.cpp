
#include "Interface.hpp"
#include "CurrentGame.hpp"
#include <iostream>


int main(){


    Interface game_screen{};
    game_screen.init();
    game_screen.initialDraw();

    CurrentGame game(true, 80, easy, false,true,&game_screen);
    bool t =true;
    GameSetting::settingServer obj;
    while(t){
    
        game.run_test(&game_screen,&obj);
        game_screen.display(&obj);
        t = !obj.game_over;
        

    }
    //std::cout << obj.score_j1 << std::endl;
    game_screen.drawGameOver(obj.object_map,obj.score_j1 + obj.score_j2);
    //game_screen.refresh_wnd();
    game_screen.close();
    std::cout << t <<std::endl;

    return 0;
}