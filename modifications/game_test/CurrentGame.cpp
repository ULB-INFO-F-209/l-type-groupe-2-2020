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
//Constructeur
CurrentGame::CurrentGame(Parsing::Game_settings game_sett):twoPlayers(game_sett.nb_player == 2? true:false),friendlyFire(game_sett.ally_shot), dropRate(game_sett.drop_rate),dif(game_sett.diff),screen_area( {0, 0}, {80, 24}),game_area( {0, 0}, {78, 16}),map(dropRate,dif) {
        
        playership1 = new PlayerShip(10, 5, { {9, 5 }, { 3, 2 } }, '0',100, 0,100,0);
        player1 = new Player(game_sett.nb_lives);
        listPlayer.push_back(player1);

        if(twoPlayers){
            playership2 = new PlayerShip(50, 5, { { 49, 5 }, { 3, 2 } }, '1',100, 1,100,0);
            player2 = new Player(game_sett.nb_lives);
            listPlayer.push_back(player2);
        }
        map.playerInit(playership1,playership2);
        map.setBounds(game_area);
        
    }


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


std::string CurrentGame::run_server(char move_to_exec){
    uint_fast16_t x1,y1,x2,y2;

    x1 = playership1->getPos().x;
    y1 = playership1->getPos().y;
    execInput(move_to_exec, x1, y1, true);
    if(twoPlayers){
        x2 = playership2->getPos().x;
        y2 = playership2->getPos().y;
        execInput(move_to_exec, x2, y2, false);
    }
     
    // update object field
    if(tick % 7 == 0)
        map.update_server(MapObject::projectile, tick);
    if(tick > 100 && tick %50  == 0)
        map.update_server(MapObject::obstacle, tick);
    if (tick > 100 && tick %150 ==0)
        map.update_server(MapObject::enemyship, tick);
    if(tick %50  == 0) {
        map.update_server(MapObject::bonus, tick);
    }
    if(map.getCurrentLevel()==3 && tick%10==0 && !map.getChangingLevel()){
        map.update_server(MapObject::boss,tick);
    }

    for( PlayerShip* p : map.getListPlayer()){
        if (p->getCurrentBonus()==minigun && p->getHp()>0 && tick % 7 == 0)
            map.spawnProjectile_server(p->getPos().x, p->getPos().y, p->getShootDamage(), true, 10, p->getPlayerNb()+1);
    }
    map.enemyShoot_server(tick);
    map.bossShoot_server(tick);
    map.updateBounds();     // update player bounds
    map.checkCollision_server(tick, friendlyFire);


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
    tick++;
    std::string to_ret = map.getState(player1->getnLives(), player2 == nullptr?0:player2->getnLives(),tick);
    if(game_over) return "END GAME";

    return to_ret;
};
