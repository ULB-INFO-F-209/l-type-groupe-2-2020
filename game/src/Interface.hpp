//
// Created by jean on 19/02/2021.
//

#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H
#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "MapHandler.hpp"


class Interface  {
    WINDOW* main_wnd;
    WINDOW* game_wnd;

    rect game_area;
    rect screen_area;
public:
    Interface();
    int init();
    void erase();
    void initialDraw();
    void display(MapHandler* m,int tick, std::vector<Player *> *listPlayer);
    void drawStar(MapHandler* m);
    void drawObstacle(MapHandler* m);
    void drawEnemy(MapHandler* m);
    void drawProjectile(MapHandler* m);
    void drawPlayer(MapHandler* m,int tick,std::vector<Player*>* listPlayer);
    void drawUI(MapHandler *m,PlayerShip* playership1,PlayerShip* playership2, Player* player1,Player* player2,int score1, int score2);
    void refresh_wnd();
    void close();
    void drawEnergyBar(int);
};


#endif //GAME_INTERFACE_H
