/**
 * TODO:
 *  thread pour jouer en même temps
 *
 */

#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>
#include <vector>
#include "MapHandler.hpp"
#include "game.hpp"

WINDOW* main_wnd;
WINDOW* game_wnd;

rect game_area;
rect screen_area;

vec2ui cur_size;


struct {
    vec2i pos;
    rect bounds;
    char disp_char;
    int energy;
} player1;

struct {
    vec2i pos;
    rect bounds;
    char disp_char;
    int energy;
} player2;



MapHandler map;

int init() {
    main_wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    
    // hide cursor
    curs_set(0);

    // enable color modification
    start_color();

    screen_area = { {0, 0}, {80, 24}};

    int infopanel_height = 4;
    game_wnd = newwin( screen_area.height() - infopanel_height - 2,
                        screen_area.width() - 2,
                        screen_area.top() + 1,
                        screen_area.left() + 1);

    main_wnd = newwin(screen_area.height(), screen_area.width(), 0, 0);

    game_area = { {0, 0}, {screen_area.width() - 2, screen_area.height() - infopanel_height - 4}};

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_BLUE, COLOR_BLACK);

    // enable function keys
    keypad(main_wnd, true);
    keypad(game_wnd, true);

    // disable input blocking
    nodelay(main_wnd, true);
    nodelay(game_wnd, true);


    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }

    return 0;
}


void run() {

    int tick;

    // init character
    player1.disp_char = '0';
    player1.pos = {10, 5};

    player2.disp_char = '1';
    player2.pos = {50, 5};

    map.setBounds(game_area);

    int in_char = 0;
    bool exit_requested = false;
    bool game_over = false;

    //frame around screen
    wattron(main_wnd, A_BOLD);
    box(main_wnd, 0, 0);
    wattroff(main_wnd, A_BOLD);

    // horizontal diving line
    wmove(main_wnd, game_area.bot() + 3, 1);
    whline(main_wnd, '-', screen_area.width()- 2);

    // initial draw

    wrefresh(main_wnd);
    wrefresh(game_wnd);

    /*uint_fast16_t maxx, maxy;

    getmaxyx(game_wnd, maxy, maxx);
    rect a = { {0, 0}, {maxx , maxy} };
    map.setBounds(a);

    int in_char;
    bool exit_requested = false;*/

    tick = 0;

    while(1) {

        werase(game_wnd);

        // get input
        in_char = wgetch(main_wnd);
        in_char = tolower(in_char);

        /*mvaddch(player1.pos.y, player1.pos.x, ' ');
        mvaddch(player2.pos.y, player2.pos.x, ' ');

        for(auto s : map.getData()){
            if (s->typ==MapObject::star){
                mvaddch(s->getPos().y, s->getPos().x, ' ');
            }
        }*/

        switch(in_char) {
            case 'q':
                if(player1.pos.x > game_area.left() + 1)
                    player1.pos.x -= 1;
                break;
            case 'p':
                exit_requested = true;
                break;
            case 'z':
                if(player1.pos.y > game_area.top())
                    player1.pos.y -= 1;
                break;
            case 's':
                if(player1.pos.y < game_area.bot() + 1)
                    player1.pos.y += 1;
                break;
            case 'd':
                if(player1.pos.x < game_area.right() - 2)
                    player1.pos.x += 1;
                break;
            case 'a':
                if((player1.pos.x > game_area.left() + 1) && (player1.pos.y > game_area.top())){
                    player1.pos.x-=1;
                    player1.pos.y-=1;}
                break;
            case 'e':
                if((player1.pos.x < game_area.right() - 2) && (player1.pos.y > game_area.top())){
                    player1.pos.x+=1;
                    player1.pos.y-=1;}
                break;
            case 'c':
                if((player1.pos.x < game_area.right() - 2) && (player1.pos.y < game_area.bot() + 1)){
                    player1.pos.x+=1;
                    player1.pos.y+=1;}
                break;
            case 'w':
                if((player1.pos.x > game_area.left() + 1) && (player1.pos.y < game_area.bot() + 1)){
                    player1.pos.x-=1;
                    player1.pos.y+=1;}
                break;
//player2
            case 'f':
                if(player2.pos.x > game_area.left() + 1)
                    player2.pos.x -= 1;
                break;
            case 't':
                if(player2.pos.y > game_area.top())
                    player2.pos.y -= 1;
                break;
            case 'g':
                if(player2.pos.y < game_area.bot() + 1)
                    player2.pos.y += 1;
                break;
            case 'h':
                if(player2.pos.x < game_area.right() - 2)
                    player2.pos.x += 1;
                break;
            case 'r':
                if((player2.pos.x > game_area.left() + 1) && (player2.pos.y > game_area.top())){
                    player2.pos.x-=1;
                    player2.pos.y-=1;}
                break;
            case 'y':
                if((player2.pos.x < game_area.right() - 2) && (player2.pos.y > game_area.top())){
                    player2.pos.x+=1;
                    player2.pos.y-=1;}
                break;
            case 'n':
                if((player2.pos.x < game_area.right() - 2) && (player2.pos.y < game_area.bot() + 1)){
                    player2.pos.x+=1;
                    player2.pos.y+=1;}
                break;
            case 'v':
                if((player2.pos.x > game_area.left() + 1) && (player2.pos.y < game_area.bot() + 1)){
                    player2.pos.x-=1;
                    player2.pos.y+=1;}
                break;

            default:
                break;
        }
        // update object field
        if(tick % 7 == 0)
            map.update(MapObject::star, tick);

        if(tick > 100 && tick %50  == 0)
            map.update(MapObject::obstacle, tick);
            
        // update player bounds
        player1.bounds = { { player1.pos.x -1, player1.pos.y}, {3, 1}};
        player2.bounds = { { player2.pos.x -1, player2.pos.y}, {3, 1}};
        
        // remove obstacle if collided
        for(size_t i = 0; i < map.getData(MapObject::obstacle).size(); i++){
            if(player1.bounds.contains(map.getData(MapObject::obstacle).at(i)->getPos())){
                map.erase(i, MapObject::obstacle);
            }
            if(player2.bounds.contains(map.getData(MapObject::obstacle).at(i)->getPos())){
                map.erase(i, MapObject::obstacle);
            }
        }

        // draw object fields
        for(auto s : map.getData(MapObject::star)){   
            mvwaddch(game_wnd, s->getPos().y, s->getPos().x, '.');        
        }

        for(auto o : map.getData(MapObject::obstacle)){
                wattron(game_wnd, A_BOLD);
                mvwaddch(game_wnd, o->getPos().y, o->getPos().x, '*');
                wattroff(game_wnd, A_BOLD);

        }

        // draw player body
        wattron(game_wnd, A_BOLD);
        mvwaddch(game_wnd, player1.pos.y, player1.pos.x, player1.disp_char);
        wattroff(game_wnd, A_BOLD);
        wattron(game_wnd, A_BOLD);
        mvwaddch(game_wnd, player2.pos.y, player2.pos.x, player2.disp_char);
        wattroff(game_wnd, A_BOLD);

        wattron(game_wnd, A_ALTCHARSET);
        mvwaddch(game_wnd, player1.pos.y, player1.pos.x - 1, ACS_LARROW);
        mvwaddch(game_wnd, player1.pos.y, player1.pos.x + 1, ACS_RARROW);
        mvwaddch(game_wnd, player2.pos.y, player2.pos.x - 1, ACS_LARROW);
        mvwaddch(game_wnd, player2.pos.y, player2.pos.x + 1, ACS_RARROW);

        // draw engines flames
        if((tick % 10) / 3){
            wattron(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
            mvwaddch(game_wnd, player1.pos.y + 1, player1.pos.x, ACS_UARROW);
            mvwaddch(game_wnd, player2.pos.y + 1, player2.pos.x, ACS_UARROW);
            wattroff(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
        }

        wattroff(game_wnd, A_ALTCHARSET);

        //refresh all
        wrefresh(main_wnd);
        wrefresh(game_wnd);
        if(exit_requested || game_over) break;

        tick++;
        usleep(10000); // 10 ms

        refresh();
    }
    close();
}


void close() {
    delwin(main_wnd);
    delwin(game_wnd);
    endwin();
}
