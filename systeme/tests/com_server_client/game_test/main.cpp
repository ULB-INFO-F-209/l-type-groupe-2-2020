#include "CurrentGame.hpp"
#include "settingServer.hpp"
#include "algorithm"

struct settingArray{
    Boss* boss_set[1];
    Star* stars_set[500];
    Obstacle* obstacles_set[60];
    Projectile* projectiles_set[300];
    Projectile* projectilesEnemy_set[200];
    PlayerShip* player_ships_set[2];
    EnemyShip* enemy_ships_set[65]; 
    Bonus* bonnuses_set[30] ;
    Player* list_player[2];

    int score_j1;
    int score_j2;
    bool two_players;
    // std::vector<Player*>* list_player;
    int tick;
    bool game_over;
    settingArray(settingServer* vect){
        std::copy(vect->object_map->getBoss().begin(),vect->object_map->getBoss().end(),boss_set);
        std::copy(vect->object_map->getStars().begin(),vect->object_map->getStars().end(),stars_set);
        std::copy(vect->object_map->getObstacles().begin(),vect->object_map->getObstacles().end(),obstacles_set);
        std::copy(vect->object_map->getProjectiles().begin(),vect->object_map->getProjectiles().end(),projectiles_set);
        std::copy(vect->object_map->getProjectilesEnemy().begin(),vect->object_map->getProjectilesEnemy().end(),projectilesEnemy_set);
        std::copy(vect->object_map->getListPlayer().begin(),vect->object_map->getListPlayer().end(),player_ships_set);
        std::copy(vect->object_map->getEnemy().begin(),vect->object_map->getEnemy().end(),enemy_ships_set);
        std::copy(vect->object_map->getBonus().begin(),vect->object_map->getBonus().end(),bonnuses_set);
        list_player[0] = (vect->object_player1);
        list_player[1] = (vect->object_player2);

        score_j1 = vect->score_j1;
        score_j2 = vect->score_j2;

        two_players = vect->two_players;
        tick = vect->tick;
        game_over = vect->game_over;
    }
};

void gameVector_To_gameArray(settingServer *vect, settingArray * arr){
    std::copy(vect->object_map->getBoss().begin(),vect->object_map->getBoss().end(),arr->boss_set);
    std::copy(vect->object_map->getStars().begin(),vect->object_map->getStars().end(),arr->stars_set);
    std::copy(vect->object_map->getObstacles().begin(),vect->object_map->getObstacles().end(),arr->obstacles_set);
    std::copy(vect->object_map->getProjectiles().begin(),vect->object_map->getProjectiles().end(),arr->projectiles_set);
    std::copy(vect->object_map->getProjectilesEnemy().begin(),vect->object_map->getProjectilesEnemy().end(),arr->projectilesEnemy_set);
    std::copy(vect->object_map->getListPlayer().begin(),vect->object_map->getListPlayer().end(),arr->player_ships_set);
    std::copy(vect->object_map->getEnemy().begin(),vect->object_map->getEnemy().end(),arr->enemy_ships_set);
    std::copy(vect->object_map->getBonus().begin(),vect->object_map->getBonus().end(),arr->bonnuses_set);
    arr->list_player[0] = (vect->object_player1);
    arr->list_player[1] = (vect->object_player2);

    arr->score_j1 = vect->score_j1;
    arr->score_j2 = vect->score_j2;

    arr->two_players = vect->two_players;
    arr->tick = vect->tick;
    arr->game_over = vect->game_over;
}

int main(){

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
        settingArray obj2{&obj};
        //gameVector_To_gameArray(&obj,&obj2);
        gameOn = !obj.game_over;
        

    }
    //std::cout << obj.score_j1 << std::endl;
    //game_screen.refresh_wnd();
    game_screen.close();


    return 0;
}
