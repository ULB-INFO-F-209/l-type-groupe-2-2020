#ifndef SETTINGSERVER_H
#define SETTINGSERVER_H
#include "MapHandler.hpp"
#include <vector>
#include <iostream>

<<<<<<< HEAD
typedef struct settingServer;
typedef struct theSettings;
=======
>>>>>>> systeme

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
    bool game_over = false;
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

<<<<<<< HEAD
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

=======
>>>>>>> systeme
struct Game_settings
{
	int nb_player = 1;
	char pseudo_hote[20];
	char pseudo_other[20] = {"Null"};
	int drop_rate=100;
	bool ally_shot=false;
	int nb_lives=1;
	char difficulty_str[20] = "easy";
	difficulty diff{easy};
    char pid[10];

};

class settingArray2{
    
    Player list_player[2];
    
public:
    Player* getListPlayer(){return &(list_player[0]);};
    settingArray2()=default;
    ~settingArray2()=default;
    settingArray2(theSettings* obj){
        
        if (obj->list_player == nullptr){
            std::cout << "il y a un probleme :ç";

        }else{
            toArray((obj->list_player),list_player);
        }

        
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
