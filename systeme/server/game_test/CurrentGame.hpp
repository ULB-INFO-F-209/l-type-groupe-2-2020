//
// Created by jean on 19/02/2021.
//

#ifndef GAME_CURRENTGAME_H
#define GAME_CURRENTGAME_H

#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include "MapHandler.hpp"
#include "Interface_game.hpp"
#include "InternGameObject.hpp"
#include "GameConstante.hpp"
#include "settingServer.hpp"

class CurrentGame {

    rect game_area;
    rect screen_area;
    bool twoPlayers;
    bool friendlyFire;
    int dropRate;
    difficulty dif;

    MapHandler map;

    int tick;
    int finalScore1;
    int finalScore2;

    PlayerShip* playership1;
    Player* player1;

    PlayerShip* playership2;
    Player* player2;
    
    std::vector<Player*> listPlayer;

    int in_char;
    bool exit_requested;
    bool game_over;

    // méthodes privées
    void execInput(int inChar, uint_fast16_t x1, uint_fast16_t y1, bool firstPlayer);
    void heal();
    void saveScore();

public:
    CurrentGame()=delete;
    CurrentGame(const CurrentGame&)=delete;
    CurrentGame& operator=(const CurrentGame&)=delete;
    CurrentGame(Game_settings game_sett);
    //void run_test(theSettings* setting_to_fill,char in_char);
    int getInput() const{return in_char;}
    void getSettings(settingServer* settings);
    std::string run_server(char move_to_exec,settingServer* settings);
    void run_client(int  parametre_to_change,settingServer* settings);
    void execInput(int inChar, uint_fast16_t x1, uint_fast16_t y1, bool firstPlayer,std::string to_fill);
    void spawnObstacle(int posx);
    void spawnEnemy(int posx,int tick);
    void spawnBoss(int tick);
    void spawnBonus(int posx,int posy,int rand_int);
    void set_client_tick(int t);
    

    ~CurrentGame(){delete player1;delete playership1; if(twoPlayers){delete playership2; delete player2;} }
    void run();
};


#endif //JEU_CURRENTGAME_H

