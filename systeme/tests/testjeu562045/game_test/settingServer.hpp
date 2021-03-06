#ifndef SETTINGSERVER_H
#define SETTINGSERVER_H
#include "MapHandler.hpp"
#include <vector>
#include <iostream>

typedef struct settingServer;
typedef struct theSettings;

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

struct theSettings{
    std::vector<Projectile*> *projectilesEnemy_set=nullptr;
    std::vector<Boss*> *boss_set =nullptr;
    std::vector<Star*> *stars_set=nullptr;
    std::vector<Obstacle*> *obstacles_set=nullptr;
    std::vector<Projectile*> *projectiles_set=nullptr;
    std::vector<PlayerShip*> *player_ships_set=nullptr;
    std::vector<EnemyShip*> *enemy_ships_set=nullptr;
    std::vector<Bonus*> *bonuses_set=nullptr;
    std::vector<Player*>* list_player=nullptr;
    int score_j1;
    int score_j2;
    bool two_players;
    int level_tick ;
    int current_level;
    
    int tick;
    bool game_over;
    theSettings()=default;
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
    Star stars_set[100];
    Obstacle obstacles_set[100];
    Projectile projectiles_set[100];
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
    settingArray()=default;
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
	difficulty diff{easy};
    char pid[10];

};

class settingArray2{
    // int boss_set_size;
    // int stars_set_size;
    // int obstacles_set_size;
    // int projectiles_set_size;
    // int projectilesEnemy_set_size;
    // int player_ships_set_size;
    // int enemy_ships_set_size; 
    // int bonnuses_set_size;
    // int list_player_size;
    // Boss boss_set[1];
    // Star stars_set[50];
    // Obstacle obstacles_set[50];
    // Projectile projectiles_set[50];
    // Projectile projectilesEnemy_set[50];
    // PlayerShip player_ships_set[2];
    //EnemyShip enemy_ships_set[65]; 
    //MapObject bonnuses_set[2];

    Player list_player[2];
    // int score_j1;
    // int score_j2;
    // bool two_players;
    // // std::vector<Player*>* list_player;
    // int tick;
    // bool game_over;
    // int level_tick;
    // int current_level;
    //settingArray2(int a):boss_set_size(a){};
public:
    Player* getListPlayer(){return &(list_player[0]);};
    settingArray2()=default;
    ~settingArray2()=default;
    settingArray2(theSettings* obj){
        
        // boss_set_size= obj->boss_set==nullptr? 0:obj->boss_set->size();
        // stars_set_size= obj->stars_set==nullptr? 0:obj->stars_set->size();
        // obstacles_set_size= obj->obstacles_set==nullptr? 0: obj->obstacles_set->size();
        // projectiles_set_size= obj->obstacles_set== nullptr ? 0 :obj->projectiles_set->size();
        // projectilesEnemy_set_size= obj->projectilesEnemy_set ==nullptr ? 0: obj->projectilesEnemy_set->size();
        // player_ships_set_size= obj->player_ships_set==nullptr? 0: obj->player_ships_set->size();
        // enemy_ships_set_size= obj->enemy_ships_set==nullptr? 0: obj->enemy_ships_set->size(); 
        // bonnuses_set_size=obj->bonuses_set==nullptr? 0: obj->bonuses_set->size() ;
        // list_player_size=obj->list_player==nullptr? 0:obj->list_player->size();                    
                    
        // if(obj->boss_set != nullptr)
        //     toArray((obj->boss_set),boss_set);
        // if(obj->stars_set != nullptr)
        //     toArray((obj->stars_set),stars_set);
        // if(obj->obstacles_set != nullptr)
        //     toArray((obj->obstacles_set),obstacles_set);
        // if(obj->projectiles_set != nullptr)
        //     toArray((obj->projectiles_set),projectiles_set);
        // if(obj->projectilesEnemy_set != nullptr)
        //     toArray((obj->projectilesEnemy_set),projectilesEnemy_set);
        // if(obj->enemy_ships_set != nullptr)
        //     toArray((obj->enemy_ships_set),enemy_ships_set);
        // if(obj->player_ships_set != nullptr)
        //      toArray((obj->player_ships_set),player_ships_set);
        
        
        /*std::cout << "on est ici" << std::endl;
        for(int i=0; i < 2; i++){
            bonnuses_set[i] = Bonus();
        }*/

        if (obj->list_player == nullptr){
            std::cout << "il y a un probleme :ç";

        }else{
            toArray((obj->list_player),list_player);
        }

        // score_j1 = obj->score_j1;
        // score_j2 = obj->score_j2;
        // two_players =obj->two_players;
        // game_over = obj->game_over;
        
        // tick = obj->tick;
        // level_tick = obj->level_tick;
        // current_level = obj->current_level;
        std::cout << "C'est bon " << std::endl;
    }

    template<typename K>
    void toArray(std::vector<K*>* obj_vect,K* array){
        for(std::size_t i = 0; i < obj_vect->size(); i++){
            std::cout << "Copy n° "<<i;
            K obj_tmp = *(obj_vect->at(i));
            array[i] = obj_tmp;
            std::cout <<"  "<< &(array[i])<<std::endl<< obj_vect->at(i)<<std::endl;
        }
    }
};

#endif