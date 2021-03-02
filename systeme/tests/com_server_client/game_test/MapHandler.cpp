//
// Created by ubuntu on 2/6/21.
//

#include "MapHandler.hpp"

void MapHandler::erase(size_t i, MapObject::type typ) { //1ier elem=index(0)
    if (typ == MapObject::star) {
        stars_set.erase(stars_set.begin() + i);
    }
    else if (typ == MapObject::obstacle) {
        obstacles_set.erase(obstacles_set.begin() + i);
    }
    else if(typ==MapObject::playership){
        player_ships_set.erase(player_ships_set.begin()+i);
    }
    else if(typ==MapObject::enemyship){
        enemy_ships_set.erase(enemy_ships_set.begin()+i);
    }

}
std::vector<Star*> MapHandler::getStars() const  { return stars_set; } // renvoyer le vect du map handler
std::vector<Obstacle*> MapHandler::getObstacles() const  { return obstacles_set; }
std::vector<Projectile*> MapHandler::getProjectiles() const {return projectiles_set;}
std::vector<Projectile*> MapHandler::getProjectilesEnemy() const {return projectilesEnemy_set;}
void MapHandler::setBounds(rect a) { field_bounds = a; }
void MapObject::move() {pos.y += 1;}
void Projectile::move() {
    if(shipType){
        pos.y -= 1;
    }else{
        pos.y += 1;
    }
}
vec2i MapObject::getPos() const {return pos;}
void MapObject::touched(int dam) {
    if ((hp - dam) < 0 ) hp = 0;
    else hp-=dam;
}
void MapHandler::update(MapObject::type typ, int t) {
    if (typ == MapObject::star) {
        for(size_t i = 0; i < stars_set.size(); i++) {
            if(stars_set.at(i)->getPos().y > field_bounds.bot() + 1)
                stars_set.erase(stars_set.begin() + i);

        }
    }
    else if (typ == MapObject::obstacle) {
        for(size_t i = 0; i < obstacles_set.size(); i++) {
            if(obstacles_set.at(i)->getPos().y > field_bounds.bot() + 1)
                obstacles_set.erase(obstacles_set.begin() + i);

        }
    }
    else if (typ == MapObject::projectile) {
        for(size_t i = 0; i < projectiles_set.size(); i++) {
            if(projectiles_set.at(i)->getPos().y > field_bounds.bot() + 1)
                projectiles_set.erase(projectiles_set.begin() + i);

        }
        for(size_t e = 0; e < projectilesEnemy_set.size(); e++) {
            if(projectilesEnemy_set.at(e)->getPos().y > field_bounds.bot() + 1)
                projectilesEnemy_set.erase(projectilesEnemy_set.begin() + e);

        }

    }else if (typ == MapObject::enemyship) {
        for(size_t i = 0; i < enemy_ships_set.size(); i++) {
            if(enemy_ships_set.at(i)->getPos().y > field_bounds.bot() + 1){
                enemy_ships_set.erase(enemy_ships_set.begin() + i);
                if(enemyCount == enemyLimit && changingLevel && enemy_ships_set.empty()){
                levelTick = t;
                enemyCount = 0;
                currentLevel++;
                }
            }


        }
    }else if (typ == MapObject::bonus) {
        for(size_t i = 0; i < bonuses_set.size(); i++) {
            if(bonuses_set.at(i)->getPos().y > field_bounds.bot() + 1)
                bonuses_set.erase(bonuses_set.begin() + i);

        }
    }
    // update existing objects
    if (typ == MapObject::star) {
        for(size_t i = 0; i < stars_set.size(); i++) {
            stars_set.at(i)->move();
            if(stars_set.at(i)->getPos().y > field_bounds.bot() + 1)
                stars_set.erase(stars_set.begin() + i);

        }
    }

    if (typ==MapObject::boss){
        for (auto & i : boss_set) {
            i->move();
            if (i->getPos().x > field_bounds.right()-19)
                i->setMovingRight(false);
            else if(i->getPos().x <= field_bounds.left())
                i->setMovingRight(true);
        }
    }

    else if (typ == MapObject::obstacle) {
        for(auto & i : obstacles_set) {
            i->move();
        }
    }

    else if (typ == MapObject::projectile) {
        for(auto & i : projectiles_set) {
            i->move();
        }
        for(auto & e : projectilesEnemy_set) {
            e->move();
        }
    }
    else if (typ == MapObject::enemyship) {
        for(auto & i : enemy_ships_set) {
            i->move();

        }
    }

    else if (typ == MapObject::bonus) {
        for(size_t i = 0; i < bonuses_set.size(); i++) {
            bonuses_set.at(i)->move();

        }
    }

    // spawn a new object

    if(typ == MapObject::star )
        stars_set.push_back(new Star(rand() % field_bounds.width(), 0));
    else if(typ == MapObject::obstacle && t % 200 == 0 && !changingLevel && !bossSpawned)
        obstacles_set.push_back(new Obstacle(rand() % (field_bounds.width()-1)+1, 0, obstacleStartDamage,obstacleStartHp));
    else if (typ == MapObject::enemyship && t%300==0 && !changingLevel&&!bossSpawned) {
        enemy_ships_set.push_back(new EnemyShip(rand() % (field_bounds.width() - 1) + 1, 0, {{10 - 1, 5},{3,      2}}, '%', enemyStartHp,t + rand() % 100, enemyStartProjectileDamage));
        enemyCount++;
          if(enemyCount >= enemyLimit){
              changingLevel = true;
          }

    }
    else if (typ==MapObject::boss && (currentLevel==6) && !bossSpawned){
        boss_set.push_back(new Boss(0,0,{{0, 0},{18,6}},'&',1000,t + 100, enemyStartProjectileDamage));
        bossSpawned=true;
    }
}
void MapHandler::spawnProjectile(int x, int y, int damage, bool type, int hp, int player){
    if(player!=0) {
        if (player_ships_set.size() == 2) {
            if (player_ships_set.at(player - 1)->getCurrentBonus() == tripleShot) {
                projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
                projectiles_set.push_back(new Projectile(x - 1, y - 1, damage, type, hp, player));
                projectiles_set.push_back(new Projectile(x + 1, y - 1, damage, type, hp, player));

            } else if (player_ships_set.at(player - 1)->getCurrentBonus() == lifeSteal) {
                projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
            }
            else if (player_ships_set.at(player - 1)->getCurrentBonus() == minigun) {
                projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
            }
            else if (player_ships_set.at(player - 1)->getCurrentBonus() == noBonus) {
                projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
            }
            else if (player_ships_set.at(player - 1)->getCurrentBonus() == damageUp) {
                projectiles_set.push_back(
                        new Projectile(x, y - 1, player_ships_set.at(player - 1)->getShootDamage()+40, type, hp, player));
            }
        }
        else {
            if (player_ships_set.at(0)->getCurrentBonus() == tripleShot) {
                projectiles_set.push_back(new Projectile(x - 1, y - 1, damage, type, hp, player));
                projectiles_set.push_back(new Projectile(x + 1, y - 1, damage, type, hp, player));
                projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
            } else if (player_ships_set.at(0)->getCurrentBonus() == lifeSteal) {
                projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp , player));
            } else if (player_ships_set.at(0)->getCurrentBonus() == minigun) {
                projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
            } else if (player_ships_set.at(0)->getCurrentBonus() == noBonus) {
                projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
            }
            else if (player_ships_set.at(0)->getCurrentBonus() == damageUp) {
                if (player_ships_set.at(0)->getShootDamage() != 20)
                    player_ships_set.at(0)->setShootDamage(20);
                projectiles_set.push_back(
                        new Projectile(x, y - 1, player_ships_set.at(0)->getShootDamage(), type, hp, player));
            }
        }
    }
    else projectilesEnemy_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
}
void MapHandler::checkCollision(int t, bool friendlyFire) {
    //collision player/obstacle
    for(PlayerShip* p : player_ships_set){
        for(auto & i : obstacles_set){
            if(p->getBounds().contains(i->getPos()) && p->getHp()>0){
                p->touched(i->get_damage());
                i->touched(i->getHp());
            }
        }
    }

    // collision projectiles/obstacles
    for(auto & obs : obstacles_set){
        for(auto & proj : projectiles_set){
            if(!obstacles_set.empty() && !projectiles_set.empty()){ // sinon out of range
                if(obs->getPos().x == proj->getPos().x && obs->getPos().y == proj->getPos().y){
                    obs->touched(proj->getDamage());
                    proj->touched(obs->get_damage());
                }
            }
        }
        for (auto & projE : projectilesEnemy_set){
            if(!obstacles_set.empty() && !projectilesEnemy_set.empty()){ // sinon out of range
                if(obs->getPos().x == projE->getPos().x && obs->getPos().y == projE->getPos().y){
                    obs->touched(projE->getDamage());
                    projE->touched(obs->get_damage());
                }
            }
        }
    }

    // collision enemy/player
    for(PlayerShip* p : player_ships_set){
        for(auto & e : enemy_ships_set){
            if(p->getBounds().contains(e->getBounds()) && p->getHp()>0){
                p->touched(p->getHp());
                e->touched(p->getDammage());
            }
        }
    }
    
    //collision player/player
    if(player_ships_set.size() > 1 && friendlyFire){
    
        if(player_ships_set.at(0)->getBounds().contains(player_ships_set.at(1)->getBounds()) && player_ships_set.at(0)->getHp()>0){
            player_ships_set.at(0)->touched(player_ships_set.at(0)->getHp());
            player_ships_set.at(1)->touched(player_ships_set.at(1)->getHp());
        }
            
    }

    // collision player/projectile
    for(PlayerShip* p : player_ships_set){
        for(auto & proj : projectilesEnemy_set){
            if(p->getBounds().contains(proj->getPos()) && p->getHp()>0){
                p->touched(proj->getDamage());
                proj->touched(proj->getHp());
            }
        }
        if(friendlyFire){
            for(auto & proj : projectiles_set){
                if(p->getBounds().contains(proj->getPos()) && p->getHp()>0 && p->getPlayerNb()!=proj->getPlayer()-1){
                    p->touched(proj->getDamage());
                    proj->touched(proj->getHp());
                }
            }
        }
    }

    // collision projectile/projectile
    for(auto & projA : projectiles_set){
        for(auto & projE : projectilesEnemy_set){
            if (projA->getPos().x == projE->getPos().x
            && (projA->getPos().y == projE->getPos().y
            || projA->getPos().y+1 == projE->getPos().y)) {
                projA->touched(projA->getHp());
                projE->touched(projE->getHp());
            }
        }
    }

    //collision enemy/projectile
    for(EnemyShip* e : enemy_ships_set){
        for(auto & proj : projectiles_set){
            if(e->getBounds().contains(proj->getPos()) && e->getHp()>0){
                e->touched(proj->getDamage());
                proj->touched(e->getDammage());
                if(player_ships_set.size() == 2){
                    player_ships_set.at(proj->getPlayer()-1)->setScore(player_ships_set.at(proj->getPlayer()-1)->getScore() + 10);
                    if(e->getHp()==0 && player_ships_set.at(proj->getPlayer()-1)->getCurrentBonus()==lifeSteal && player_ships_set.at(proj->getPlayer()-1)->getHp()<100){
                        if ((player_ships_set.at(proj->getPlayer()-1)->getHp()+10) <= 100)
                            player_ships_set.at(proj->getPlayer()-1)->setHp(player_ships_set.at(proj->getPlayer()-1)->getHp()+10);
                        else player_ships_set.at(proj->getPlayer()-1)->setHp(100);
                    }

                }
                else if (player_ships_set.size() == 1) {
                    player_ships_set.at(0)->setScore(player_ships_set.at(0)->getScore() + 10);
                    if(e->getHp()==0 && player_ships_set.at(0)->getCurrentBonus()==lifeSteal && player_ships_set.at(0)->getHp()<100){
                        if ((player_ships_set.at(0)->getHp()+10) <= 100)
                            player_ships_set.at(0)->setHp(player_ships_set.at(0)->getHp()+10);
                        else player_ships_set.at(0)->setHp(100);
                    }
                }
            }
        }
    }

    //collison player/bonus
    for(PlayerShip* p : player_ships_set){
        for(auto & b : bonuses_set){
            if(p->getBounds().contains(b->getPos()) && p->getHp()>0){
                p->catchBonus(b);
                b->touched(b->getHp());
            }
        }
    }

    //collision Boss/projectile
    for(Boss* b : boss_set){
        for(auto & proj : projectiles_set){
            if(b->getBounds().contains(proj->getPos()) && b->getHp()>0){
                b->touched(proj->getDamage());
                proj->touched(b->getDammage());
                if(player_ships_set.size() == 2){
                    player_ships_set.at(proj->getPlayer()-1)->setScore(player_ships_set.at(proj->getPlayer()-1)->getScore() + 10);
                    if(b->getHp()==0 && player_ships_set.at(proj->getPlayer()-1)->getCurrentBonus()==lifeSteal && player_ships_set.at(proj->getPlayer()-1)->getHp()<100){
                        if ((player_ships_set.at(proj->getPlayer()-1)->getHp()+10) <= 100)
                            player_ships_set.at(proj->getPlayer()-1)->setHp(player_ships_set.at(proj->getPlayer()-1)->getHp()+10);
                        else player_ships_set.at(proj->getPlayer()-1)->setHp(100);
                    }

                }
                else if (player_ships_set.size() == 1) {
                    player_ships_set.at(0)->setScore(player_ships_set.at(0)->getScore() + 10);
                    if(b->getHp()==0 && player_ships_set.at(0)->getCurrentBonus()==lifeSteal && player_ships_set.at(0)->getHp()<100)
                        player_ships_set.at(0)->setHp(player_ships_set.at(0)->getHp()+10);
                }
            }
        }
    }

    //collision player/boss
    for(PlayerShip* p : player_ships_set){
        for(auto & b : boss_set){
            if(p->getBounds().contains(b->getBounds()) && p->getHp()>0){
                p->touched(p->getHp());
                b->touched(p->getDammage());
            }
        }
    }

    //erase enemy
    for(size_t e = 0; e < enemy_ships_set.size(); e++){
        if(enemy_ships_set.at(e)->getHp() <= 0){
            if (rand()%100<=probaBonus)
                spawnBonuses(enemy_ships_set.at(e)->getPos().x, enemy_ships_set.at(e)->getPos().y);
            enemy_ships_set.erase(enemy_ships_set.begin() + e);
            if(enemyCount == enemyLimit && changingLevel && enemy_ships_set.empty()){
                levelTick = t;
                enemyCount = 0;
                currentLevel++;
            }
        }
    }
    //erase boss
    for(size_t e = 0; e < boss_set.size(); e++){
        if(boss_set.at(e)->getHp() <= 0){
            boss_set.erase(boss_set.begin() + e);
            if(enemyCount == enemyLimit && changingLevel && boss_set.empty()){
                levelTick = t;
                enemyCount = 0;
                currentLevel++;
            }
        }
    }
    // erase bonus
    for(size_t bon = 0; bon < bonuses_set.size(); bon++){
        if(bonuses_set.at(bon)->getHp() <= 0)bonuses_set.erase(bonuses_set.begin() + bon);
    }

    //erase obstacle
    for(size_t obs = 0; obs < obstacles_set.size(); obs++) {
        if (obstacles_set.at(obs)->getHp() <= 0)
            obstacles_set.erase(obstacles_set.begin() + obs);
    }
    //erase projectiles
    for(size_t proj = 0; proj < projectiles_set.size(); proj++){
        if(projectiles_set.at(proj)->getHp() <= 0)projectiles_set.erase(projectiles_set.begin() + proj);
    }

    //erase enemy projectiles
    for(size_t projE = 0; projE < projectilesEnemy_set.size(); projE++){
        if(projectilesEnemy_set.at(projE)->getHp() <= 0)projectilesEnemy_set.erase(projectilesEnemy_set.begin() + projE);
    }
}
void MapHandler::playerInit(PlayerShip* p1,PlayerShip* p2) {
    player_ships_set.push_back(p1);
    if(p2)player_ships_set.push_back(p2);
}
void MapHandler::updateBounds() {
    for( PlayerShip* p : player_ships_set){
        p->setBounds({ { static_cast<uint_fast16_t>(p->getPos().x -1), p->getPos().y}, {3, 2}});
    }
    for(EnemyShip* e: enemy_ships_set){
        e->setBounds({{static_cast<uint_fast16_t>(e->getPos().x-1), e->getPos().y},{3,1}});
    }
    for(Boss* b: boss_set){
        b->setBounds({{static_cast<uint_fast16_t>(b->getPos().x), b->getPos().y},{18,6}});
    }

}
std::vector<PlayerShip *> MapHandler::getListPlayer() const {
    return player_ships_set;
}
std::vector<EnemyShip *> MapHandler::getEnemy() const {
    return enemy_ships_set;
}
std::vector<Bonus*> MapHandler::getBonus() const {
    return bonuses_set;
}
void MapHandler::enemyShoot(int tick) {
    for (auto & i : enemy_ships_set) {
        if (tick== i->getShootTime()+100){
            spawnProjectile(i->getPos().x,i->getPos().y+1,i->getShootDamage(),false,i->getProjectileHp(),0);
            i->setShootTime(tick);
        }
    }
}
void MapHandler::bossShoot(int tick) {
    for (auto & b : boss_set) {
        if (tick== b->getShootTime()+50){
            spawnProjectile(b->getPos().x+7,b->getPos().y+5,b->getShootDamage(),false,b->getProjectileHp(),0);
            spawnProjectile(b->getPos().x+11,b->getPos().y+5,b->getShootDamage(),false,b->getProjectileHp(),0);

            b->setShootTime(tick);
        }
    }
}
void MapHandler::explosion() {
    for (auto & i : enemy_ships_set) {
        i->touched(20);
    }
}
void MapHandler::spawnBonuses(int x, int y) {
    auto bonusT = bonusType(rand()%4); // à changer si nombre de bonus change
    bonuses_set.push_back(new Bonus(x, y, bonusT ));
}
void MapHandler::changeLevel() {

    if(currentLevel==2){
        enemyLimit+=5;
        enemyStartHp+=10;
        enemyStartProjectileDamage+=5;
    }
    else if(currentLevel==3){
        enemyLimit+=15;
    }
    else if(currentLevel==4){
        enemyStartHp+=10;
        enemyStartProjectileDamage+=5;
    }
    else if(currentLevel==5){
        enemyLimit+=5;
        obstacleStartHp+=10;
        obstacleStartDamage+=10;
    }

}
std::vector<Boss *> MapHandler::getBoss() const {
    return boss_set;
}
MapHandler::MapHandler(int p, difficulty d): probaBonus(p),dif(d){
    if(d==easy){
        enemyLimit=5;
        enemyStartHp = 30;
        enemyStartProjectileDamage = 10;
        obstacleStartHp = 10;
        obstacleStartDamage = 10;
    }
    else if(d==medium){
        enemyLimit=10;
        enemyStartHp = 35;
        enemyStartProjectileDamage = 15;
        obstacleStartHp = 15;
        obstacleStartDamage = 15;
    }
    else{
        enemyLimit=20;
        enemyStartHp = 45;
        enemyStartProjectileDamage = 25;
        obstacleStartHp = 25;
        obstacleStartDamage = 25;
    }
}
void PlayerShip::catchBonus(const Bonus* b) {
        this->setCurrentBonus(b->getBonusType());
}