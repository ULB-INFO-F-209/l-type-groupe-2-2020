#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>

#include "game.h"

struct {
    vec2i pos;
    char disp_char;
} player1;

struct {
    vec2i pos;
    char disp_char;
} player2;

WINDOW* wnd;

int init() {
    wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();

    // enable function keys
    keypad(wnd, true);

    // disable input blocking
    nodelay(wnd, true);

    // hide cursor
    curs_set(0);

    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    // enable color modification
    start_color();

    // draw box around screen
    attron(A_BOLD);
    box(wnd, 0, 0);
    attroff(A_BOLD);

    return 0;
}


void run() {

    player1.disp_char = '0';
    player1.pos = {10, 5};

    player2.disp_char = '1';
    player2.pos = {50, 5};

    int in_char;

    bool exit_requested = false;

    while(1) {
        in_char = wgetch(wnd);

        mvaddch(player1.pos.y, player1.pos.x, ' ');
        mvaddch(player2.pos.y, player2.pos.x, ' ');

        switch(in_char) {
            case 'q':
                player1.pos.x -= 1;
                break;
            case 'p':
                exit_requested = true;
                break;
            case 'z':
                player1.pos.y -= 1;
                break;
            case 's':
                player1.pos.y += 1;
                break;
            case 'd':
                player1.pos.x += 1;
                break;
            case 'a':
                player1.pos.x-=1;
                player1.pos.y-=1;
                break;
            case 'e':
                player1.pos.x+=1;
                player1.pos.y-=1;
                break;
            case 'c':
                player1.pos.x+=1;
                player1.pos.y+=1;
                break;
            case 'w':
                player1.pos.x-=1;
                player1.pos.y+=1;
                break;
//player2
            case 'f':
                player2.pos.x -= 1;
                break;
            case 't':
                player2.pos.y -= 1;
                break;
            case 'g':
                player2.pos.y += 1;
                break;
            case 'h':
                player2.pos.x += 1;
                break;
            case 'r':
                player2.pos.x-=1;
                player2.pos.y-=1;
                break;
            case 'y':
                player2.pos.x+=1;
                player2.pos.y-=1;
                break;
            case 'n':
                player2.pos.x+=1;
                player2.pos.y+=1;
                break;
            case 'v':
                player2.pos.x-=1;
                player2.pos.y+=1;
                break;

            default:
                break;
        }

        mvaddch(player1.pos.y, player1.pos.x, player1.disp_char);
        mvaddch(player2.pos.y, player2.pos.x, player2.disp_char);

        if(exit_requested) break;

        usleep(10000); // 10 ms

        refresh();
    }
}


void close() {
    endwin();
}
