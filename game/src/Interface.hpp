//
// Created by jean on 19/02/2021.
//

#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H
#include <unistd.h>
#include <ncurses.h>

//#include <cstdint>
#include <string>
#include <stdlib.h>
//#include <time.h>
#include <vector>

#include "Rect.hpp"
#include "Player.hpp"
#include "MapHandler.hpp"

//class MapHandler;
//class PlayerShip;

class Interface  {
    WINDOW* main_wnd;
    WINDOW* game_wnd;

    rect game_area;
    rect screen_area;
public:
    Interface();
    int init();
    void initialDraw();
    void display(MapHandler *m,int tick, std::vector<Player *> *listPlayer,PlayerShip* playership1,PlayerShip* playership2, Player* player1,Player* player2,int score1, int score2);
    void drawStar(MapHandler* m);
    void drawObstacle(MapHandler* m);
    void drawEnemy(MapHandler* m);
    void drawProjectile(MapHandler* m);
    void drawPlayer(MapHandler* m,int tick,std::vector<Player*>* listPlayer);
    void drawUI(MapHandler *m,PlayerShip* playership1,PlayerShip* playership2, Player* player1,Player* player2,int score1, int score2,int tick);
    void drawBonus(MapHandler* m);
    void drawBoss(MapHandler* m);
    void drawNewLevel(MapHandler* m, int tick);
    void refresh_wnd();
    void close();
    void drawEnergyBar(int);
    WINDOW* get_main_window(){return main_wnd;};
    WINDOW* get_game_window(){return game_wnd;};
    rect get_game_area(){return game_area;};
    rect get_screen_area(){return screen_area;};
};


#endif //GAME_INTERFACE_H
