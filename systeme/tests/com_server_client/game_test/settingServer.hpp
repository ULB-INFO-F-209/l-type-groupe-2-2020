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

#endif