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
        enemy_ships_set.push_back(new EnemyShip(rand() % (field_bounds.width()-1)+1, 0, { {10 - 1, 5 }, { 3, 2 } }, '%',20,10,t+rand()%100));
}
void MapHandler::spawnProjectile(int x, int y, int damage, bool type){
    projectiles_set.push_back(new Projectile(x,y,damage,type));
}

void MapHandler::checkCollision() {
    //collision player/obstacle
    for(PlayerShip* p : player_ships_set){
        for(size_t i = 0; i < obstacles_set.size(); i++){
            if(p->getBounds().contains(obstacles_set.at(i)->getPos()) && p->getHp()>0){
                p->touched(obstacles_set.at(i)->get_damage());
                obstacles_set.erase(obstacles_set.begin() + i);

            }
        }
    }
    // collision projectiles/obstacles
    for(auto & obs : obstacles_set){
        for(size_t proj = 0; proj < projectiles_set.size(); proj++){
            if(!obstacles_set.empty() && !projectiles_set.empty()){ // sinon out of range
                if(obs->getPos().x == projectiles_set.at(proj)->getPos().x && obs->getPos().y == projectiles_set.at(proj)->getPos().y){
                    obs->touched(projectiles_set.at(proj)->getDamage());
                    projectiles_set.erase(projectiles_set.begin() + proj);
                }
            }
        }
    }
    //erase obstacle
    for(size_t obs = 0; obs < obstacles_set.size(); obs++) {
        if (obstacles_set.at(obs)->getHp() <= 0)
            obstacles_set.erase(obstacles_set.begin() + obs);
    }
}

void MapHandler::playerInit(PlayerShip* p1,PlayerShip* p2) {
    player_ships_set.push_back(p1);
    player_ships_set.push_back(p2);



}

void MapHandler::updatePlayerBounds() {
    for( PlayerShip* p : player_ships_set){
        p->setBounds({ { p->getPos().x -1, p->getPos().y}, {3, 2}});

    }

}

std::vector<PlayerShip *> MapHandler::getListPlayer() const {
    return player_ships_set;
}

std::vector<EnemyShip *> MapHandler::getEnemy() const {
    return enemy_ships_set;
}

void MapHandler::enemyShoot(int tick) {
    for (auto & i : enemy_ships_set) {
        if (tick== i->getShootTime()+100){
            spawnProjectile(i->getPos().x,i->getPos().y+1,10,false);
            i->setShootTime(tick);
        }
    }
}


