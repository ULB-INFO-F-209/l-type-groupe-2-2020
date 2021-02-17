/**
 * TODO:
 *  thread pour jouer en même temps
 *  vaisseaux ennemis
 *  collisions:
 *      player:projectile
 *      projectile:projectile
 *      ennemy:projectile
 *  score
 *  si vaisseau alié perd une vie tous les ennemis down
 *  faire des niveaux
 *  enlever static_cast !!
 *  transformer game.cpp en classe
 *  changer vectors en listes
 *  mettre tous les destructors
 *  damage version alexandre
 * ERROR:
 */

#include <unistd.h>
#include <ncurses.h>

#include <cstdint>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "MapHandler.hpp"
#include "game.hpp"
#include "Player.hpp"

WINDOW* main_wnd;
WINDOW* game_wnd;

rect game_area;
rect screen_area;


MapHandler map;

int init() {

    srand(time(0)); // ??????

    main_wnd = initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    
    // hide cursor
    curs_set(0);

    // enable color modification
    start_color();

    
    // define area for screen (default terminal size)
    screen_area = { {0, 0}, {80, 24}};

    // initialize window areas
    int infopanel_height = 4;
    game_wnd = newwin( screen_area.height() - infopanel_height - 2,
                        screen_area.width() - 2,
                        screen_area.top() + 1,
                        screen_area.left() + 1);

    main_wnd = newwin(screen_area.height(), screen_area.width(), 0, 0);

    // define area for movement
    game_area = { {0, 0}, {static_cast<uint_fast16_t>(screen_area.width() - 2), static_cast<uint_fast16_t>(screen_area.height() - infopanel_height - 4)}};

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
    PlayerShip* playership1 = new PlayerShip(10, 5, { {10 - 1, 5 }, { 3, 2 } }, '0',100, 0,10);
    PlayerShip* playership2 = new PlayerShip(50, 5, { { 50 - 1, 5 }, { 3, 2 } }, '1',100, 1,10);
    Player* player1 = new Player(3, 0);
    Player* player2 = new Player(3, 0);
    std::vector<Player*> listPlayer;
    listPlayer.push_back(player1);
    listPlayer.push_back(player2);

    map.playerInit(playership1,playership2);

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

    tick = 0;

    while(1) {

        werase(game_wnd);

        // get input
        in_char = wgetch(main_wnd);
        in_char = tolower(in_char);

        
        uint_fast16_t x1 = playership1->getPos().x;
        uint_fast16_t y1 = playership1->getPos().y;
        uint_fast16_t  x2 = playership2->getPos().x;
        uint_fast16_t y2 = playership2->getPos().y;
        switch(in_char) {
            case 'q':
                if(x1 > game_area.left() + 1)
                    playership1->setPos(x1 - 1, y1);
                break;
            case 'p':
                exit_requested = true;
                break;
            case 'z':
                if(y1 > game_area.top())
                    playership1->setPos(x1, y1 - 1);
                break;
            case 's':
                if(y1 < game_area.bot())
                    playership1->setPos(x1, y1 + 1);
                break;
            case 'd':
                if(x1 < game_area.right() - 2)
                    playership1->setPos(x1 + 1, y1);
                break;
            case 'a':
                if((x1 > game_area.left() + 1) && (y1 > game_area.top())){
                    playership1->setPos(x1 - 1, y1 - 1);}
                break;
            case 'e':
                if((x1 < game_area.right() - 2) && (y1 > game_area.top())){
                    playership1->setPos(x1 + 1, y1 - 1);}
                break;
            case 'c':
                if((x1 < game_area.right() - 2) && (y1 < game_area.bot())){
                    playership1->setPos(x1 + 1, y1 + 1);}
                break;
            case 'w':
                if((x1 > game_area.left() + 1) && (y1 < game_area.bot())){
                    playership1->setPos(x1 - 1, y1 + 1);}
                break;
            case ' ':
                if(playership1->getHp()>0)
                    map.spawnProjectile(playership1->getPos().x, playership1->getPos().y -1, 10, true);
                break;
//player2
            case 'f':
                if(x2 > game_area.left() + 1)
                    playership2->setPos(x2 - 1 , y2);
                break;
            case 't':
                if(y2 > game_area.top())
                    playership2->setPos(x2, y2 - 1);;
                break;
            case 'g':
                if(y2 < game_area.bot())
                    playership2->setPos(x2 , y2 + 1);
                break;
            case 'h':
                if(x2< game_area.right() - 2)
                    playership2->setPos(x2 + 1 , y2);
                break;
            case 'r':
                if((x2 > game_area.left() + 1) && (y2 > game_area.top())){
                    playership2->setPos(x2 - 1 , y2 - 1);}
                break;
            case 'y':
                if((x2 < game_area.right() - 2) && (y2 > game_area.top())){
                    playership2->setPos(x2 + 1 , y2 - 1);}
                break;
            case 'n':
                if((x2 < game_area.right() - 2) && (y2 < game_area.bot())){
                    playership2->setPos(x2 + 1 , y2 + 1);}
                break;
            case 'v':
                if((x2 > game_area.left() + 1) && (y2 < game_area.bot())){
                    playership2->setPos(x2 - 1 , y2 + 1);}
                break;
            case 'm':
                if(playership2->getHp()>0)
                    map.spawnProjectile(playership2->getPos().x, playership2->getPos().y -1, 10, true);
                break;
            default:
                break;
        }
        // update object field
        if(tick % 7 == 0)
            map.update(MapObject::star, tick);
        if(tick % 7 == 0)
            map.update(MapObject::projectile, tick);
        if(tick > 100 && tick %50  == 0) {
            map.update(MapObject::obstacle, tick);
        }
        if (tick > 100 && tick %150 ==0)
            map.update(MapObject::enemyship, tick);

        map.enemyShoot(tick);

        map.updatePlayerBounds();     // update player bounds
        map.checkCollision();

        if (player1->getnLives() < 1 && player2->getnLives() < 1)
            game_over = true;

        // draw stars
        for(auto s : map.getStars()){   
            mvwaddch(game_wnd, s->getPos().y, s->getPos().x, '.');        
        }
        // draw obstacle
        for(auto o : map.getObstacles()){
                wattron(game_wnd, A_BOLD);
                mvwaddch(game_wnd, o->getPos().y, o->getPos().x, '*');
                wattroff(game_wnd, A_BOLD);

        }
        for(auto p : map.getProjectiles()){

            mvwaddch(game_wnd, p->getPos().y, p->getPos().x, '#');
        }
        // draw ennemies
        for(auto e :map.getEnemy()){
            wattron(game_wnd, A_BOLD);
            mvwaddch(game_wnd, e->getPos().y, e->getPos().x, e->getChar());
            wattroff(game_wnd, A_BOLD);


            wattron(game_wnd, A_ALTCHARSET);
            mvwaddch(game_wnd, e->getPos().y, e->getPos().x - 1, ACS_LARROW);
            mvwaddch(game_wnd, e->getPos().y, e->getPos().x + 1, ACS_RARROW);
            wattroff(game_wnd, A_ALTCHARSET);
        }


        for( PlayerShip* p : map.getListPlayer()){
            // draw player body
            
            wattron(game_wnd, A_BOLD);
            mvwaddch(game_wnd, p->getPos().y, p->getPos().x, p->getChar());
            wattroff(game_wnd, A_BOLD);


            wattron(game_wnd, A_ALTCHARSET);
            mvwaddch(game_wnd, p->getPos().y, p->getPos().x - 1, ACS_LARROW);
            mvwaddch(game_wnd, p->getPos().y, p->getPos().x + 1, ACS_RARROW);
            if(listPlayer.at(p->getPlayerNb())->getnLives() > 0){
                if(p->getHp()<=0 && p->getIsAlive()){
                    p->setisAlive(false);
                    p->setKillTime(tick);
                    listPlayer.at(p->getPlayerNb())->setnLives(listPlayer.at(p->getPlayerNb())->getnLives() - 1);
                    
                }
                if(tick==p->getKillTime()+300 && !p->getIsAlive()){
            
                    p->setisAlive(true);
                    p->setHp(100);
        
                }
            }

            if(listPlayer.at(p->getPlayerNb())->getnLives() > 0){

                if(tick % 100 < 50 && p->getHp()<=0 && tick<p->getKillTime()+300) {
                    wattron(game_wnd, A_BOLD);
                    mvwaddch(game_wnd, p->getPos().y, p->getPos().x, ' ');
                    wattroff(game_wnd, A_BOLD);

                    wattron(game_wnd, A_ALTCHARSET);
                    mvwaddch(game_wnd, p->getPos().y, p->getPos().x - 1, ' ');
                    mvwaddch(game_wnd, p->getPos().y, p->getPos().x + 1, ' ');
                }

                // draw engines flames
                if((tick % 10) / 3 && p->getHp()>0) {
                    wattron(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
                    mvwaddch(game_wnd, p->getPos().y + 1, p->getPos().x, ACS_UARROW);
                    mvwaddch(game_wnd, p->getPos().y + 1, p->getPos().x, ACS_UARROW);
                    wattroff(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
                }
            }


            wattroff(game_wnd, A_ALTCHARSET);

            if(listPlayer.at(p->getPlayerNb())->getnLives() < 1){
                map.erase(p->getPlayerNb(), MapObject::playership);
            }  
        }

        // draw UI elements
        // energy bar player1
        wmove(main_wnd, 20, 1);
        whline(main_wnd, ' ', 25); // health bar is 25 chars long
        wmove(main_wnd, 20, 1);
        drawEnergyBar(playership1->getHp());

        // energy bar player2
        wmove(main_wnd, 20, 54);
        whline(main_wnd, ' ', 25); // health bar is 25 chars long
        wmove(main_wnd, 20, 54);
        drawEnergyBar(playership2->getHp());

        // draw static string to hold percentage
        mvwprintw(main_wnd, 21, 1, "  - P1 HP     -");
        mvwprintw(main_wnd, 21, 54, "  - P2 HP     -");
        mvwprintw(main_wnd, 21, 17, "lives: %i",player1->getnLives());
        mvwprintw(main_wnd, 21, 70, "lives: %i",player2->getnLives());

        // draw numeric percentage player 1
        wattron(main_wnd, A_BOLD);
        if(playership1->getHp() <= 25) {
            wattron(main_wnd, COLOR_PAIR(4));
            if(tick % 100 < 50)
                mvwprintw(main_wnd, 21, 11, "%i%%", playership1->getHp()); 
            wattroff(main_wnd, COLOR_PAIR(4));
        } else
            mvwprintw(main_wnd, 21, 11, "%i%%", playership1->getHp()); 
        wattroff(main_wnd, A_BOLD);

        // draw numeric percentage player 2
        wattron(main_wnd, A_BOLD);
        if(playership2->getHp() <= 25) {
            wattron(main_wnd, COLOR_PAIR(4));
            if(tick % 100 < 50)
                mvwprintw(main_wnd, 21, 64, "%i%%", playership2->getHp()); 
            wattroff(main_wnd, COLOR_PAIR(4));
        } else
            mvwprintw(main_wnd, 21, 64, "%i%%", playership2->getHp()); 
        wattroff(main_wnd, A_BOLD);

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

void drawEnergyBar(int a) {

    int col_pair = 1;
    for(int i = 0; i < a; i+=4) {
        if(i > 100)
            col_pair = 5; // blue
        else if(i > 50)
            col_pair = 2; // green
        else if(i > 25)
            col_pair = 3; // yellow
        else
            col_pair = 4; // red

        wattron(main_wnd, COLOR_PAIR(col_pair));
        wattron(main_wnd, A_BOLD);
        waddch(main_wnd, '/');
        wattroff(main_wnd, A_BOLD);
        wattroff(main_wnd, COLOR_PAIR(col_pair));
    }
}