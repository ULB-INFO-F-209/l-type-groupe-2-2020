#include "CurrentGame.hpp"

CurrentGame::CurrentGame(Parsing::Game_settings game_sett):twoPlayers(game_sett.nb_player == 2? true:false),friendlyFire(game_sett.ally_shot), dropRate(game_sett.drop_rate),dif(game_sett.diff),screen_area( {0, 0}, {80, 24}),game_area( {0, 0}, {78, 16}),map(dropRate,dif),
            enemy_queue(),obstacles_queue(),player1(),playership1() {

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
CurrentGame::CurrentGame(Parsing::Level level_sett, Parsing::Game_settings sett):twoPlayers(sett.nb_player ==2 ? true:false),friendlyFire(sett.ally_shot), dropRate(sett.drop_rate), dif(sett.diff),screen_area( {0, 0}, {80, 24}),game_area( {0, 0}, {78, 16}),map(dropRate,dif),
        enemy_queue(level_sett.enemy_list),obstacles_queue(level_sett.obs_list),player1(),playership1(),boss(level_sett.player.boss){
    playership1 = new PlayerShip(10, 10, { {9, 5 }, { 3, 2 } }, '0',level_sett.player.hp,0,100,0);
    playershipStartHp=level_sett.player.hp;
    player1 = new Player(sett.nb_lives);
    listPlayer.push_back(player1);
    if(twoPlayers){
                playership2 = new PlayerShip(50, 10, { { 49, 5 }, { 3, 2 } }, '1',level_sett.player.hp, 1,100,0);
                player2 = new Player(sett.nb_lives);
                listPlayer.push_back(player2);
            }
    map.playerInit(playership1,playership2);
    map.setBounds(game_area);
    enemy_queue=level_sett.enemy_list;
    obstacles_queue=level_sett.obs_list;

    if (level_sett.player.speed == 0) {
        enemySpeed = 300;
        enemy2Speed = 40;
        obstacleSpeed = 100;
    }
    else if (level_sett.player.speed == 1) {
        enemySpeed = 225;
        enemy2Speed = 30;
        obstacleSpeed = 75;
    }
    else if (level_sett.player.speed == 2) {
        enemySpeed = 150;
        enemy2Speed = 20;
        obstacleSpeed = 50;
    }
    else if (level_sett.player.speed == 3) {
        enemySpeed = 100;
        enemy2Speed = 15;
        obstacleSpeed = 35;
    }
    else if (level_sett.player.speed == 4) {
        enemySpeed = 75;
        enemy2Speed = 10;
        obstacleSpeed = 25;
    }

}


void CurrentGame::execInput(int* inChar, uint_fast16_t x1, uint_fast16_t y1, bool firstPlayer){
    for(int i = 0; i <11; i++){

        if(firstPlayer){
            switch(inChar[i]) {
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
                    //Si hp a plus de 0, le joueur ne clignote pas, il peut jouer, sinon non
                    //&& bonus minigun actif (tir auto)
                    if(playership1->getHp()>0 && playership1->getCurrentBonus()!=minigun)
                        map.spawnProjectile(int(playership1->getPos().x), int(playership1->getPos().y), playership1->getShootDamage(), true, 10, 1);
                    break;
                default:
                break;
                }

        }
        else{
            switch(inChar[i]) {

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
                        map.spawnProjectile(int(playership2->getPos().x), int(playership2->getPos().y), playership1->getShootDamage(), true, 10, 2);
                    break;
                default:
                    break;
                    }
            }
    }
}


void CurrentGame::heal() {
    for( PlayerShip* p : map.getListPlayer()){

        if(listPlayer.at(std::vector<Player*>::size_type (p->getPlayerNb()))->getnLives() > 0){

            // si hp à 0, PlayerShip clignote et crée une explosion
            if(p->getHp()<=0 && p->getIsAlive()){
                map.explosion();
                p->setisAlive(false);
                p->setKillTime(tick);
                //on retire une vie au joueur
                listPlayer.at(std::vector<Player*>::size_type(p->getPlayerNb()))->setnLives(listPlayer.at(std::vector<Player*>::size_type(p->getPlayerNb()))->getnLives() - 1);

            }
            // réanime PlayerShip après 3 sec
            if(tick==p->getKillTime()+300 && !p->getIsAlive()){
                p->setisAlive(true);
                p->setCurrentBonus(noBonus);
                //Custom game
                if(map.getCustomGame())
                    p->setHp(playershipStartHp);
                else
                    p->setHp(100);
            }
        }
    }
}

void CurrentGame::saveScore(){
    for( PlayerShip* p : map.getListPlayer()){
        if(p->getPlayerNb() == 0)finalScore1 = p->getScore();
        if(p->getPlayerNb() == 1)finalScore2 = p->getScore();
    }
}

void CurrentGame::destroyPlayership(){
    for( PlayerShip* p : map.getListPlayer()){
        //si le joueur n'a plus de vie
        if(listPlayer.at(std::vector<Player*>::size_type(p->getPlayerNb()))->getnLives() < 1){
            if (map.getListPlayer().size() == 2) {
                map.erase(std::vector<Player*>::size_type(p->getPlayerNb()), MapObject::playership);
            }
            else {
                map.erase(0, MapObject::playership);
            }
        }
    }
}


std::string CurrentGame::run_server(int *move_to_exec){

    execInput(move_to_exec, playership1->getPos().x, playership1->getPos().y, true);
    if(twoPlayers){
        execInput(move_to_exec, playership2->getPos().x, playership2->getPos().y, false);
    }

    // mise à jour des positions des objets
    if(tick % 7 == 0)
        map.update_server(MapObject::projectile, tick);
    if(tick > 100 && tick %50  == 0)
        map.update_server(MapObject::obstacle, tick);
    if (tick > 100 && tick %150 ==0)
        map.update_server(MapObject::enemyship, tick);
    if (tick > 100 && tick %20 ==0)
        map.update_server(MapObject::enemyship2, tick);
    if(tick %50  == 0) {
        map.update_server(MapObject::bonus, tick);
    }
    //boss après niveau 2 ou 4
    if((map.getCurrentLevel()==2 || map.getCurrentLevel()==4) && tick%10==0 && !map.getChangingLevel()){
        //on met à jour les boss
        map.update_server(MapObject::boss,tick);
    }

    for( PlayerShip* p : map.getListPlayer()){
        if (p->getCurrentBonus()==minigun && p->getHp()>0 && tick % 7 == 0)
            map.spawnProjectile(int(p->getPos().x), int(p->getPos().y), p->getShootDamage(), true, 10, p->getPlayerNb()+1);
    }
    map.enemyShoot_server(tick);
    map.bossShoot_server(tick);
    map.updateBounds();


    if (map.getCurrentLevel() == lastLevel+1) //Dernier lvl = x, si on est à x+1 -> on a gagné
        game_over =true;

    if(twoPlayers){
        if (player1->getnLives() < 1 && player2->getnLives() < 1)
            game_over =true;
    }else{
        if (player1->getnLives() < 1)
            game_over =true;
    }


    heal();

    // Fait une pause de 5 sec 1 sec après avoir tué tous les ennemis, puis passe au niveau suivant
    if(map.getLevelTick() != 0 && tick <= map.getLevelTick() + 600 && tick > map.getLevelTick()+100){
            if(tick == map.getLevelTick() + 600) {
                map.changeLevel();
                map.setChangingLevel(false);
            }
        }


    destroyPlayership();
    map.checkCollision_server(tick, friendlyFire);
    saveScore();// sauvegarde le score

    tick++;
    std::string to_ret = getPlayerState(map.getState(player1->getnLives(), player2 == nullptr?0:player2->getnLives(),tick));
    if(game_over || exit_requested){
         return "END GAME";
    }

    return to_ret;
}

std::string CurrentGame::run_server(int *move_to_exec,std::vector<Parsing::Enemy_template> enemy_list,std::vector<Parsing::Obstacle_template> obs_list){
    execInput(move_to_exec, playership1->getPos().x, playership1->getPos().y, true);
    if(twoPlayers){
        execInput(move_to_exec, playership2->getPos().x, playership2->getPos().y, false);
    }
    map.setCustomGame(true);
    // mise à jour des positions des objets
    if(tick % 7 == 0)
        map.update_server(MapObject::projectile, tick);
    if(tick > 100 && tick %obstacleSpeed  == 0)
        map.update_server(MapObject::obstacle, tick);
    if (tick > 100 && tick %enemySpeed ==0)
        map.update_server(MapObject::enemyship, tick);
    if (tick > 100 && tick %enemy2Speed ==0)
        map.update_server(MapObject::enemyship2, tick);
    if(tick %50  == 0) {
        map.update_server(MapObject::bonus, tick);
    }
    if(tick%100==0)
        map.add_object_server(MapObject::enemyship, tick, &enemy_list,&obs_list);
    if(tick%10==0){
        map.update_server(MapObject::boss,tick);
    }

    for( PlayerShip* p : map.getListPlayer()){
        if (p->getCurrentBonus()==minigun && p->getHp()>0 && tick % 7 == 0)
            map.spawnProjectile(int(p->getPos().x), int(p->getPos().y), p->getShootDamage(), true, 10, p->getPlayerNb()+1);
    }
    map.enemyShoot_server(tick);
    map.bossShoot_server(tick);
    map.updateBounds();

    if(boss && map.getEnemyCount() == int(enemy_list.size()) && map.getEnemy().size() == 0 && !map.getBossSpawned() && map.getEnemy2().size()==0){
        map.add_object_server(MapObject::boss, tick, &enemy_list, &obs_list);
        map.setBossSpawned(true);
        boss = false;
    }
    if(map.getEnemyCount() == int(enemy_list.size()) && map.getEnemy().size() == 0 && map.getBoss().empty() && !boss && map.getEnemy2().size()==0){
        game_over = true;
    }
    std::cout << " boss spawned = " << map.getBossSpawned() <<std::endl;
    std::cout << " boss empty = " << map.getBoss().empty() <<std::endl;
    if(map.getBossSpawned() && map.getBoss().empty())
        game_over=true;

    if(twoPlayers){
        if (player1->getnLives() < 1 && player2->getnLives() < 1)
            game_over = true;
    }else{
        if (player1->getnLives() < 1)
            game_over = true;
    }

    heal();



    destroyPlayership();
    map.checkCollision_server(tick, friendlyFire);
    saveScore();// sauvegarde le score

    tick++;
    std::string to_ret = getPlayerState(map.getState(player1->getnLives(), player2 == nullptr?0:player2->getnLives(),tick));

    if(game_over || exit_requested){
         return "END GAME";
    }

    return to_ret;

}


std::string CurrentGame::getPlayerState(std::string state){
    // state                                /*E_1_HP1_Vies_Score_bonus_level_tick*/


    state.append("E_");
    state.append(std::to_string(playership1->getPlayerNb()));
    state.append("_");
    state.append(std::to_string(playership1->getHp()));
    state.append("_");
    state.append(std::to_string(player1->getnLives()));
    state.append("_");
    state.append(std::to_string(playership1->getScore()));
    state.append("_");
    state.append(std::to_string(static_cast<long unsigned int>(playership1->getCurrentBonus())));
    state.append("_");
    state.append(std::to_string(map.getCurrentLevel()));
    state.append("_");
    state.append(std::to_string(tick));
    state.append("&");

    if(twoPlayers){
        state.append("E_");
        state.append(std::to_string(playership2->getPlayerNb()));
        state.append("_");
        state.append(std::to_string(playership2->getHp()));
        state.append("_");
        state.append(std::to_string(player2->getnLives()));
        state.append("_");
        state.append(std::to_string(playership2->getScore()));
        state.append("_");
        state.append(std::to_string(static_cast<long unsigned int>(playership2->getCurrentBonus())));
        state.append("_");
        state.append(std::to_string(map.getCurrentLevel()));
        state.append("_");
        state.append(std::to_string(tick));
        state.append("&");


    }
    return state;

}
