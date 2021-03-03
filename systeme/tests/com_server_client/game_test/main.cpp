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
    
    int tmp=0;
    while(gameOn){
        game.run_test(&game_screen,&obj);
        // settingArray obj2{  obj.object_map->getBoss().empty() ? new Boss(): *(obj.object_map->getBoss().data()),
        //                     obj.object_map->getStars().empty() ? new Star(): *(obj.object_map->getStars().data()), 
        //                     obj.object_map->getObstacles().empty() ? new Obstacle(): *(obj.object_map->getObstacles().data()), 
        //                     obj.object_map->getProjectiles().empty() ? new Projectile(): *(obj.object_map->getProjectiles().data()),
        //                     obj.object_map->getProjectilesEnemy().empty() ? new Projectile(): *(obj.object_map->getProjectilesEnemy().data()),
        //                     obj.object_map->getListPlayer().empty() ? new PlayerShip(): *(obj.object_map->getListPlayer().data()),
        //                     obj.object_map->getEnemy().empty() ? new EnemyShip(): *(obj.object_map->getEnemy().data()),
        //                     obj.object_map->getBonus().empty() ? new Bonus(): *(obj.object_map->getBonus().data()),
        //                     obj.list_player->empty() ? new Player(): *(obj.list_player->data()),
        //                     obj.score_j1,
        //                     obj.score_j2,
        //                     obj.two_players,
        //                     obj.tick,
        //                     obj.game_over,
        //                     obj.object_map->getLevelTick(),
        //                     obj.object_map->getCurrentLevel(),
        //                     { obj.object_map->getBoss().size(),
        //                        obj.object_map->getStars().size(), 
        //                        obj.object_map->getObstacles().size(),
        //                        obj.object_map->getProjectiles().size(), 
        //                        obj.object_map->getProjectilesEnemy().size(), 
        //                        obj.object_map->getListPlayer().size(), 
        //                        obj.object_map->getEnemy().size(), 
        //                        obj.object_map->getBonus().size(), 
        //                        obj.list_player->size()
        //                     } 
        //                 };
        //game_screen.display(&obj2);
        
        //std::copy(obj.object_map->getStars().begin(),obj.object_map->getStars().end(),val);
        //auto val1 = val[0];
        settingArray obj2(&obj);
        // werase(game_screen.get_game_window());
        // for(std::size_t i =0; i<  obj.object_map->getStars().size()/*obj2.my_size.stars_set_size*/;i++){
        //     //mvwaddch(game_screen.get_game_window(), obj.object_map->getStars()[i]->getPos().y, obj.object_map->getStars()[i]->getPos().x, '.');
        //     //std::cout << "array = " << obj2.my_size.stars_set_size << "  vect = " << obj.object_map->getStars().size()<<std::endl;
        //     //usleep(100000);
        //     mvwaddch(game_screen.get_game_window(), obj2.stars_set[i].getPos().y, obj2.stars_set[i].getPos().x, '.');
        // }

        // wrefresh(game_screen.get_game_window());
        // wrefresh(game_screen.get_game_window());
        // usleep(10000); // 10 ms
        // refresh();
        game_screen.display(&obj2);
        
        

        gameOn = !obj.game_over;
        tmp++;

    }
    game_screen.close();


    return 0;
}

