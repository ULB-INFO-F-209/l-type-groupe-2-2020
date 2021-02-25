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
    int dropRate;
    difficulty difficulte;

    MapHandler map{80};

    int tick=0;
    int finalScore1{};
    int finalScore2{};

    PlayerShip* playership1 = new PlayerShip(10, 5, { {10 - 1, 5 }, { 3, 2 } }, '0',100, 0,100,0);
    Player* player1 = new Player(3);

    if (twoPlayers){
        PlayerShip* playership2 = new PlayerShip(50, 5, { { 50 - 1, 5 }, { 3, 2 } }, '1',100, 1,100,0);
        Player* player2 = new Player(3);
    }
    std::vector<Player*> listPlayer=std::vector<Player*>();

    int in_char = 0;
    bool exit_requested = false;
    bool game_over = false;


    // méthodes privées
    void execInput(int inChar, uint_fast16_t x1, uint_fast16_t y1, uint_fast16_t x2, uint_fast16_t y2);
    void heal();
    void saveScore();

public:
    CurrentGame()=default;
    CurrentGame(bool twoP, int dropR, difficulty diff) {twoPlayers=twoP; dropRate=dropR; difficulte=diff;}
    int getInput(){return in_char;}

    void run();
};


#endif //JEU_CURRENTGAME_H
