#ifndef SETTINGSERVER_H
#define SETTINGSERVER_H
#include "MapHandler.hpp"
#include <vector>
#include <iostream>

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


#endif
