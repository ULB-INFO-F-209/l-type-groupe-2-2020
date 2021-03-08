//
// Created by jean on 19/02/2021.
//
/**
 * TODO:
 *  thread pour jouer en même temps (Aïssa)
 *  enlever static_cast !!
 * ERROR:
 *
 *
 */
#include "CurrentGame.hpp"


void CurrentGame::execInput(int inChar, uint_fast16_t x1, uint_fast16_t y1, bool firstPlayer){
    if(firstPlayer){
        switch(inChar) {
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
            default:
            break;
            }
        
    }
    else{
        switch(inChar) {
            
            case 'f':
                if(x1 > game_area.left() + 1)
                    playership2->setPos(x1 - 1 , y1);
                break;
            case 't':
                if(y1 > game_area.top())
                    playership2->setPos(x1, y1 - 1);;
                break;
            case 'g':
                if(y1 < game_area.bot())
                    playership2->setPos(x1 , y1 + 1);
                break;
            case 'h':
                if(x1< game_area.right() - 2)
                    playership2->setPos(x1 + 1 , y1);
                break;
            case 'r':
                if((x1 > game_area.left() + 1) && (y1 > game_area.top())){
                    playership2->setPos(x1 - 1 , y1 - 1);}
                break;
            case 'y':
                if((x1 < game_area.right() - 2) && (y1 > game_area.top())){
                    playership2->setPos(x1 + 1 , y1 - 1);}
                break;
            case 'n':
                if((x1 < game_area.right() - 2) && (y1 < game_area.bot())){
                    playership2->setPos(x1 + 1 , y1 + 1);}
                break;
            case 'v':
                if((x1 > game_area.left() + 1) && (y1 < game_area.bot())){
                    playership2->setPos(x1 - 1 , y1 + 1);}
                break;
            case 'm':
                if(playership2->getHp()>0 && playership2->getCurrentBonus()!=minigun)
                    map.spawnProjectile(playership2->getPos().x, playership2->getPos().y, playership1->getShootDamage(), true, 10, 2);
                break;
            default:
                break;
                }
        }
}


void CurrentGame::heal() {      // remet hp du player à 100 si encore vies
    for( PlayerShip* p : map.getListPlayer()){
        if(listPlayer.at(p->getPlayerNb())->getnLives() > 0){
            if(p->getHp()<=0 && p->getIsAlive()){
                map.explosion();
                p->setisAlive(false);
                p->setKillTime(tick);
                listPlayer.at(p->getPlayerNb())->setnLives(listPlayer.at(p->getPlayerNb())->getnLives() - 1);

            }
            if(tick==p->getKillTime()+300 && !p->getIsAlive()){
                p->setisAlive(true);
                p->setCurrentBonus(noBonus);
                p->setHp(100);
            }
        }
    }
}

void CurrentGame::saveScore(){      //final score save
    for( PlayerShip* p : map.getListPlayer()){
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
}


void CurrentGame::run() {

    tick = 0;

    playership1 = new PlayerShip(10, 5, { {10 - 1, 5 }, { 3, 2 } }, '0',100, 0,100,0);
    player1 = new Player(3);
    listPlayer.push_back(player1);

    if(twoPlayers){
        playership2 = new PlayerShip(50, 5, { { 50 - 1, 5 }, { 3, 2 } }, '1',100, 1,100,0);
        player2 = new Player(3);
        listPlayer.push_back(player2);
    }
      
    Interface_game anInterface;
    anInterface.init();
    map.playerInit(playership1,playership2);
    map.setBounds(anInterface.get_game_area());
    anInterface.initialDraw();
    game_area = anInterface.get_game_area();
    screen_area = anInterface.get_screen_area();
    while(true) {

        // get input
        in_char = wgetch(anInterface.get_main_window());
        in_char = tolower(in_char);

        uint_fast16_t x1,y1,x2,y2;

        x1 = playership1->getPos().x;
        y1 = playership1->getPos().y;
        if(twoPlayers){
            x2 = playership2->getPos().x;
            y2 = playership2->getPos().y;
        }


        // fonction du switch
        execInput(in_char, x1, y1, true);    // peut changer le exit_requested
        if(twoPlayers)execInput(in_char, x2, y2, false);


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
        if(map.getCurrentLevel()==6 && tick%10==0 && !map.getChangingLevel()){
            map.update(MapObject::boss,tick);
        }

        for( PlayerShip* p : map.getListPlayer()){
            if (p->getCurrentBonus()==minigun && p->getHp()>0 && tick % 7 == 0)
                map.spawnProjectile(p->getPos().x, p->getPos().y, p->getShootDamage(), true, 10, p->getPlayerNb()+1);
        }
        map.enemyShoot(tick);
        map.bossShoot(tick);
        map.updateBounds();     // update player bounds
        map.checkCollision(tick, friendlyFire);

        if(map.getBoss().empty() && map.getBossSpawned())
            game_over = true;

        if(twoPlayers){
            if (player1->getnLives() < 1 && player2->getnLives() < 1)
                game_over = true;
        }else{
            if (player1->getnLives() < 1)
                game_over = true;
        }

        heal(); // remet hp du player à 100 si encore vies

        werase(anInterface.get_game_window());
        anInterface.display(&map,tick,&listPlayer,playership1,playership2,player1,player2,finalScore1,finalScore2, twoPlayers);

        if(map.getLevelTick() != 0 && tick <= map.getLevelTick() + 600 && tick > map.getLevelTick()+100){
            anInterface.drawNewLevel(&map, tick);
            if(tick == map.getLevelTick() + 600) {
                map.changeLevel();
                map.setChangingLevel(false);
            }
        }
        anInterface.refresh_wnd();

        saveScore(); // sauvegarde le score

        if(exit_requested) break;
        if(game_over){
            
            anInterface.drawGameOver(&map,finalScore1 + finalScore2);
            anInterface.refresh_wnd();
            while(true){
                in_char = wgetch(anInterface.get_main_window());
                if(in_char == 'p')break;
            }
            break;
        }
        tick++;

    }
    anInterface.close();
}




void CurrentGame::getSettings(settingServer* settings) {
    settings->object_map = &map;
    settings->object_playership1 = playership1;
    settings->object_playership2 = playership2;
    settings->score_j1 = finalScore1;
    settings->score_j2 = finalScore2;
    settings->two_players = twoPlayers;
    settings->object_player1 = player1;
    settings->object_player2 = player2;
    settings->list_player = &listPlayer;
    settings->tick = tick;
    settings->game_over = game_over;

};


std::string CurrentGame::run_server(char move_to_exec,settingServer* settings){

    std::string what_change;
   
    uint_fast16_t x1,y1,x2,y2;

    x1 = playership1->getPos().x;
    y1 = playership1->getPos().y;
    execInput(move_to_exec, x1, y1, true);
    if(twoPlayers){
        x2 = playership2->getPos().x;
        y2 = playership2->getPos().y;
        execInput(move_to_exec, x2, y2, false);
    }
    
    // fonction du switch
     
    // update object field
    if(tick % 7 == 0)
        map.update_server(MapObject::star, tick,&what_change);
    if(tick % 7 == 0)
        map.update_server(MapObject::projectile, tick,&what_change);

    if(tick > 100 && tick %50  == 0) {
        map.update_server(MapObject::obstacle, tick,&what_change);
    }
    if (tick > 100 && tick %150 ==0)
        map.update_server(MapObject::enemyship, tick, &what_change);
    if(tick %50  == 0) {
        map.update_server(MapObject::bonus, tick, &what_change);
    }
    if(map.getCurrentLevel()==3 && tick%10==0 && !map.getChangingLevel()){
        map.update_server(MapObject::boss,tick,&what_change);
    }

    for( PlayerShip* p : map.getListPlayer()){
        if (p->getCurrentBonus()==minigun && p->getHp()>0 && tick % 7 == 0)
            map.spawnProjectile_server(p->getPos().x, p->getPos().y, p->getShootDamage(), true, 10, p->getPlayerNb()+1,&what_change);
    }
    map.enemyShoot_server(tick,&what_change);
    map.bossShoot_server(tick,&what_change);
    map.updateBounds();     // update player bounds
    map.checkCollision_server(tick, friendlyFire,&what_change);

    if(map.getBoss().empty() && map.getBossSpawned())
         game_over = true;

    if(twoPlayers){
        if (player1->getnLives() < 1 && player2->getnLives() < 1)
            game_over = true;
    }else{
        if (player1->getnLives() < 1)
            game_over = true;
    }

    heal(); // remet hp du player à 100 si encore vies

    if(map.getLevelTick() != 0 && tick <= map.getLevelTick() + 600 && tick > map.getLevelTick()+100){
            if(tick == map.getLevelTick() + 600) {
                map.changeLevel();
                map.setChangingLevel(false);
            }
        }

    
    saveScore(); // sauvegarde le score

    if(exit_requested){
        const char * tmp = what_change.c_str();
        getSettings(settings);
    
    return what_change;
    } 
    if(game_over){
        
        const char * tmp = what_change.c_str();
        getSettings(settings);
    
    return what_change;
    }
    

    
    tick++;
    what_change.append("T|");
    what_change.append(std::to_string(tick));
    what_change.append("&");
    getSettings(settings);
    return what_change;
    

};


void CurrentGame::run_client(int move_to_exec,settingServer* settings){
    // get input
    /*in_char = wgetch(anInterface->get_main_window());
    in_char = tolower(in_char);*/

    uint_fast16_t x1,y1,x2,y2;

    x1 = playership1->getPos().x;
    y1 = playership1->getPos().y;
    if(twoPlayers){
        x2 = playership2->getPos().x;
        y2 = playership2->getPos().y;
    }


    // fonction du switch
    execInput(move_to_exec, x1, y1, true);    // peut changer le exit_requested
    if(twoPlayers)execInput(move_to_exec, x2, y2, false);


    // update object field
    if(tick % 7 == 0)
        map.update_client(MapObject::star, tick);
    if(tick % 7 == 0)
        map.update_client(MapObject::projectile, tick);

    if(tick > 100 && tick %50  == 0) {
        map.update_client(MapObject::obstacle, tick);
    }
    if (tick > 100 && tick %150 ==0)
        map.update_client(MapObject::enemyship, tick);
    if(tick %50  == 0) {
        map.update_client(MapObject::bonus, tick);
    }
    if(map.getCurrentLevel()==3 && tick%10==0 && !map.getChangingLevel()){
        map.update_client(MapObject::boss,tick);
    }

    //minigun
    for( PlayerShip* p : map.getListPlayer()){
        if (p->getCurrentBonus()==minigun && p->getHp()>0 && tick % 7 == 0)
            map.spawnProjectile(p->getPos().x, p->getPos().y, p->getShootDamage(), true, 10, p->getPlayerNb()+1);
    }
    map.enemyShoot(tick);
    map.bossShoot(tick);
    map.updateBounds();     // update player bounds
    map.checkCollision_client(tick, friendlyFire);

    if(map.getBoss().empty() && map.getBossSpawned())
         game_over = true;

    if(twoPlayers){
        if (player1->getnLives() < 1 && player2->getnLives() < 1)
            game_over = true;
    }else{
        if (player1->getnLives() < 1)
            game_over = true;
    }

    heal(); // remet hp du player à 100 si encore vies

    if(map.getLevelTick() != 0 && tick <= map.getLevelTick() + 600 && tick > map.getLevelTick()+100){
            if(tick == map.getLevelTick() + 600) {
                map.changeLevel();
                map.setChangingLevel(false);
            }
        }

    
    saveScore(); // sauvegarde le score

    if(exit_requested){
        game_over = true;
        getSettings(settings);
        return;
    } 
    if(game_over){
        getSettings(settings);
        
        return;
    }
    getSettings(settings);
    
    return;
}


void CurrentGame::spawnObstacle(int posx){
    
    map.spawnObstacle(posx);

};

void CurrentGame::spawnEnemy(int posx,int tick){
    
    map.spawnEnemy(posx,tick);

};

void CurrentGame::spawnBoss(int tick){
    
    map.spawnBoss(tick);

};

void CurrentGame::spawnBonus(int posx,int posy,int rand_int){
    
    map.spawnBonus_client(posx,posy,rand_int);

};

void CurrentGame::set_client_tick(int t){
	tick = t;
}


