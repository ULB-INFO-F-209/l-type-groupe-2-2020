//
// Created by jean on 19/02/2021.
//

#include "Interface.hpp"

int Interface::init() {

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

    //wresize(main_wnd, screen_area.height(), screen_area.width());
    

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

void Interface::initialDraw(){
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
}

Interface::Interface(): main_wnd(),game_wnd(), game_area(), screen_area() {

}

void Interface::display(MapHandler *m,int tick, std::vector<Player *> *listPlayer,PlayerShip* playership1,PlayerShip* playership2, Player* player1,Player* player2,int score1, int score2, bool twoPlayers) {

    // l'affichage à chaque tour de boucle (server->game->server->client)
    drawStar(m);
    drawProjectile(m);
    drawEnemy(m);
    drawObstacle(m);
    drawBonus(m);
    drawPlayer(m,tick,listPlayer);
    drawBoss(m);
    drawUI(m,playership1,playership2,player1,player2,score1,score2,tick, twoPlayers);

}

void Interface::drawStar(MapHandler *m) {
    for(auto s : m->getStars()){
        mvwaddch(game_wnd, s->getPos().y, s->getPos().x, '.');
    }

}

void Interface::drawObstacle(MapHandler *m) {
    for(auto o : m->getObstacles()){
        wattron(game_wnd, COLOR_PAIR(1));
        mvwaddch(game_wnd, o->getPos().y, o->getPos().x, '#');
        wattroff(game_wnd, COLOR_PAIR(1));

    }
}

void Interface::drawEnemy(MapHandler *m) {
    for(auto e :m->getEnemy()){
        wattron(game_wnd, COLOR_PAIR(4));
        mvwaddch(game_wnd, e->getPos().y, e->getPos().x, e->getChar());
        wattroff(game_wnd, COLOR_PAIR(4));


        wattron(game_wnd, A_ALTCHARSET);
        mvwaddch(game_wnd, e->getPos().y, e->getPos().x - 1, ACS_LARROW);
        mvwaddch(game_wnd, e->getPos().y, e->getPos().x + 1, ACS_RARROW);
        wattroff(game_wnd, A_ALTCHARSET);
    }

}

void Interface::drawProjectile(MapHandler *m) {
    for(auto p : m->getProjectiles()){
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
    for(auto pE : m->getProjectilesEnemy()){
        wattron(game_wnd, COLOR_PAIR(4));
        mvwaddch(game_wnd, pE->getPos().y, pE->getPos().x, '*');
        wattroff(game_wnd, COLOR_PAIR(4));
    }

}



void Interface::drawPlayer(MapHandler *m, int tick, std::vector<Player *> *listPlayer) {
    for( PlayerShip* p : m->getListPlayer()) {
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


        if(listPlayer->at(p->getPlayerNb())->getnLives() > 0){

            if(tick % 100 < 50 && p->getHp()<=0 && tick<p->getKillTime()+300) {
                wattron(game_wnd, COLOR_PAIR(player_color));
                mvwaddch(game_wnd, p->getPos().y, p->getPos().x, ' ');
                wattroff(game_wnd, COLOR_PAIR(player_color));

                wattron(game_wnd, A_ALTCHARSET);
                mvwaddch(game_wnd, p->getPos().y, p->getPos().x - 1, ' ');
                mvwaddch(game_wnd, p->getPos().y, p->getPos().x + 1, ' ');
                wattroff(game_wnd, COLOR_PAIR(player_color));

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



}

void Interface::drawUI(MapHandler *m,PlayerShip* playership1,PlayerShip* playership2, Player* player1,Player* player2,int score1, int score2,int tick, bool twoPlayers) {
    
    // energy bar player1
    wmove(main_wnd, 20, 1);
    whline(main_wnd, ' ', 25); // health bar is 25 chars long
    wmove(main_wnd, 20, 1);
    drawEnergyBar(playership1->getHp());
    //score
    mvwprintw(main_wnd, 22, 1, "  score: %i", score1);
    // draw static string to hold percentage
    mvwprintw(main_wnd, 21, 1, "- P1 HP                -");
    mvwprintw(main_wnd, 21, 15, "lives: %i",player1->getnLives());
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
    if (playership1->getCurrentBonus() == minigun)
        mvwprintw(main_wnd, 22, 25, "  B%d:minigun",playership1->getPlayerNb()+1);
    else if (playership1->getCurrentBonus() == damageUp)
        mvwprintw(main_wnd, 22, 25, "  B%d:damageUp",playership1->getPlayerNb()+1);
    else if (playership1->getCurrentBonus() == tripleShot)
        mvwprintw(main_wnd,22, 25, "  B%d:tripleShot",playership1->getPlayerNb()+1);
    else if (playership1->getCurrentBonus() == lifeSteal)
        mvwprintw(main_wnd, 22, 25, "  B%d:lifeSteal",playership1->getPlayerNb()+1);
    else if (playership1->getCurrentBonus() == noBonus)
        mvwprintw(main_wnd, 22, 25, "  B%d:          ",playership1->getPlayerNb()+1);

    if(twoPlayers){
        // energy bar player2
        wmove(main_wnd, 20, 54);
        whline(main_wnd, ' ', 25); // health bar is 25 chars long
        wmove(main_wnd, 20, 54);
        drawEnergyBar(playership2->getHp());
        //score  
        mvwprintw(main_wnd, 22, 54, "  score: %i", score2);
        // draw static string to hold percentage
        mvwprintw(main_wnd, 21, 54, "- P2 HP                -");
        mvwprintw(main_wnd, 21, 68, "lives: %i",player2->getnLives());
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
        if (playership2->getCurrentBonus() == minigun)
            mvwprintw(main_wnd, 22, 40, "  B%d:minigun",playership2->getPlayerNb()+1);
        else if (playership2->getCurrentBonus() == damageUp)
            mvwprintw(main_wnd, 22, 40, "  B%d:damageUp",playership2->getPlayerNb()+1);
        else if (playership2->getCurrentBonus() == tripleShot)
            mvwprintw(main_wnd, 22, 40, "  B%d:tripleShot",playership2->getPlayerNb()+1);
        else if (playership2->getCurrentBonus() == lifeSteal)
            mvwprintw(main_wnd, 22, 40, "  B%d:lifeSteal",playership2->getPlayerNb()+1);
        else if (playership2->getCurrentBonus() == noBonus)
            mvwprintw(main_wnd, 22, 40, "  B%d:          ",playership2->getPlayerNb()+1);
    }
    
    //level
    mvwprintw(main_wnd,20,33," LEVEL : %i",m->getCurrentLevel());

}

void Interface::refresh_wnd() {
    wrefresh(main_wnd);
    wrefresh(game_wnd);
    usleep(10000); // 10 ms
    refresh();

}

void Interface::close() {
    delwin(main_wnd);
    delwin(game_wnd);
    endwin();

}

void Interface::drawEnergyBar(int a) {

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

void Interface::drawBonus(MapHandler *m) {
    for(auto b : m->getBonus()) {
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

}

void Interface::drawNewLevel(MapHandler *map, int tick) {
    mvwprintw(game_wnd, 8, 35, "level %i", map->getCurrentLevel());
}

void Interface::drawBoss(MapHandler *map) {
    for(auto b :map->getBoss()){
        wattron(main_wnd, COLOR_PAIR(4));
        mvwprintw(game_wnd, b->getPos().y, b->getPos().x, "      ______      ");
        mvwprintw(game_wnd, b->getPos().y+1, b->getPos().x, " ____|______|____");
        mvwprintw(game_wnd, b->getPos().y+2, b->getPos().x, "/ |____________| \\");
        mvwprintw(game_wnd, b->getPos().y+3, b->getPos().x, "| |____________| |");
        mvwprintw(game_wnd, b->getPos().y+4, b->getPos().x, "\\_|____ ___ ___|_/");
        mvwprintw(game_wnd, b->getPos().y+5, b->getPos().x, "      |_| |_|     ");
        wattroff(main_wnd, COLOR_PAIR(4));

    }
  }

void Interface::drawGameOver(MapHandler* m, int score1){
    mvwprintw(game_wnd,8, 35,"GAME OVER");
    mvwprintw(game_wnd,9, 35,"SCORE : %i", score1);
    mvwprintw(game_wnd,12, 30,"press SPACE to quit");
    
    
}
