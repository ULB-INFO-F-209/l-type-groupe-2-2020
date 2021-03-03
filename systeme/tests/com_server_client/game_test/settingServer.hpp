#ifndef SETTINGSERVER_H
#define SETTINGSERVER_H
#include "MapHandler.hpp"
struct settingServer{
    MapHandler* object_map;
    PlayerShip* object_playership1;
    PlayerShip* object_playership2;
    int score_j1;
    int score_j2;
    bool two_players;
    Player * object_player1;
    Player* object_player2;
    std::vector<Player*>* list_player;
    int tick;
    bool game_over;
};


struct sizeArray{
    std::size_t boss_set;
    std::size_t stars_set_size;
    std::size_t obstacles_set;
    std::size_t projectiles_set;
    std::size_t projectilesEnemy_set;
    std::size_t player_ships_set;
    std::size_t enemy_ships_set; 
    std::size_t bonnuses_set ;
    std::size_t list_player;

};

struct settingArray{
    Boss boss_set[1];
    Star stars_set[50];
    Obstacle obstacles_set[65];
    Projectile projectiles_set[200];
    Projectile projectilesEnemy_set[200];
    PlayerShip player_ships_set[2];
    EnemyShip enemy_ships_set[65]; 
    Bonus bonnuses_set[65];
    Player list_player[2];
    int score_j1;
    int score_j2;
    bool two_players;
    // std::vector<Player*>* list_player;
    int tick;
    bool game_over;
    int level_tick;
    int current_level;
    sizeArray my_size;
};




#endif
