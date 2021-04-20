//
// Created by jean on 19/02/2021.
//

#include "Interface_game.hpp"
#include <iostream>

int Interface_game::init() {

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
void Interface_game::initialDraw(){
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
Interface_game::Interface_game(): main_wnd(),game_wnd(), game_area(), screen_area() {

}
void Interface_game::display(MapHandler *m,int tick, std::vector<Player *> *listPlayer,PlayerShip* playership1,PlayerShip* playership2, Player* player1,Player* player2,int score1, int score2, bool twoPlayers) {

    // l'affichage à chaque tour de boucle (server->game->server->client)
    werase(game_wnd); // attention ?
    drawStar(m);
    drawProjectile(m);
    drawEnemy(m, tick, listPlayer);
    drawObstacle(m);
    drawBonus(m);
    drawPlayer(m,tick,listPlayer);
    drawBoss(m);
    drawNewLevel(m,tick);
    drawUI(m,playership1,playership2,player1,player2,score1,score2,tick, twoPlayers);
    refresh_wnd();
}
void Interface_game::display(settingServer* settings){
    werase(game_wnd); // attention ?
    drawStar(settings->object_map);
    drawProjectile(settings->object_map);
    drawEnemy(settings->object_map, settings->tick, settings->list_player);
    drawObstacle(settings->object_map);
    drawBonus(settings->object_map);
    drawPlayer(settings->object_map,settings->tick,settings->list_player);
    drawBoss(settings->object_map);
    drawNewLevel(settings->object_map,settings->tick);
    drawUI(settings->object_map,settings->object_playership1,settings->object_playership2,settings->object_player1,settings->object_player2,settings->score_j1,settings->score_j2,settings->tick, settings->two_players);
    if (settings->game_over){
        drawGameOver(settings->object_map, (settings->score_j1+settings->score_j2));
        return;
    }
    refresh_wnd();
}
<<<<<<< HEAD
void Interface_game::display(settingArray *sett){
    werase(game_wnd); // attention ?
    if (sett->game_over){
        std::cout << sett->game_over << std::endl;
        drawGameOver((sett->score_j1+sett->score_j2));
        refresh_wnd();
        return;
    }
    drawStar(sett->stars_set,sett->my_size.stars_set_size);
    drawProjectile(sett->projectiles_set,sett->my_size.projectiles_set, sett->projectilesEnemy_set,sett->my_size.projectilesEnemy_set);
    drawEnemy(sett->enemy_ships_set, sett->tick, sett->list_player,sett->player_ships_set,sett->my_size.enemy_ships_set,sett->my_size.player_ships_set);
    drawObstacle(sett->obstacles_set,sett->my_size.obstacles_set);
    drawBonus(sett->bonnuses_set,sett->my_size.bonnuses_set);
    drawPlayer(sett->player_ships_set,sett->tick,sett->list_player,sett->my_size.player_ships_set,sett->my_size.list_player);
    drawBoss(sett->boss_set,sett->my_size.boss_set);
    drawNewLevel(sett->tick,sett->level_tick,sett->current_level);
    drawUI(sett->player_ships_set,sett->list_player,sett->score_j1,sett->score_j2 ,sett->tick, sett->two_players,sett->current_level,sett->my_size.player_ships_set);
    refresh_wnd();
}
=======

>>>>>>> systeme
void Interface_game::drawStar(MapHandler *m) {
    for(auto s : m->getStars()){
        mvwaddch(game_wnd, s->getPos().y, s->getPos().x, '.');
    }

}
void Interface_game::drawObstacle(MapHandler *m) {
    for(auto o : m->getObstacles()){
        wattron(game_wnd, COLOR_PAIR(1));
        mvwaddch(game_wnd, o->getPos().y, o->getPos().x, '#');
        wattroff(game_wnd, COLOR_PAIR(1));

    }
}
void Interface_game::drawEnemy(MapHandler *m, int tick, std::vector<Player *> *listPlayer) {
    for(auto e :m->getEnemy()){
        wattron(game_wnd, COLOR_PAIR(4));
        mvwaddch(game_wnd, e->getPos().y, e->getPos().x, e->getChar());
        wattroff(game_wnd, COLOR_PAIR(4));


        wattron(game_wnd, A_ALTCHARSET);
        mvwaddch(game_wnd, e->getPos().y, e->getPos().x - 1, ACS_LARROW);
        mvwaddch(game_wnd, e->getPos().y, e->getPos().x + 1, ACS_RARROW);
        wattroff(game_wnd, A_ALTCHARSET);
    }

    for( PlayerShip* p : m->getListPlayer()) {
        if(listPlayer->at(p->getPlayerNb())->getnLives() > 0){
            if(tick % 20 < 10 && p->getHp()<=0 && tick<p->getKillTime()+100) {
                for(EnemyShip* e :m->getEnemy()){
                    wattron(game_wnd, COLOR_PAIR(4));
                    mvwaddch(game_wnd, e->getPos().y, e->getPos().x, ' ');
                    wattroff(game_wnd, COLOR_PAIR(4));

                    wattron(game_wnd, A_ALTCHARSET);
                    mvwaddch(game_wnd, e->getPos().y, e->getPos().x - 1, ' ');
                    mvwaddch(game_wnd, e->getPos().y, e->getPos().x + 1, ' ');
                    wattroff(game_wnd, A_ALTCHARSET);
                }
            }
        }
    }

}
void Interface_game::drawProjectile(MapHandler *m) {
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
void Interface_game::drawPlayer(MapHandler *m, int tick, std::vector<Player *> *listPlayer) {
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
            // show player looses a life
            if(tick % 100 < 50 && p->getHp()<=0 && tick<p->getKillTime()+300) {
                wattron(game_wnd, COLOR_PAIR(player_color));
                mvwaddch(game_wnd, p->getPos().y, p->getPos().x, ' ');
                wattroff(game_wnd, COLOR_PAIR(player_color));

                wattron(game_wnd, A_ALTCHARSET);
                mvwaddch(game_wnd, p->getPos().y, p->getPos().x - 1, ' ');
                mvwaddch(game_wnd, p->getPos().y, p->getPos().x + 1, ' ');
                wattroff(game_wnd, A_ALTCHARSET);
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
void Interface_game::drawUI(MapHandler *m,PlayerShip* playership1,PlayerShip* playership2, Player* player1,Player* player2,int score1, int score2,int tick, bool twoPlayers) {
    
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
        mvwprintw(main_wnd, 22, 16, "  B%d: M",playership1->getPlayerNb()+1);
    else if (playership1->getCurrentBonus() == damageUp)
        mvwprintw(main_wnd, 22, 16, "  B%d: D",playership1->getPlayerNb()+1);
    else if (playership1->getCurrentBonus() == tripleShot)
        mvwprintw(main_wnd,22, 16, "  B%d: T",playership1->getPlayerNb()+1);
    else if (playership1->getCurrentBonus() == lifeSteal)
        mvwprintw(main_wnd, 22, 16, "  B%d: L",playership1->getPlayerNb()+1);
    else if (playership1->getCurrentBonus() == noBonus)
        mvwprintw(main_wnd, 22, 16, "  B%d:  ",playership1->getPlayerNb()+1);

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
            mvwprintw(main_wnd, 22, 69, "  B%d: M",playership2->getPlayerNb()+1);
        else if (playership2->getCurrentBonus() == damageUp)
            mvwprintw(main_wnd, 22, 69, "  B%d: D",playership2->getPlayerNb()+1);
        else if (playership2->getCurrentBonus() == tripleShot)
            mvwprintw(main_wnd, 22, 69, "  B%d: T",playership2->getPlayerNb()+1);
        else if (playership2->getCurrentBonus() == lifeSteal)
            mvwprintw(main_wnd, 22, 69, "  B%d: L",playership2->getPlayerNb()+1);
        else if (playership2->getCurrentBonus() == noBonus)
            mvwprintw(main_wnd, 22, 69, "  B%d:  ",playership2->getPlayerNb()+1);
    }
    
    //level
    mvwprintw(main_wnd,20,33," LEVEL : %i",m->getCurrentLevel());

}
void Interface_game::refresh_wnd() {
    wrefresh(main_wnd);
    wrefresh(game_wnd);
    

}
void Interface_game::close() {
    werase(game_wnd);
    werase(main_wnd);
    delwin(main_wnd);
    delwin(game_wnd);
    endwin();

}
void Interface_game::drawEnergyBar(int a) {

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
void Interface_game::drawBonus(MapHandler *m) {
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
void Interface_game::drawNewLevel(MapHandler *map, int tick) {
    if(map->getLevelTick() != 0 && tick <= map->getLevelTick() + 600 && tick > map->getLevelTick()+100){
        mvwprintw(game_wnd, 8, 35, "level %i", map->getCurrentLevel());
    }
}
void Interface_game::drawBoss(MapHandler *map) {
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
void Interface_game::drawBoss(Boss *bs,std::size_t size_bs) {
    for(std::size_t i=0; i < size_bs; i++){
        wattron(main_wnd, COLOR_PAIR(4));
        mvwprintw(game_wnd, bs[i].getPos().y,   bs[i].getPos().x, "      ______      ");
        mvwprintw(game_wnd, bs[i].getPos().y+1, bs[i].getPos().x, " ____|______|____");
        mvwprintw(game_wnd, bs[i].getPos().y+2, bs[i].getPos().x, "/ |____________| \\");
        mvwprintw(game_wnd, bs[i].getPos().y+3, bs[i].getPos().x, "| |____________| |");
        mvwprintw(game_wnd, bs[i].getPos().y+4, bs[i].getPos().x, "\\_|____ ___ ___|_/");
        mvwprintw(game_wnd, bs[i].getPos().y+5, bs[i].getPos().x, "      |_| |_|     ");
        wattroff(main_wnd, COLOR_PAIR(4));

    }
  }
void Interface_game::drawGameOver(MapHandler* m, int score1){
    mvwprintw(game_wnd,8, 35,"GAME OVER");
    mvwprintw(game_wnd,9, 35,"SCORE : %i", score1);
    mvwprintw(game_wnd,12, 32,"press P to quit");
    refresh_wnd();
    
    

}
void Interface_game::drawGameOver(int score1){
    mvwprintw(game_wnd,8, 35,"GAME OVER");
    mvwprintw(game_wnd,9, 35,"SCORE : %i", score1);
    mvwprintw(game_wnd,12, 32,"press p to quit");
    refresh_wnd();
    while(true){
        char in_char = wgetch(get_main_window());
        if(in_char == 'p')break;
    } 

}
void Interface_game::drawStar(Star*s,std::size_t size_s){
    //if (size_s == 0) return;
    for(std::size_t i =0; i< size_s;i++){
        mvwaddch(game_wnd, s[i].getPos().y, s[i].getPos().x, '.');
    }
}
void Interface_game::drawObstacle(Obstacle*o,std::size_t size_o){
    if (size_o == 0) return;
    for(std::size_t i =0; i< size_o;i++){
        
        wattron(game_wnd, COLOR_PAIR(1));
        mvwaddch(game_wnd, o[i].getPos().y, o[i].getPos().x, '#');
        wattroff(game_wnd, COLOR_PAIR(1));

    }
}
void Interface_game::drawEnemy(EnemyShip* e, int tick, Player* listPlayer,PlayerShip* ps,std::size_t size_e,std::size_t size_ps){
    for(std::size_t i =0; i< size_e;i++){
        wattron(game_wnd, COLOR_PAIR(4));
        mvwaddch(game_wnd, e[i].getPos().y, e[i].getPos().x, e[i].getChar());
        wattroff(game_wnd, COLOR_PAIR(4));


        wattron(game_wnd, A_ALTCHARSET);
        mvwaddch(game_wnd, e[i].getPos().y, e[i].getPos().x - 1, ACS_LARROW);
        mvwaddch(game_wnd, e[i].getPos().y, e[i].getPos().x + 1, ACS_RARROW);
        wattroff(game_wnd, A_ALTCHARSET);
    }

    for(std::size_t i =0; i< size_ps;i++){
        if(listPlayer[ps[i].getPlayerNb()].getnLives() > 0){
            if(tick % 20 < 10 && ps[i].getHp()<=0 && tick<ps[i].getKillTime()+100) {
                for(std::size_t i =0; i< size_e;i++){
                    wattron(game_wnd, COLOR_PAIR(4));
                    mvwaddch(game_wnd, e[i].getPos().y, e[i].getPos().x, ' ');
                    wattroff(game_wnd, COLOR_PAIR(4));

                    wattron(game_wnd, A_ALTCHARSET);
                    mvwaddch(game_wnd, e[i].getPos().y, e[i].getPos().x - 1, ' ');
                    mvwaddch(game_wnd, e[i].getPos().y, e[i].getPos().x + 1, ' ');
                    wattroff(game_wnd, A_ALTCHARSET);
                }
            }
        }
    }
}
void Interface_game::drawProjectile(Projectile*p,std::size_t size_p, Projectile*pe,std::size_t size_pe){
    
    for(std::size_t i =0; i< size_p;i++){
        if (p[i].getPlayer()==1) {
            wattron(game_wnd, COLOR_PAIR(5));
            mvwaddch(game_wnd, p[i].getPos().y, p[i].getPos().x, '*');
            wattroff(game_wnd, COLOR_PAIR(5));
        }
        else{
            wattron(game_wnd, COLOR_PAIR(2));
            mvwaddch(game_wnd, p[i].getPos().y, p[i].getPos().x, '*');
            wattroff(game_wnd, COLOR_PAIR(2));
        }
    }
    
    for(std::size_t i =0; i< size_pe;i++){
        wattron(game_wnd, COLOR_PAIR(4));
        mvwaddch(game_wnd, pe[i].getPos().y, pe[i].getPos().x, '*');
        wattroff(game_wnd, COLOR_PAIR(4));
    }
}
void Interface_game::drawPlayer(PlayerShip* ps,int tick,Player* listPlayer,std::size_t size_ps,std::size_t size_p){
    for(std::size_t i =0; i< size_ps;i++) {
        // draw player body
        int player_color;
        if (ps[i].getPlayerNb()==1){
            player_color=2;
        }
        else player_color=5;
        wattron(game_wnd, COLOR_PAIR(player_color));
        mvwaddch(game_wnd, ps[i].getPos().y, ps[i].getPos().x, ps[i].getChar());
        wattroff(game_wnd, COLOR_PAIR(player_color));

        wattron(game_wnd, A_ALTCHARSET);
        mvwaddch(game_wnd, ps[i].getPos().y, ps[i].getPos().x - 1, ACS_LARROW);
        mvwaddch(game_wnd, ps[i].getPos().y, ps[i].getPos().x + 1, ACS_RARROW);


        if(listPlayer[(ps[i].getPlayerNb())].getnLives() > 0){
            // show player looses a life
            if(tick % 100 < 50 && ps[i].getHp()<=0 && tick<ps[i].getKillTime()+300) {
                wattron(game_wnd, COLOR_PAIR(player_color));
                mvwaddch(game_wnd, ps[i].getPos().y, ps[i].getPos().x, ' ');
                wattroff(game_wnd, COLOR_PAIR(player_color));

                wattron(game_wnd, A_ALTCHARSET);
                mvwaddch(game_wnd, ps[i].getPos().y, ps[i].getPos().x - 1, ' ');
                mvwaddch(game_wnd, ps[i].getPos().y, ps[i].getPos().x + 1, ' ');
                wattroff(game_wnd, A_ALTCHARSET);
            }

            // draw engines flames
            if((tick % 10) / 3 && ps[i].getHp()>0) {
                wattron(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
                mvwaddch(game_wnd, ps[i].getPos().y + 1, ps[i].getPos().x, ACS_UARROW);
                mvwaddch(game_wnd, ps[i].getPos().y + 1, ps[i].getPos().x, ACS_UARROW);
                wattroff(game_wnd, COLOR_PAIR(tick % 2 ? 3 : 4));
            }
        }

        wattroff(game_wnd, A_ALTCHARSET);

    }
}
void Interface_game::drawUI(PlayerShip* playerships, Player* players, int score1, int score2,int tick, bool twoPlayers,int current_level ,std::size_t size_ps){
    /*
    Ajouter des var pour les coords de la vie des PlayerSHip [TODO]
    */ 

    if(twoPlayers && size_ps == 2){
        // energy bar player2
        wmove(main_wnd, 20, 54);
        whline(main_wnd, ' ', 25); // health bar is 25 chars long
        wmove(main_wnd, 20, 54);
        drawEnergyBar(playerships[1].getHp());
        //score  
        mvwprintw(main_wnd, 22, 54, "  score: %i", score2);
        // draw static string to hold percentage
        mvwprintw(main_wnd, 21, 54, "- P2 HP                -");
        mvwprintw(main_wnd, 21, 68, "lives: %i",players[1].getnLives());
        // draw numeric percentage player 2
        wattron(main_wnd, A_BOLD);
        if(playerships[1].getHp() <= 25) {
            wattron(main_wnd, COLOR_PAIR(4));
            if(tick % 100 < 50)
                mvwprintw(main_wnd, 21, 62, "%i%%", playerships[1].getHp());
            wattroff(main_wnd, COLOR_PAIR(4));
        } else
            mvwprintw(main_wnd, 21, 62, "%i%%", playerships[1].getHp());
        wattroff(main_wnd, A_BOLD);
        if (playerships[1].getCurrentBonus() == minigun)
            mvwprintw(main_wnd, 22, 69, "  B%d: M",playerships[1].getPlayerNb()+1);
        else if (playerships[1].getCurrentBonus() == damageUp)
            mvwprintw(main_wnd, 22, 69, "  B%d: D",playerships[1].getPlayerNb()+1);
        else if (playerships[1].getCurrentBonus() == tripleShot)
            mvwprintw(main_wnd, 22, 69, "  B%d: T",playerships[1].getPlayerNb()+1);
        else if (playerships[1].getCurrentBonus() == lifeSteal)
            mvwprintw(main_wnd, 22, 69, "  B%d: L",playerships[1].getPlayerNb()+1);
        else if (playerships[1].getCurrentBonus() == noBonus)
            mvwprintw(main_wnd, 22, 69, "  B%d:  ",playerships[1].getPlayerNb()+1);
    }
    
    // energy bar player1
    if (playerships[0].getPlayerNb() == 1){
        wmove(main_wnd, 20, 54);
        whline(main_wnd, ' ', 25); // health bar is 25 chars long
        wmove(main_wnd, 20, 54);
        drawEnergyBar(playerships[0].getHp());
        //score  
        mvwprintw(main_wnd, 22, 54, "  score: %i", score2);
        // draw static string to hold percentage
        mvwprintw(main_wnd, 21, 54, "- P2 HP                -");
        mvwprintw(main_wnd, 21, 68, "lives: %i",players[1].getnLives());
        // draw numeric percentage player 2
        wattron(main_wnd, A_BOLD);
        if(playerships[1].getHp() <= 25) {
            wattron(main_wnd, COLOR_PAIR(4));
            if(tick % 100 < 50)
                mvwprintw(main_wnd, 21, 62, "%i%%", playerships[0].getHp());
            wattroff(main_wnd, COLOR_PAIR(4));
        } else
            mvwprintw(main_wnd, 21, 62, "%i%%", playerships[0].getHp());
        wattroff(main_wnd, A_BOLD);
        if (playerships[1].getCurrentBonus() == minigun)
            mvwprintw(main_wnd, 22, 69, "  B%d: M",playerships[0].getPlayerNb()+1);
        else if (playerships[1].getCurrentBonus() == damageUp)
            mvwprintw(main_wnd, 22, 69, "  B%d: D",playerships[0].getPlayerNb()+1);
        else if (playerships[1].getCurrentBonus() == tripleShot)
            mvwprintw(main_wnd, 22, 69, "  B%d: T",playerships[0].getPlayerNb()+1);
        else if (playerships[1].getCurrentBonus() == lifeSteal)
            mvwprintw(main_wnd, 22, 69, "  B%d: L",playerships[0].getPlayerNb()+1);
        else if (playerships[1].getCurrentBonus() == noBonus)
            mvwprintw(main_wnd, 22, 69, "  B%d:  ",playerships[0].getPlayerNb()+1);


        wmove(main_wnd, 20, 1);
        whline(main_wnd, ' ', 25); // health bar is 25 chars long
        wmove(main_wnd, 20, 1);
        drawEnergyBar(0);
        //score
        mvwprintw(main_wnd, 22, 1, "  score: %i", score1);
        // draw static string to hold percentage
        mvwprintw(main_wnd, 21, 1, "- P1 HP                -");
        mvwprintw(main_wnd, 21, 15, "lives: %i",0);
        // draw numeric percentage player 1
        wattron(main_wnd, A_BOLD);
        
        mvwprintw(main_wnd, 21, 9, "%i%%", 0);
        wattroff(main_wnd, A_BOLD);
        if (playerships[0].getCurrentBonus() == minigun)
            mvwprintw(main_wnd, 22, 16, "  B%d: M",1);
        else if (playerships[0].getCurrentBonus() == damageUp)
            mvwprintw(main_wnd, 22, 16, "  B%d: D",1);
        else if (playerships[0].getCurrentBonus() == tripleShot)
            mvwprintw(main_wnd,22, 16, "  B%d: T",1);
        else if (playerships[0].getCurrentBonus() == lifeSteal)
            mvwprintw(main_wnd, 22, 16, "  B%d: L",1);
        else if (playerships[0].getCurrentBonus() == noBonus)
            mvwprintw(main_wnd, 22, 16, "  B%d:  ",1);
    }
    

    if (playerships[0].getPlayerNb()==0){

        wmove(main_wnd, 20, 1);
        whline(main_wnd, ' ', 25); // health bar is 25 chars long
        wmove(main_wnd, 20, 1);
        drawEnergyBar(playerships[0].getHp());
        //score
        mvwprintw(main_wnd, 22, 1, "  score: %i", score1);
        // draw static string to hold percentage
        mvwprintw(main_wnd, 21, 1, "- P1 HP                -");
        mvwprintw(main_wnd, 21, 15, "lives: %i",players[0].getnLives());
        // draw numeric percentage player 1
        wattron(main_wnd, A_BOLD);
        if(playerships[0].getHp() <= 25) {
            wattron(main_wnd, COLOR_PAIR(4));
            if(tick % 100 < 50)
                mvwprintw(main_wnd, 21, 9, "%i%%", playerships[0].getHp());
            wattroff(main_wnd, COLOR_PAIR(4));
        } else
            mvwprintw(main_wnd, 21, 9, "%i%%", playerships[0].getHp());
        wattroff(main_wnd, A_BOLD);
        if (playerships[0].getCurrentBonus() == minigun)
            mvwprintw(main_wnd, 22, 16, "  B%d: M",playerships[0].getPlayerNb()+1);
        else if (playerships[0].getCurrentBonus() == damageUp)
            mvwprintw(main_wnd, 22, 16, "  B%d: D",playerships[0].getPlayerNb()+1);
        else if (playerships[0].getCurrentBonus() == tripleShot)
            mvwprintw(main_wnd,22, 16, "  B%d: T",playerships[0].getPlayerNb()+1);
        else if (playerships[0].getCurrentBonus() == lifeSteal)
            mvwprintw(main_wnd, 22, 16, "  B%d: L",playerships[0].getPlayerNb()+1);
        else if (playerships[0].getCurrentBonus() == noBonus)
            mvwprintw(main_wnd, 22, 16, "  B%d:  ",playerships[0].getPlayerNb()+1);
    }

    
    //level
    mvwprintw(main_wnd,20,33," LEVEL : %i",current_level);
}
void Interface_game::drawBonus(Bonus* b,std::size_t size_b){
    for(std::size_t i =0; i< size_b; i++) {
        wattron(game_wnd, A_BOLD);
        if(b[i].getBonusType()==lifeSteal){
            mvwaddch(game_wnd, b[i].getPos().y, b[i].getPos().x, 'L');
        }
        else if(b[i].getBonusType()==minigun){
            mvwaddch(game_wnd, b[i].getPos().y, b[i].getPos().x, 'M');
        }
        else if(b[i].getBonusType()==damageUp){
            mvwaddch(game_wnd, b[i].getPos().y, b[i].getPos().x, 'D');
        }
        else if(b[i].getBonusType()==tripleShot){
            mvwaddch(game_wnd, b[i].getPos().y, b[i].getPos().x, 'T');
        }
        wattroff(game_wnd, A_BOLD);

    }
}
void Interface_game::drawNewLevel(int tick, int level_tick,int current_level){
    if(level_tick != 0 && tick <= level_tick + 600 && tick > level_tick+100){
        mvwprintw(game_wnd, 8, 35, "level %i", current_level);
    }
}

