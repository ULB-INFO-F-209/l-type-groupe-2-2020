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
            if(obstacles_set.at(i)->getPos().y > field_bounds.bot() + 1)
                obstacles_set.erase(obstacles_set.begin() + i);
            
        }
    }
    
    else if (typ == MapObject::projectile) {
        for(size_t i = 0; i < projectiles_set.size(); i++) {
            projectiles_set.at(i)->move();
            if(projectiles_set.at(i)->getPos().y > field_bounds.bot() + 1)
                projectiles_set.erase(projectiles_set.begin() + i);
        }
    }
    else if (typ == MapObject::enemyship) {
        for(size_t i = 0; i < enemy_ships_set.size(); i++) {
            enemy_ships_set.at(i)->move();
            if(enemy_ships_set.at(i)->getPos().y > field_bounds.bot() + 1)
                enemy_ships_set.erase(enemy_ships_set.begin() + i);

        }
    }


    // spawn a new object
    
    if(typ == MapObject::star)
        stars_set.push_back(new Star(rand() % field_bounds.width(), 0));
    else if(typ == MapObject::obstacle && t % 200 == 0)
        obstacles_set.push_back(new Obstacle(rand() % (field_bounds.width()-1)+1, 0, 10,10));
    else if (typ == MapObject::enemyship && t%300==0)
        enemy_ships_set.push_back(new EnemyShip(rand() % (field_bounds.width()-1)+1, 0, { {10 - 1, 5 }, { 3, 2 } }, '%',30,10,t+rand()%100));
}
void MapHandler::spawnProjectile(int x, int y, int damage, bool type, int hp, int player){
    projectiles_set.push_back(new Projectile(x,y,damage,type,hp, player));
}

void MapHandler::checkCollision() {
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
    //erase enemy
    for(size_t e = 0; e < enemy_ships_set.size(); e++){
        if(enemy_ships_set.at(e)->getHp() <= 0) {
            spawnBonuses(enemy_ships_set.at(e)->getPos().x, enemy_ships_set.at(e)->getPos().y);
            enemy_ships_set.erase(enemy_ships_set.begin() + e);
            //ajouter proba
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
                //player_ships_set.at(projectiles_set.at(proj)->getPlayer()-1)->setScore(player_ships_set.at(projectiles_set.at(proj)->getPlayer()-1)->getScore() + 10);
                proj->touched(proj->getHp());
                if(player_ships_set.size() == 2){
                    player_ships_set.at(proj->getPlayer()-1)->setScore(player_ships_set.at(proj->getPlayer()-1)->getScore() + 10);
                }
                else if (player_ships_set.size() == 1) { 
                    player_ships_set.at(0)->setScore(player_ships_set.at(0)->getScore() + 10);
                }
            }
        }
    }
    //erase enemy
    for(size_t e = 0; e < enemy_ships_set.size(); e++){
        if(enemy_ships_set.at(e)->getHp() <= 0)enemy_ships_set.erase(enemy_ships_set.begin() + e);
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
            spawnProjectile(i->getPos().x,i->getPos().y+1,10,false,10,0);
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
    bonusType  bonusT = bonusType(rand()%4); // à changer si nombre de bonus change
    bonuses_set.push_back(new Bonus(x, y, bonusT ));
}