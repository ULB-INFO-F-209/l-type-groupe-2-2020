//
// Created by jean on 19/02/2021.
//

#ifndef GAME_CURRENTGAME_H
#define GAME_CURRENTGAME_H
#include <cstdint>

#include <unistd.h>
#include <ncurses.h>

#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "MapHandler.hpp"
#include "Player.hpp"


// at least 16-bit int 2D vector
typedef struct {
    uint_fast16_t x;
    uint_fast16_t y;
} vec2i;


// simple integer rectangle type
struct rect {
    vec2i offset;
    vec2i bounds;

    uint_fast16_t top() { return offset.y; }
    uint_fast16_t bot() { return offset.y + bounds.y; }
    uint_fast16_t left() { return offset.x; }
    uint_fast16_t right() { return offset.x + bounds.x; }

    uint_fast16_t width() { return bounds.x; }
    uint_fast16_t height() { return bounds.y; }

    bool contains(vec2i a) { return (a.x >= offset.x && a.x < right()) &&
                                    (a.y >= offset.y && a.y < bot()); }
    bool contains(rect r){
        for (uint_fast16_t i = left(); i < right(); ++i) {
            for (uint_fast16_t j = top(); j < bot(); ++j) {
                vec2i test;
                test.x=i;
                test.y=j;
                if (r.contains(test))
                    return true;
            }
        }
        return false;
    }
};


class CurrentGame {
    WINDOW* main_wnd;
    WINDOW* game_wnd;

    rect game_area;
    rect screen_area;

    MapHandler map;

    int tick=0;
    int finalScore1, finalScore2;
    PlayerShip* playership1 = new PlayerShip(10, 5, { {10 - 1, 5 }, { 3, 2 } }, '0',100, 0,100,0);
    PlayerShip* playership2 = new PlayerShip(50, 5, { { 50 - 1, 5 }, { 3, 2 } }, '1',100, 1,100,0);
    Player* player1 = new Player(1);
    Player* player2 = new Player(1);
    std::vector<Player*> listPlayer;

    int in_char = 0;
    bool exit_requested = false;
    bool game_over = false;

    
    // méthodes privées
    void execInput(int in_char, uint_fast16_t x1, uint_fast16_t y1, uint_fast16_t x2, uint_fast16_t y2);
    void heal();
    void saveScore();

    public:
    int getInput(){return in_char;}

    void run();
};


#endif //JEU_CURRENTGAME_H
