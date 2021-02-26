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

enum difficulty{easy, medium, hard};

class CurrentGame {

    rect game_area;
    rect screen_area;
    bool twoPlayers;
    bool friendlyFire;
    int dropRate;
    difficulty difficulte;

    MapHandler map{80};

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
    CurrentGame(bool twoP, int dropR, difficulty diff, bool ff) {twoPlayers=twoP; dropRate=dropR; difficulte=diff; friendlyFire=ff;}
    int getInput(){return in_char;}

    void run();
};


#endif //JEU_CURRENTGAME_H
