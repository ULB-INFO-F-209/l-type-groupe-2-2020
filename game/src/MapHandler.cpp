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
void MapHandler::setBounds(rect a) { field_bounds = a; }

void MapObject::move() {pos.y += 1;}

void Projectile::move() {
    if(shipType){
        pos.y -= 1;
    }else{
        pos.y += 1;
    }
}

void Obstacle::touched(int dam) {hp-=dam;} //hp-=damage;

vec2i MapObject::getPos() const {return pos;}

void MapObject::touched(int dam) {
    hp-=dam;
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
    }else if (typ == MapObject::enemyship) {
        for(size_t i = 0; i < enemy_ships_set.size(); i++) {
            if(enemy_ships_set.at(i)->getPos().y > field_bounds.bot() + 1){
                enemy_ships_set.erase(enemy_ships_set.begin() + i);
                if(enemyCount == 5 && changingLevel && enemy_ships_set.size() == 0){
                levelTick = t;
                enemyCount = 0;
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
    
    else if (typ == MapObject::obstacle) {
        for(size_t i = 0; i < obstacles_set.size(); i++) {
            obstacles_set.at(i)->move();            
        }
    }
    
    else if (typ == MapObject::projectile) {
        for(size_t i = 0; i < projectiles_set.size(); i++) {
            projectiles_set.at(i)->move();
            
        }
    }
    else if (typ == MapObject::enemyship) {
        for(size_t i = 0; i < enemy_ships_set.size(); i++) {
            enemy_ships_set.at(i)->move();
            
        }
    }

    else if (typ == MapObject::bonus) {
        for(size_t i = 0; i < bonuses_set.size(); i++) {
            bonuses_set.at(i)->move();
            if(bonuses_set.at(i)->getPos().y > field_bounds.bot() + 1)
                bonuses_set.erase(bonuses_set.begin() + i);

        }
    }

    // spawn a new object
    
    if(typ == MapObject::star)
        stars_set.push_back(new Star(rand() % field_bounds.width(), 0));
    else if(typ == MapObject::obstacle && t % 200 == 0 && !changingLevel)
        obstacles_set.push_back(new Obstacle(rand() % (field_bounds.width()-1)+1, 0, obstacleStartDamage,obstacleStartHp));
    else if (typ == MapObject::enemyship && t%300==0 && !changingLevel) {
        enemy_ships_set.push_back(new EnemyShip(rand() % (field_bounds.width() - 1) + 1, 0, {{10 - 1, 5},{3,      2}}, '%', enemyStartHp,t + rand() % 100, enemyStartProjectileDamage));
        enemyCount++;
        if(enemyCount >= 5){
            changingLevel = true;
            currentLevel++;
        }
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
                if (player_ships_set.at(player - 1)->getShootDamage() != 20)
                    player_ships_set.at(player - 1)->setShootDamage(20);
                projectiles_set.push_back(
                        new Projectile(x, y - 1, player_ships_set.at(player - 1)->getShootDamage(), type, hp, player));
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
    else projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
}

void MapHandler::checkCollision(int t) {
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

    // collision player/projectile
    for(PlayerShip* p : player_ships_set){
        for(auto & proj : projectiles_set){
            if(!proj->getShipType() && p->getBounds().contains(proj->getPos()) && p->getHp()>0){
                p->touched(proj->getDamage());
                proj->touched(proj->getHp());
            }
        }
    }

    // collision projectil/projectile
    for(size_t proj1 = 0; proj1 < projectiles_set.size(); proj1++){
        for(size_t proj2 = 0; proj2 < projectiles_set.size(); proj2++){
            //add condition to check if player is alive after shooting
            if(projectiles_set.at(proj1) != projectiles_set.at(proj2) && projectiles_set.at(proj1)->getPos().x == projectiles_set.at(proj2)->getPos().x && projectiles_set.at(proj1)->getPos().y == projectiles_set.at(proj2)->getPos().y){  
                projectiles_set.at(proj1)->touched(projectiles_set.at(proj1)->getDamage());
                projectiles_set.at(proj2)->touched(projectiles_set.at(proj2)->getDamage());
            }
        }
    }
    
    //collision enemy/projectile
    for(EnemyShip* e : enemy_ships_set){
        for(auto & proj : projectiles_set){
            if(proj->getShipType() && e->getBounds().contains(proj->getPos()) && e->getHp()>0){
                e->touched(proj->getDamage());
                proj->touched(e->getDammage());
                if(player_ships_set.size() == 2){
                    player_ships_set.at(proj->getPlayer()-1)->setScore(player_ships_set.at(proj->getPlayer()-1)->getScore() + 10);
                    if(e->getHp()==0 && player_ships_set.at(proj->getPlayer()-1)->getCurrentBonus()==lifeSteal && player_ships_set.at(proj->getPlayer()-1)->getHp()<100)
                        player_ships_set.at(proj->getPlayer()-1)->setHp(player_ships_set.at(proj->getPlayer()-1)->getHp()+10);
                }
                else if (player_ships_set.size() == 1) { 
                    player_ships_set.at(0)->setScore(player_ships_set.at(0)->getScore() + 10);
                    if(e->getHp()==0 && player_ships_set.at(0)->getCurrentBonus()==lifeSteal && player_ships_set.at(0)->getHp()<100)
                        player_ships_set.at(0)->setHp(player_ships_set.at(0)->getHp()+10);

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


    //erase enemy
    for(size_t e = 0; e < enemy_ships_set.size(); e++){
        if(enemy_ships_set.at(e)->getHp() <= 0){
            if (rand()%100<=probaBonus)
                spawnBonuses(enemy_ships_set.at(e)->getPos().x, enemy_ships_set.at(e)->getPos().y);
            enemy_ships_set.erase(enemy_ships_set.begin() + e);
            if(enemyCount == 5 && changingLevel && enemy_ships_set.size() == 0){
                levelTick = t;
                enemyCount = 0;
            }
        }
    }
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
}

void MapHandler::playerInit(PlayerShip* p1,PlayerShip* p2) {
    player_ships_set.push_back(p1);
    player_ships_set.push_back(p2);
}

void MapHandler::updatePlayerBounds() {
    for( PlayerShip* p : player_ships_set){
        p->setBounds({ { static_cast<uint_fast16_t>(p->getPos().x -1), p->getPos().y}, {3, 2}});
    }
    for(EnemyShip* e: enemy_ships_set){
        e->setBounds({{static_cast<uint_fast16_t>(e->getPos().x-1), e->getPos().y},{3,1}});
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

void MapHandler::explosion() {
    for (auto & i : enemy_ships_set) {
        i->touched(20);
    }
}

void MapHandler::spawnBonuses(int x, int y) {
    auto bonusT = bonusType(rand()%4); // à changer si nombre de bonus change
    bonuses_set.push_back(new Bonus(x, y, bonusT ));
}

void PlayerShip::catchBonus(const Bonus* b) {
        this->setCurrentBonus(b->getBonusType());
}
