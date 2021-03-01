#include "CurrentGame.hpp"
#include "settingServer.hpp"


int main(int argc, char **argv){

    // CurrentGame game(true , 80, hard, true);
    // game.run();



    Interface game_screen{};
    game_screen.init();
    game_screen.initialDraw();

    CurrentGame game(false, 80, easy, false,&game_screen);
    
    bool gameOn =true;

    
    settingServer obj;
    while(gameOn){
    
        game.run_test(&game_screen,&obj);
        game_screen.display(&obj);
        gameOn = !obj.game_over;
        

    }
    //std::cout << obj.score_j1 << std::endl;
    //game_screen.refresh_wnd();
    game_screen.close();


    return 0;
}
