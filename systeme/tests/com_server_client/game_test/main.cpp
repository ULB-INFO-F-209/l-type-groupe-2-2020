#include "CurrentGame.hpp"
#include "settingServer.hpp"
#include "algorithm"
#include "iostream"



int main(){

    // CurrentGame game(true , 80, hard, true);
    // game.run();



    Interface game_screen{};
    game_screen.init();
    game_screen.initialDraw();    

    CurrentGame game(true, 80, easy, true,&game_screen);
    
    bool gameOn =true;

    settingServer obj;    
    
    
    while(gameOn){
        game.run_test(&game_screen,&obj);
        
        gameOn = !obj.game_over;
        settingArray obj2(&obj);
        game_screen.display(&obj2);
        

    }
    game_screen.close();


    return 0;
}

