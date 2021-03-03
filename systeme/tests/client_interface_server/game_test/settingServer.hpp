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
    sizeArray my_size;
    Boss boss_set[1];
    Star stars_set[606];
    Obstacle obstacles_set[100];
    Projectile projectiles_set[300];
    Projectile projectilesEnemy_set[300];
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

    settingArray(settingServer*obj){
        my_size = { obj->object_map->getBoss().size(),
                    obj->object_map->getStars().size(),
                    obj->object_map->getObstacles().size(),
                    obj->object_map->getProjectiles().size(), 
                    obj->object_map->getProjectilesEnemy().size(), 
                    obj->object_map->getListPlayer().size(), 
                    obj->object_map->getEnemy().size(), 
                    obj->object_map->getBonus().size(), 
                    obj->list_player->size()
                    };
        
        toArray((obj->object_map->getBoss()),boss_set);
        toArray((obj->object_map->getStars()),stars_set);
        toArray((obj->object_map->getObstacles()),obstacles_set);
        toArray((obj->object_map->getProjectiles()),projectiles_set);
        toArray((obj->object_map->getProjectilesEnemy()),projectilesEnemy_set);
        toArray((obj->object_map->getEnemy()),enemy_ships_set);
        toArray((obj->object_map->getListPlayer()),player_ships_set);
        toArray((obj->object_map->getBonus()),bonnuses_set);
        toArray(*(obj->list_player),list_player);

        score_j1 = obj->score_j1;
        score_j2 = obj->score_j2;
        two_players =obj->two_players;
        game_over = obj->game_over;
        tick = obj->tick;
        level_tick = obj->object_map->getLevelTick();
        current_level = obj->object_map->getCurrentLevel();

    }

    template<typename K>
    void toArray(std::vector<K*> obj_vect,K* array){
        for(std::size_t i = 0; i < obj_vect.size(); i++){
            array[i] = *(obj_vect[i]);
        }
    }
    
};

struct Game_settings
{
	int nb_player = 1;
	char pseudo_hote[20];
	char pseudo_other[20];
	int drop_rate=25;
	bool ally_shot=false;
	int nb_lives=3;
	char difficulty_str[20] = "easy";
	difficulty diff;
    char pid[10];

};


#endif
