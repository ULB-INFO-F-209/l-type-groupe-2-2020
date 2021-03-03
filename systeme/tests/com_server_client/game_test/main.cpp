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

    CurrentGame game(true, 80, easy, false,&game_screen);
    
    bool gameOn =true;

    
    settingServer obj;

    
    
    
    int tmp=0;
    while(gameOn){
        game.run_test(&game_screen,&obj);
        //gameVector_To_gameArray(&obj,&obj2,&size_obj2);
        settingArray obj2 {  {obj.object_map->getBoss().empty() ? Boss(): **(obj.object_map->getBoss().data())},
                             {obj.object_map->getStars().empty() ? Star(): **(obj.object_map->getStars().data())}, 
                             {obj.object_map->getObstacles().empty() ? Obstacle(): **(obj.object_map->getObstacles().data())}, 
                             {obj.object_map->getProjectiles().empty() ? Projectile(): **(obj.object_map->getProjectiles().data())},
                             {obj.object_map->getProjectilesEnemy().empty() ? Projectile(): **(obj.object_map->getProjectilesEnemy().data())},
                             {obj.object_map->getListPlayer().empty() ? PlayerShip(): **(obj.object_map->getListPlayer().data())},
                             {obj.object_map->getEnemy().empty() ? EnemyShip(): **(obj.object_map->getEnemy().data())},
                             {obj.object_map->getBonus().empty() ? Bonus(): **(obj.object_map->getBonus().data())},
                             {obj.list_player->empty() ? Player(): **(obj.list_player->data())},
                             obj.score_j1,
                             obj.score_j2,
                             obj.two_players,
                             obj.tick,
                             obj.game_over,
                             obj.object_map->getLevelTick(),
                             obj.object_map->getCurrentLevel(),
                             { obj.object_map->getBoss().size(),
                                obj.object_map->getStars().size(), 
                                obj.object_map->getObstacles().size(),
                                obj.object_map->getProjectiles().size(), 
                                obj.object_map->getProjectilesEnemy().size(), 
                                obj.object_map->getListPlayer().size(), 
                                obj.object_map->getEnemy().size(), 
                                obj.object_map->getBonus().size(), 
                                obj.list_player->size()} 
                            };
        //Star val[100];
        //val = 
        
        //usleep(10000);
        game_screen.display(&obj2);
        //std::cout << obj2.my_size.boss_set << std::endl;
        //if (tmp == 100)
        //settingArray obj2{&obj};
        //gameVector_To_gameArray(&obj,&obj2);
        gameOn = !obj.game_over;
        tmp++;

    }
    //std::cout << obj.score_j1 << std::endl;
    //game_screen.refresh_wnd();
    game_screen.close();


    return 0;
}

