//
// Created by jean on 19/02/2021.
//

#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H
#include <unistd.h>
#include <ncurses.h>
#include <string>
#include <cstdlib>
#include <vector>
#include "Rect.hpp"
#include "Player.hpp"
#include "MapHandler.hpp"

class Interface_game  {
    WINDOW* main_wnd;
    WINDOW* game_wnd;
    rect game_area;
    rect screen_area;
public:
    Interface_game();
    int init();
    void initialDraw();
    void display(MapHandler *m,int tick, std::vector<Player *> *listPlayer,PlayerShip* playership1,PlayerShip* playership2, Player* player1,Player* player2,int score1, int score2,bool twoPlayers);

    void drawStar(MapHandler* m);
    void drawStar(Star*,std::size_t);

    void drawObstacle(Obstacle*,std::size_t);
    void drawObstacle(MapHandler* m);

    void drawEnemy(MapHandler* m, int tick, std::vector<Player*>* listPlayer);
    void drawEnemy(EnemyShip* m, int tick, Player* p,PlayerShip* ps,std::size_t size_m,std::size_t size_ps);

    void drawProjectile(MapHandler* m);
    void drawProjectile(Projectile*p,std::size_t size_p,Projectile*pe,std::size_t size_pe);

    void drawPlayer(MapHandler* m,int tick,std::vector<Player*>* listPlayer);
    void drawPlayer(PlayerShip* ps,int tick,Player* listPlayer,std::size_t size_m,std::size_t size_p);

    void drawUI(PlayerShip* playerships, Player* players, int score1, int score2,int tick, bool twoPlayers,int current_level,std::size_t size_ps);
    void drawUI(MapHandler *m,PlayerShip* playership1,PlayerShip* playership2, Player* player1,Player* player2,int score1, int score2,int tick, bool twoPlayers);
    
    void drawBonus(MapHandler* m);
    void drawBonus(Bonus* b,std::size_t size_b);

    void drawBoss(MapHandler* m);
    void drawBoss(Boss *bs,std::size_t size_bs);

    void drawNewLevel(int tick, int level_tick,int current_level);
    void drawNewLevel(MapHandler* m, int tick);

    void drawGameOver(MapHandler* m, int score1);
    void drawGameOver(int score);

    void refresh_wnd();
    void close();
    void drawEnergyBar(int);
    WINDOW* get_main_window(){return main_wnd;};
    WINDOW* get_game_window(){return game_wnd;};
    rect get_game_area(){return game_area;};
    rect get_screen_area(){return screen_area;};

};


#endif //GAME_INTERFACE_H

