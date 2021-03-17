/**
 * TODO:
 *  thread pour jouer en même temps (Aïssa)
 *  enlever static_cast !!
 *  transformer game.cpp en classe
 *  damage version alexandre
 *  couleur
 *  ajouter effet explosion
 * ERROR:
 */

#include <unistd.h>
#include <ncurses.h>
#include <cstdint>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "MapHandler.hpp"
#include "game.hpp"
#include "Player.hpp"

WINDOW* main_wnd;
WINDOW* game_wnd;

rect game_area;
rect screen_area;

MapHandler map(80); //passé en param par le client

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

    wresize(main_wnd, screen_area.height(), screen_area.width());

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
    init_pair(6,COLOR_WHITE,COLOR_BLACK);

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
    int finalScore1, finalScore2;
    PlayerShip* playership1 = new PlayerShip(10, 5, { {10 - 1, 5 }, { 3, 2 } }, '0',100, 0,100,0);
    PlayerShip* playership2 = new PlayerShip(50, 5, { { 50 - 1, 5 }, { 3, 2 } }, '1',100, 1,100,0);
    Player* player1 = new Player(1);
    Player* player2 = new Player(1);
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
                if(playership1->getHp()>0 && playership1->getCurrentBonus()!=minigun)
                    map.spawnProjectile(playership1->getPos().x, playership1->getPos().y, playership1->getShootDamage(), true, 10, 1);
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
                if(playership2->getHp()>0 && playership2->getCurrentBonus()!=minigun)
                    map.spawnProjectile(playership2->getPos().x, playership2->getPos().y, playership1->getShootDamage(), true, 10, 2);
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
        if(tick %50  == 0) {
            map.update(MapObject::bonus, tick);
        }

        for( PlayerShip* p : map.getListPlayer()){
            if (p->getCurrentBonus()==minigun && p->getHp()>0 && tick % 7 == 0)
                map.spawnProjectile(p->getPos().x, p->getPos().y, p->getShootDamage(), true, 10, p->getPlayerNb()+1);
        }
        map.enemyShoot(tick);
        map.updatePlayerBounds();     // update player bounds
        map.checkCollision(tick);

        if (player1->getnLives() < 1 && player2->getnLives() < 1)
            game_over = true;

        // draw stars
        for(auto s : map.getStars()){   
            mvwaddch(game_wnd, s->getPos().y, s->getPos().x, '.');
        }
        // draw obstacle
        for(auto o : map.getObstacles()){
                wattron(game_wnd, COLOR_PAIR(6));
                mvwaddch(game_wnd, o->getPos().y, o->getPos().x, ACS_DIAMOND);
                wattroff(game_wnd, COLOR_PAIR(6));
        }
        for(auto p : map.getProjectiles()){
            if (p->getShipType()) {
                if (p->getPlayer()==1) {
                    wattron(game_wnd, COLOR_PAIR(5));
                    mvwaddch(game_wnd, p->getPos().y, p->getPos().x, '*');
                    wattroff(game_wnd, COLOR_PAIR(5));
                }
                else{
                    wattron(game_wnd, COLOR_PAIR(2));
                    mvwaddch(game_wnd, p->getPos().y, p->getPos().x, '*');
                    wattroff(game_wnd, COLOR_PAIR(2));
                }
            }
            else{
                wattron(game_wnd, COLOR_PAIR(4));
                mvwaddch(game_wnd, p->getPos().y, p->getPos().x, '*');
                wattroff(game_wnd, COLOR_PAIR(4));

            }
        }
        // draw ennemies
        for(auto e :map.getEnemy()){
            wattron(game_wnd, COLOR_PAIR(4));
            mvwaddch(game_wnd, e->getPos().y, e->getPos().x, e->getChar());
            wattroff(game_wnd, COLOR_PAIR(4));


            wattron(game_wnd, A_ALTCHARSET);
            mvwaddch(game_wnd, e->getPos().y, e->getPos().x - 1, ACS_LARROW);
            mvwaddch(game_wnd, e->getPos().y, e->getPos().x + 1, ACS_RARROW);
            wattroff(game_wnd, A_ALTCHARSET);
        }
        // draw Bonus
        for(auto b : map.getBonus()) {
            wattron(game_wnd, A_BOLD);
            if(b->getBonusType()==lifeSteal){
                mvwaddch(game_wnd, b->getPos().y, b->getPos().x, 'L');
            }
            else if(b->getBonusType()==minigun){
                mvwaddch(game_wnd, b->getPos().y, b->getPos().x, 'M');
            }
            else if(b->getBonusType()==damageUp){
                mvwaddch(game_wnd, b->getPos().y, b->getPos().x, 'D');
            }
            else if(b->getBonusType()==tripleShot){
                mvwaddch(game_wnd, b->getPos().y, b->getPos().x, 'T');
            }
            wattroff(game_wnd, A_BOLD);

        }

        for( PlayerShip* p : map.getListPlayer()){
            // draw player body
            int player_color;
            if (p->getPlayerNb()==1){
                player_color=2;
            }
            else player_color=5;
            wattron(game_wnd, COLOR_PAIR(player_color));
            mvwaddch(game_wnd, p->getPos().y, p->getPos().x, p->getChar());
            wattroff(game_wnd, COLOR_PAIR(player_color));

            wattron(game_wnd, A_ALTCHARSET);
            mvwaddch(game_wnd, p->getPos().y, p->getPos().x - 1, ACS_LARROW);
            mvwaddch(game_wnd, p->getPos().y, p->getPos().x + 1, ACS_RARROW);
            if(listPlayer.at(p->getPlayerNb())->getnLives() > 0){
                if(p->getHp()<=0 && p->getIsAlive()){
                    p->setisAlive(false);
                    p->setKillTime(tick);
                    listPlayer.at(p->getPlayerNb())->setnLives(listPlayer.at(p->getPlayerNb())->getnLives() - 1);
                    map.explosion();
                }
                if(tick==p->getKillTime()+300 && !p->getIsAlive()){

                    p->setisAlive(true);
                    p->setHp(100);

                }
            }

            if(listPlayer.at(p->getPlayerNb())->getnLives() > 0){

                if(tick % 100 < 50 && p->getHp()<=0 && tick<p->getKillTime()+300) {
                    wattron(game_wnd, COLOR_PAIR(player_color));
                    mvwaddch(game_wnd, p->getPos().y, p->getPos().x, ' ');
                    wattroff(game_wnd, COLOR_PAIR(player_color));

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
             
        }

        for( PlayerShip* p : map.getListPlayer()){
            //final score save
            if(p->getPlayerNb() == 0)finalScore1 = p->getScore();
            if(p->getPlayerNb() == 1)finalScore2 = p->getScore();
            if(listPlayer.at(p->getPlayerNb())->getnLives() < 1){
                if (map.getListPlayer().size() == 2) {
                    map.erase(p->getPlayerNb(), MapObject::playership);
                }
                else {
                    map.erase(0, MapObject::playership);
                }
            } 
        }
        //draw new level
        if(map.getLevelTick() != 0 && tick <= map.getLevelTick() + 600 && tick > map.getLevelTick()+100){
            mvwprintw(game_wnd, 8, 35, "level %i", map.getCurrentLevel());
            map.changeLevel();
            if(tick == map.getLevelTick() + 600)
                map.setChangingLevel(false);
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

        //score
        mvwprintw(main_wnd, 22, 1, "  score: %i", finalScore1);
        mvwprintw(main_wnd, 22, 54, "  score: %i", finalScore2);

        // draw static string to hold percentage
        mvwprintw(main_wnd, 21, 1, "- P1 HP                -");
        mvwprintw(main_wnd, 21, 54, "- P2 HP                -");
        mvwprintw(main_wnd, 21, 15, "lives: %i",player1->getnLives());
        mvwprintw(main_wnd, 21, 68, "lives: %i",player2->getnLives());

        // draw numeric percentage player 1
        wattron(main_wnd, A_BOLD);
        if(playership1->getHp() <= 25) {
            wattron(main_wnd, COLOR_PAIR(4));
            if(tick % 100 < 50)
                mvwprintw(main_wnd, 21, 9, "%i%%", playership1->getHp()); 
            wattroff(main_wnd, COLOR_PAIR(4));
        } else
            mvwprintw(main_wnd, 21, 9, "%i%%", playership1->getHp()); 
        wattroff(main_wnd, A_BOLD);

        // draw numeric percentage player 2
        wattron(main_wnd, A_BOLD);
        if(playership2->getHp() <= 25) {
            wattron(main_wnd, COLOR_PAIR(4));
            if(tick % 100 < 50)
                mvwprintw(main_wnd, 21, 62, "%i%%", playership2->getHp()); 
            wattroff(main_wnd, COLOR_PAIR(4));
        } else
            mvwprintw(main_wnd, 21, 62, "%i%%", playership2->getHp()); 
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