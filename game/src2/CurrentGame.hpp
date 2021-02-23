//
// Created by jean on 19/02/2021.
//

#ifndef GAME_CURRENTGAME_H
#define GAME_CURRENTGAME_H

#include <unistd.h>
#include <ncurses.h>

#include <string>
#include <stdlib.h>
//#include <time.h>
#include "MapHandler.hpp"
#include "Interface.hpp"
#include "InternGameObject.hpp"
//class Interface;

class CurrentGame {
    
    rect game_area;
    rect screen_area;

    MapHandler map;

    int tick=0;
    int finalScore1, finalScore2;

    PlayerShip* playership1 = new PlayerShip(10, 5, { {10 - 1, 5 }, { 3, 2 } }, '0',100, 0,100,0);
    PlayerShip* playership2 = new PlayerShip(50, 5, { { 50 - 1, 5 }, { 3, 2 } }, '1',100, 1,100,0);
    Player* player1 = new Player(1);
    Player* player2 = new Player(1);
    std::vector<Player*> listPlayer=std::vector<Player*>();

    int in_char = 0;
    bool exit_requested = false;
    bool game_over = false;

    
    // méthodes privées
    void execInput(int in_char, uint_fast16_t x1, uint_fast16_t y1, uint_fast16_t x2, uint_fast16_t y2);
    void heal();
    void saveScore();

    public:
    CurrentGame()=default;
    int getInput(){return in_char;}

    void run();
};


#endif //JEU_CURRENTGAME_H
