//
// Created by jean on 19/02/2021.
//

#ifndef GAME_CURRENTGAME_H
#define GAME_CURRENTGAME_H

#include <unistd.h>
#include <ncurses.h>

#include <string>
//#include <stdlib.h>
#include <cstdlib>
#include "MapHandler.hpp"
#include "Interface.hpp"
#include "InternGameObject.hpp"
#include "GameConstante.hpp"
#include <iostream>
//class Interface;



class CurrentGame {

    rect game_area;
    rect screen_area;
    bool twoPlayers;
    bool friendlyFire;
    int dropRate;
    difficulty diff{};

    MapHandler map;

    int tick=0;
    int finalScore1{};
    int finalScore2{};

    PlayerShip* playership1;
    Player* player1;

    
    PlayerShip* playership2 = nullptr;
    Player* player2 = nullptr;
    
    std::vector<Player*> listPlayer=std::vector<Player*>();

    int in_char = 0;
    bool exit_requested = false;
    bool game_over = false;


    // méthodes privées
    void execInput(int inChar, uint_fast16_t x1, uint_fast16_t y1, bool firstPlayer);
    void heal();
    void saveScore();

public:
    CurrentGame()=default;
    CurrentGame(bool twoP, int dropR, difficulty d, bool ff):map(dropR,d),twoPlayers(twoP),dropRate(dropR),diff(diff),friendlyFire(ff) {}
    CurrentGame(bool twoP, int dropR, difficulty diff, bool ff, bool server,Interface * anInterface):map(dropR,diff),twoPlayers(twoP),dropRate(dropR),diff(diff),friendlyFire(ff) {
        
        if (server){
            playership1 = new PlayerShip(10, 5, { {10 - 1, 5 }, { 3, 2 } }, '0',100, 0,100,0);
            player1 = new Player(1);
            listPlayer.push_back(player1);

            if(twoPlayers){
                playership2 = new PlayerShip(50, 5, { { 50 - 1, 5 }, { 3, 2 } }, '1',100, 1,100,0);
                player2 = new Player(1);
                listPlayer.push_back(player2);
            }
            map.setBounds(anInterface->get_game_area());
            game_area = anInterface->get_game_area();
            screen_area = anInterface->get_screen_area();
            
        }
    }

    int getInput(){return in_char;}
    void delPlayer();
    void run();
    void get_settings(GameSetting::settingServer* obj){
        obj->object_map = &map;
        obj->object_playership1 = playership1; 
        obj->object_playership2 = playership2;
        obj->score_j1 =  playership1->getScore();
        obj->score_j2 =  twoPlayers ? playership2->getScore() :0;
        obj->two_players = twoPlayers; 
        obj->object_player1 =  player1;
        obj->object_player2 = player2;
        obj->list_player = &listPlayer; 
        obj->tick = tick; 
        obj->game_over = game_over;};
    void run_test(Interface* ,GameSetting::settingServer*);
    void change_level(){
        if(map.getLevelTick() != 0 && tick <= map.getLevelTick() + 600 && tick > map.getLevelTick()+100){
            //anInterface->drawNewLevel(&map, tick);
            if(tick == map.getLevelTick() + 600) {
                map.changeLevel();
                map.setChangingLevel(false);
            }
        }
    }
};


#endif //JEU_CURRENTGAME_H
