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


class Interface {
    WINDOW* main_wnd;
    WINDOW* game_wnd;

    rect game_area;
    rect screen_area;
public:
    int init();
    void initialDraw();

};


#endif //GAME_INTERFACE_H
