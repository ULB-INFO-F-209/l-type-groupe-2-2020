#ifndef GAME_CONSTANTE_H
#define GAME_CONSTANTE_H

#include "Rect.hpp"
#include "MapHandler.hpp"
#include <vector>


namespace GameConstate{
    const int INIT_SCORE = 0;

    const int J1_NUMBER = 0;
    const int J2_NUMBER = 1;
    const rect J1_RECT{ {10 - 1, 5 }, { 3, 2 } };
    const rect J2_RECT{ { 50 - 1, 5 }, { 3, 2 } };
    const int J1_START_X = 10;
    const int J1_START_Y = 5;
    const int J2_START_X = 50;
    const int J2_START_Y = 5;
    constexpr char J1_CHAR_REPR = '0';
    constexpr char J2_CHAR_REPR = '1';
    const int CONLLISION_DAMAGE = 100;
    const int PLAYER_HP = 100;



}

namespace GameSetting{

    struct settingClient;
    struct settingServer;
}

struct GameSetting::settingServer{
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

struct GameSetting::settingClient{
    MapHandler* object_map; 
};
#endif