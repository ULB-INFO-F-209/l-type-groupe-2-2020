//
// Created by jean on 19/02/2021.
//

#include "CurrentGame.hpp"


void CurrentGame::execInput(int in_char, uint_fast16_t x1, uint_fast16_t y1, uint_fast16_t x2, uint_fast16_t y2){
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
                map.spawnProjectile(playership1->getPos().x, playership1->getPos().y -1, 10, true, 10, 1);
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
                map.spawnProjectile(playership2->getPos().x, playership2->getPos().y -1, 10, true, 10, 2);
            break;
        default:
            break;
    }
}

//===================================================================================================

void CurrentGame::heal() {      // remet hp du player à 100 si encore vies
    for( PlayerShip* p : map.getListPlayer()){   
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
    }
}

//===================================================================================================

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

//===================================================================================================

void CurrentGame::run() {

    listPlayer.push_back(player1);
    listPlayer.push_back(player2);
    Interface anInterface;
    anInterface.init();
    map.playerInit(playership1,playership2);
    map.setBounds(game_area);
    anInterface.initialDraw();
    while(1) {
        
        // get input
        in_char = wgetch(main_wnd);
        in_char = tolower(in_char);
        
        
        uint_fast16_t x1 = playership1->getPos().x;
        uint_fast16_t y1 = playership1->getPos().y;
        uint_fast16_t  x2 = playership2->getPos().x;
        uint_fast16_t y2 = playership2->getPos().y;

        // fonction du switch
        execInput(in_char, x1, y1, x2, y2);    // peut changer le exit_requested


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

        heal(); // remet hp du player à 100 si encore vies
        
        saveScore(); // sauvegarde le score     FIXME: devons nous le faire à chaque tick ?

        if(exit_requested || game_over) break;

        tick++;
        anInterface.display(&map,tick,&listPlayer,playership1,playership2,player1,player2,finalScore1,finalScore2);

    }
    anInterface.close();
}