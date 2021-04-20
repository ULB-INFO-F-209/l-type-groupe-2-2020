//
// Created by ubuntu on 2/6/21.
//

#include "MapHandler.hpp"
#include <unistd.h>

void MapHandler::erase(size_t i, MapObject::type typ) {     // supprime un objet de son vecteur (ex: ennemi detruit)
    if (typ == MapObject::star) {
        stars_set.erase(stars_set.begin() + static_cast<long int>(i));  // i est la position de l'objet dans le vecteur
    }
    else if (typ == MapObject::obstacle) {
        obstacles_set.erase(obstacles_set.begin() + static_cast<long int>(i));
    }
    else if(typ==MapObject::playership){
        player_ships_set.erase(player_ships_set.begin() + static_cast<long int>(i));
    }
    else if(typ==MapObject::enemyship){
        enemy_ships_set.erase(enemy_ships_set.begin() + static_cast<long int>(i));
    }

}

std::vector<Star*> MapHandler::getStars() const  { return stars_set; }

std::vector<Obstacle*> MapHandler::getObstacles() const  { return obstacles_set; }

std::vector<Projectile*> MapHandler::getProjectiles() const {return projectiles_set;}

std::vector<Projectile*> MapHandler::getProjectilesEnemy() const {return projectilesEnemy_set;}

void MapHandler::setBounds(rect a) { field_bounds = a; }

void MapObject::move() {pos.y += 1;}    // déplacement par défaut des ennemis

void Projectile::move() {
    if(shipType){       // si le shiptype = True, alors ce sont les projectiles alliés (vont vers le haut)
        pos.y -= 1;
    }else{
        pos.y += 1;
    }
}

vec2i MapObject::getPos() const {return pos;}   // (pos = position)

void MapObject::touched(int dam) {  // fonction permettant de ne pas avoir de valeurs négatives lorsqu'on recoit un dégat
    if ((hp - dam) < 0 ) hp = 0;
    else hp-=dam;
}



void MapHandler::spawnProjectile(int x, int y, int damage, bool type, int hp, int player){
    if (y-1 >= 0) {     // permet de ne pas spawn des projectiles hors map
        if(player!=0) {     // 0=ennemi, 1=joueur1, 2=joueur2
            if (player_ships_set.size() == 2) {     // si les 2 joueurs sont encore vivants et donc 2 palyerships
                if (player_ships_set.at(static_cast<long unsigned int>(player - 1))->getCurrentBonus() == tripleShot) {     // ici on spawn 3 projetciles l'un à coté de l'autre car bonus TripleShot
                    projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
                    projectiles_set.push_back(new Projectile(x - 1, y - 1, damage, type, hp, player));
                    projectiles_set.push_back(new Projectile(x + 1, y - 1, damage, type, hp, player));

                } else if (player_ships_set.at(static_cast<long unsigned int>(player - 1))->getCurrentBonus() == lifeSteal) {
                    projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
                }
                else if (player_ships_set.at(static_cast<long unsigned int>(player - 1))->getCurrentBonus() == minigun) {
                    projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
                }
                else if (player_ships_set.at(static_cast<long unsigned int>(player - 1))->getCurrentBonus() == noBonus) {
                    projectiles_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));
                }
                else if (player_ships_set.at(static_cast<long unsigned int>(player - 1))->getCurrentBonus() == damageUp) {
                    // spawn un projectile avec + de dégats car bonus DamageUp
                    projectiles_set.push_back(new Projectile(x, y - 1, player_ships_set.at(static_cast<long unsigned int>(player - 1))->getShootDamage()+40, type, hp, player));
                }
            }
            else {  // 1 seul playership sur la map donc player_ships_set.at(0)
            // commentaiires idem qu'au dessus
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
                    
                    projectiles_set.push_back(
                            new Projectile(x, y - 1, player_ships_set.at(0)->getShootDamage()+40, type, hp, player));
                }
            }
        }
        else projectilesEnemy_set.push_back(new Projectile(x, y - 1, damage, type, hp, player));    //payer=0=Ennemi
    }    

}


void MapHandler::playerInit(PlayerShip* p1,PlayerShip* p2) {    // ajoute un vaisseau allié dans le vecteur de playerships
    player_ships_set.push_back(p1);
    if(p2)player_ships_set.push_back(p2);
}

void MapHandler::updateBounds() {       // ici les bounds représentent la place (le nombre de cases) qu'un objet occupe sur la map
    for( PlayerShip* p : player_ships_set){
        p->setBounds({ { static_cast<uint_fast16_t>(p->getPos().x -1), p->getPos().y}, {3, 2}});    // ici le player ship utilise 3 cases en longueur et 2 en hauteur
    }
    for(EnemyShip* e: enemy_ships_set){
        e->setBounds({{static_cast<uint_fast16_t>(e->getPos().x-1), e->getPos().y},{3,1}});
    }
    for(EnemyShip2* e: enemy_ships2_set){
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
std::vector<EnemyShip2 *> MapHandler::getEnemy2() const {
    return enemy_ships2_set;
}
std::vector<Bonus*> MapHandler::getBonus() const {
    return bonuses_set;
}

void MapHandler::explosion() {      // fonciton qui inflige 20 de dégat à tous les ennemis présents si un playership explose
    for (auto & i : enemy_ships_set) {
        i->touched(20);
    }
}
int MapHandler::spawnBonuses(int x, int y) {    // spawn un bonus aléatoire en fonciton de sa position
    int rand_spawn_bonus = rand()%4;    // choisit parmi les 4 bonus
    auto bonusT = bonusType(rand_spawn_bonus);
    bonuses_set.push_back(new Bonus(x, y, bonusT ));
    return rand_spawn_bonus;
}

int MapHandler::spawnBonuses(int x, int y, bonusType bonus) {   // spawn un bonus choisi (custom game) en fonction de sa position
    bonuses_set.push_back(new Bonus(x, y, bonus ));
    return bonus;
}

void MapHandler::changeLevel() {    // lorsqu'on change de niveau, certains attributs changent également pour augmenter la difficulté

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

MapHandler::MapHandler(int p, difficulty d): probaBonus(p),dif(d), boss_set(), stars_set(), obstacles_set(), projectiles_set(), projectilesEnemy_set(), player_ships_set(), enemy_ships_set(), enemy_ships2_set(), bonuses_set(), field_bounds(){
    // initialise les attributs en fonction de la difficulté
    if(d==easy){
        enemyLimit=5;
        enemyStartHp = 30;
        enemyStartProjectileDamage = 10;
        obstacleStartHp = 10;
        obstacleStartDamage = 10;
        customMultiplier = 1;
    }
    else if(d==medium){
        enemyLimit=10;
        enemyStartHp = 35;
        enemyStartProjectileDamage = 15;
        obstacleStartHp = 15;
        obstacleStartDamage = 15;
        customMultiplier = 2;

    }
    else{
        enemyLimit=20;
        enemyStartHp = 45;
        enemyStartProjectileDamage = 25;
        obstacleStartHp = 25;
        obstacleStartDamage = 25;
        customMultiplier = 3;

    }
}

void PlayerShip::catchBonus(const Bonus* b) {   // setter du currentBonus
        this->setCurrentBonus(b->getBonusType());
}


void MapHandler::update_server(MapObject::type typ,int t){
    // fonciton qui efface les objets, les déplace s'ils sont encore sur la map, les crée (en partie non personnalisée)

    // EFFACE LES OBJETS QUI N'ONT PLUS DE HP OU QUI SORTENT DE LA MAP-------------------------------------------------------------
    if (typ == MapObject::star) {       //  les etoiles sont supprimées lorsqu'elles sortent de la map
        for(size_t i = 0; i < stars_set.size(); i++) {
            if(stars_set.at(i)->getPos().y > field_bounds.bot() + 1)    // field_bounds.bot() + 1 est la limite inférieure de la map
                stars_set.erase(stars_set.begin() + static_cast<long int>(i));
        }
    }
    else if (typ == MapObject::obstacle) {
        for(size_t i = 0; i < obstacles_set.size(); i++) {
            if(obstacles_set.at(i)->getPos().y > field_bounds.bot() + 1)    // field_bounds.bot() + 1 est la limite inférieure de la map
                obstacles_set.erase(obstacles_set.begin() + static_cast<long int>(i));
        }
    }

    else if (typ == MapObject::enemyship) {
        for(size_t i = 0; i < enemy_ships_set.size(); i++) {
            if(enemy_ships_set.at(i)->getPos().y > field_bounds.bot() + 1){     // l'ennemi sort de la map sans mourir
                enemy_ships_set.erase(enemy_ships_set.begin() + static_cast<long int>(i));
                if(enemyCount == enemyLimit && changingLevel && enemy_ships_set.empty() && enemy_ships2_set.empty() ){  // si tous les ennemis sont effacés, on change de niveau
                levelTick = t;
                enemyCount = 0;
                currentLevel++;
                }
            }
        }
    }
    else if (typ == MapObject::enemyship2) {    // idem qu'au dessus
        for(size_t i = 0; i < enemy_ships2_set.size(); i++) {
            if(enemy_ships2_set.at(i)->getPos().x > field_bounds.right() + 1){
                enemy_ships2_set.erase(enemy_ships2_set.begin() + static_cast<long int>(i));
                if(enemyCount == enemyLimit && changingLevel && enemy_ships2_set.empty() && enemy_ships_set.empty()){
                levelTick = t;
                enemyCount = 0;
                currentLevel++;
                }
            }
        }
    }
    else if (typ == MapObject::bonus) {
        for(size_t i = 0; i < bonuses_set.size(); i++) {
            if(bonuses_set.at(i)->getPos().y > field_bounds.bot() + 1)  // le bonus sort de la map sans avoir été pris
                bonuses_set.erase(bonuses_set.begin() + static_cast<long int>(i));
        }
    }


    // DÉPLACE LES OBJETS DEJA EXISTANTS-----------------------------------------------------------------------
    if (typ == MapObject::star) {
        for(size_t i = 0; i < stars_set.size(); i++) {
            stars_set.at(i)->move();    // le move les deplace d'une position vers le bas
            if(stars_set.at(i)->getPos().y > field_bounds.bot() + 1)    // verifie que l'etoile sort de la map
                stars_set.erase(stars_set.begin() + static_cast<long int>(i));

        }
    }

    if (typ==MapObject::boss){
        for (auto & i : boss_set) {
            i->move();  // le move le deplace d'une position vers la droite ou vers la gauche en fonction du "movingRight"
            if (i->getPos().x > field_bounds.right()-19)    // le "-19" est pris en compte pour la taille du Boss
                i->setMovingRight(false);
            else if(i->getPos().x <= field_bounds.left())
                i->setMovingRight(true);
        }
    }

    else if (typ == MapObject::obstacle) {
        for(auto & i : obstacles_set) {
            i->move();      // déplace l'obstacle d'une position vers le bas
        }
    }

    else if (typ == MapObject::projectile) {
        for(auto & i : projectiles_set) {
            i->move(); // déplace d'une position vers le haut
        }
        for(auto & e : projectilesEnemy_set) {
            e->move();  // deplace d'une position vers le bas
        }

        for(size_t i = 0; i < projectiles_set.size(); ) {
            if(projectiles_set.at(i)->getPos().y > field_bounds.bot() + 1)      // efface le projectile si hors de la map
                projectiles_set.erase(projectiles_set.begin() + static_cast<long int>(i));
            else
                ++i;
        }
        for(size_t e = 0; e < projectilesEnemy_set.size();) {
            if(projectilesEnemy_set.at(e)->getPos().y > field_bounds.bot() + 1)     // efface le projectile si hors de la map
                projectilesEnemy_set.erase(projectilesEnemy_set.begin() + static_cast<long int>(e));
            else ++e;
        }
    }
    else if (typ == MapObject::enemyship) {
        for(auto & i : enemy_ships_set) {
            i->move();  // deplace d'une position vers le bas

        }
    }
    else if (typ == MapObject::enemyship2) {
        for(auto & i : enemy_ships2_set) {
            i->move();  // déplace d'une position vers la droite
        }
    }

    else if (typ == MapObject::bonus) {
        for(size_t i = 0; i < bonuses_set.size(); i++) {
            bonuses_set.at(i)->move();  // déplace d'une position vers le bas

        }
    }
    if(!customGame)     // si on est pas dans une partie personnalisée, on ajoute des objets automatiquement sur la amp
        add_object_server(typ,t);
    
}

void MapHandler::add_object_server(MapObject::type typ,int t){
        // spawn un nouvel objet sur la map en fonction de son type typ et son tick t

    if(typ == MapObject::star )
        stars_set.push_back(new Star(static_cast<uint_fast16_t>(rand()) % field_bounds.width(), 0));    // ajoute dans l'objet dans le vecteur correspondant

    if(typ == MapObject::obstacle && t % 200 == 0 && !changingLevel && !bossSpawned){   // on spawn un obstacle tous les 200 ticks
        int x = rand() % (static_cast<int>(field_bounds.width())-1)+1;      // la position de l'obstacle est choisie aléatoirement avec un rand
        obstacles_set.push_back(new Obstacle(static_cast<uint_fast16_t>(x), 0, obstacleStartDamage,obstacleStartHp));
    }
    else if (typ == MapObject::enemyship && t%300==0 && !changingLevel&&!bossSpawned) {     // on spawn un ennemi vertical tous les 300 ticks
        int x = rand() % (static_cast<int>(field_bounds.width()) - 1) + 1;  // la position de l'ennemi est choisie aléatoirement avec un rand
        int enemy_tick = t + rand() % 100;
        enemy_ships_set.push_back(new EnemyShip(static_cast<uint_fast16_t>(x), 0, {{10 - 1, 5},{3,2}}, '%', enemyStartHp,enemy_tick, enemyStartProjectileDamage));
        enemyCount++;
        if(enemyCount >= enemyLimit){     // permet de limiter le nombre d'ennemis qui apparaissent 
            changingLevel = true;
        }
    }

    else if (typ == MapObject::enemyship2 && t%400==0 && !changingLevel&&!bossSpawned) {    // on spawn un ennemi horinzontal tous les 400 ticks
        int y = rand() % (static_cast<int>(field_bounds.height())/2) + 1;   // la position de l'ennemi est choisie aléatoirement avec un rand
        int enemy_tick = t + rand() % 100;
        enemy_ships2_set.push_back(new EnemyShip2(1, static_cast<uint_fast16_t>(y), {{10 - 1, 5},{3,2}}, '@', enemyStartHp,enemy_tick, enemyStartProjectileDamage));
        enemyCount++;
        if(enemyCount >= enemyLimit){   // permet de limiter le nombre d'ennemis qui apparaissent 
            changingLevel = true;
        }
    }

    else if (typ==MapObject::boss && !bossSpawned){
        //création des boss
        if (currentLevel==2){       // premier boss avec 2 projectils et 5000 de hp
            boss_set.push_back(new Boss(0,0,{{0, 0},{18,6}},'&',5000,t + 100, enemyStartProjectileDamage, 1));  
        }  
        if (currentLevel==4){       // deuxiemme boss avec 4 projectiles et 10000 de hp
            boss_set.push_back(new Boss(0,0,{{0, 0},{18,6}},'&',10000,t + 100, enemyStartProjectileDamage, 2));  
        }
        bossSpawned=true;    
    }
}
void MapHandler::add_object_server(MapObject::type typ,int t,std::vector<Enemy_template> *enemy_list,std::vector<Obstacle_template> *obs_list){
    // PARTIE PERSONNALISÉE: on spawn un objet en fonciton de son type typ, son tick t et sa position (enregistrée dans le vecteur de cet objet)
    // le tick d'un objet est ici enregistré sous forme de seconde, un tick d'un objet *100 = 1 tick normal
    
    for (size_t i = 0; i < obs_list->size(); i++)   // Obstacle
    {
        if((obs_list->at(i).tick*100)== t)  // si le tick de l'objet *100 = tick global à ce moment, on spawn l'objet
            obstacles_set.push_back(new Obstacle(static_cast<uint_fast16_t>((obs_list->at(i).x+12.53)/12.53), 0, obs_list->at(i).damage*customMultiplier,obs_list->at(i).hp*customMultiplier));
            // on spawn en fonction du x (les 12.53 sont des calculs pour les rendre à l'echelle du terminal), le y=O car on spawn en haut de l'ecran

    }
    
    for (size_t j = 0; j < enemy_list->size(); j++)
    {
        if((enemy_list->at(j).tick*100)== t){   // si le tick de l'objet *100 = tick global à ce moment, on spawn l'objet
            int enemy_tick = t + rand() % 100;
            
            if(enemy_list->at(j).skin==0) // ennemi vertical
                enemy_ships_set.push_back(new EnemyShip(static_cast<uint_fast16_t>((enemy_list->at(j).x+ 12.53)/12.53), 0, {{10 - 1, 5},{3,2}}, '%', enemy_list->at(j).hp*customMultiplier,enemy_tick, enemy_list->at(j).damage*customMultiplier, bonusType(enemy_list->at(j).bonus)));
                // on spawn en fonction du x (les 12.53 sont des calculs pour les rendre à l'echelle du terminal), le y=O car on spawn en haut de l'ecran
            else    // ennemi horinzontal
                enemy_ships2_set.push_back(new EnemyShip2(0, static_cast<uint_fast16_t>((enemy_list->at(j).x+ 58.75)/58.75), {{10 - 1, 5},{3,2}}, '%', enemy_list->at(j).hp*customMultiplier,enemy_tick, enemy_list->at(j).damage*customMultiplier, bonusType(enemy_list->at(j).bonus)));
                // on spawn en fonction du x (ici représente le y pour les ennemis horizontaux) (les 58.75 sont des calculs pour les rendre à l'echelle du terminal)
            enemyCount++;
        }
        
    }
    if(typ== MapObject::type::boss) // si le typ vaut boss, on spawn le boss avec 10000 hp
        boss_set.push_back(new Boss(0,0,{{0, 0},{18,6}},'&',10000,t + 100, enemyStartProjectileDamage, 2));    

}

void MapHandler::bossShoot_server(int tick) {   // fonction qui s'occupe ds projectiles des boss
    for (auto & b : boss_set) {
        if (tick== b->getShootTime()+50){   // les boss tirent tous les 50 ticks

            int posx = static_cast<int>(b->getPos().x), posy = static_cast<int>(b->getPos().y)+1;   // le premier boss tire 2 projectiles
            spawnProjectile(posx+7,posy+5,b->getShootDamage(),false,b->getProjectileHp(),0);
            spawnProjectile(posx+11,posy+5,b->getShootDamage(),false,b->getProjectileHp(),0);

            if (b->getBossType()==2) {                                                              // le second en tire 2 de plus
                spawnProjectile(posx+3,posy+5,b->getShootDamage(),false,b->getProjectileHp(),0);
                spawnProjectile(posx+15,posy+5,b->getShootDamage(),false,b->getProjectileHp(),0);
            }
            b->setShootTime(tick);
        }
    }
}

void MapHandler::enemyShoot_server(int tick) {  // fonction qui s'occupe des projectiles des ennemis
    for (auto & i : enemy_ships_set) {
        if (tick== i->getShootTime()+100){  // les ennemis verticaux tirent tous les 100 tick
            int posx = static_cast<int>(i->getPos().x), posy = static_cast<int>(i->getPos().y)+1;   // récupère les positions de l'ennemi
            spawnProjectile(posx,posy,i->getShootDamage(),false,i->getProjectileHp(),0);
            i->setShootTime(tick);
        }
    }
    for (auto & i : enemy_ships2_set) {
        if (tick== i->getShootTime()+50){   // les ennemis horizontaux tirent tous les 50 ticks
            int posx = static_cast<int>(i->getPos().x), posy = static_cast<int>(i->getPos().y)+1;
            spawnProjectile(posx,posy,i->getShootDamage(),false,i->getProjectileHp(),0);
            i->setShootTime(tick);
        }
    }
}

void MapHandler::checkCollision_server(int t, bool friendlyFire) {  // s'occupe des collisions pour tous les objets de la map
    //collision player/obstacle
    for(PlayerShip* p : player_ships_set){
        for(auto & i : obstacles_set){
            if(p->getBounds().contains(i->getPos()) && p->getHp()>0){   // si les bounds du player contiennent la position de l'obstacle
                // on met des degats pour chacun des 2 objects, on les supprimera plus loin s'ils n'ont plus de hp
                p->touched(i->get_damage());
                i->touched(i->getHp());
            }
        }
    }

    // collision projectiles/obstacles
    for(auto & obs : obstacles_set){
        for(auto & proj : projectiles_set){     // on regarde en fonciton des projectiles alliés
            if(!obstacles_set.empty() && !projectiles_set.empty()){ // sinon out of range
                if(obs->getPos().x == proj->getPos().x && obs->getPos().y == proj->getPos().y){ // si les 2 objets sont sur la meme position
                    obs->touched(proj->getDamage());
                    proj->touched(obs->get_damage());
                }
            }
        }
        for (auto & projE : projectilesEnemy_set){  // on regarde en fonction des projectiles ennemis
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
            if(p->getBounds().contains(e->getBounds()) && p->getHp()>0){    // si les bounds du player contiennent les bounds de l'ennemis
                p->touched(p->getHp());
                e->touched(p->getDammage());
            }
        }
    }

    // collision enemy2/player
    for(PlayerShip* p : player_ships_set){
        for(auto & e : enemy_ships2_set){
            if(p->getBounds().contains(e->getBounds()) && p->getHp()>0){    // idem
                p->touched(p->getHp());
                e->touched(p->getDammage());
            }
        }
    }

    //collision player/player
    if(player_ships_set.size() > 1 && friendlyFire){    // is le friendlyFire est activé, les vaisseaux alliés peuvent se toucher

        if(player_ships_set.at(0)->getBounds().contains(player_ships_set.at(1)->getBounds()) && player_ships_set.at(0)->getHp()>0){
            // on enelve directement tout leurs hp pour enlever directement une vie et faire une explosion
            player_ships_set.at(0)->touched(player_ships_set.at(0)->getHp());
            player_ships_set.at(1)->touched(player_ships_set.at(1)->getHp());
        }

    }

    // collision player/projectile
    for(PlayerShip* p : player_ships_set){
        for(auto & proj : projectilesEnemy_set){
            if(p->getBounds().contains(proj->getPos()) && p->getHp()>0){ // si les bounds du player contiennet la position du projectile
                p->touched(proj->getDamage());
                proj->touched(proj->getHp());
            }
        }
        if(friendlyFire){       // si le friendlyFire est activé, les joueurs peuvent se toucher
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
            || projA->getPos().y+1 == projE->getPos().y)) {     // assurance au cas où les updates des projectiles se font en meme temps et qu'ils se croisent sans se toucher
                projA->touched(projA->getHp());
                projE->touched(projE->getHp());
            }
        }
    }

    //collision enemy/projectile
    for(EnemyShip* e : enemy_ships_set){
        for(auto & proj : projectiles_set){
            if(e->getBounds().contains(proj->getPos()) && e->getHp()>0){    // si les bounds de l'ennemi contiennet la pos du projectile
                e->touched(proj->getDamage());
                proj->touched(e->getDammage());
                if(player_ships_set.size() == 2){   // si on est 2 joueurs vivants, on recupere le player grace à son projectile pour mettre à jour son score
                    player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->setScore(player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getScore() + 10);
                    if(e->getHp()==0 && player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getCurrentBonus()==lifeSteal && player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getHp()<100){
                        // si le bonus LifeSteal est activé, on rajoute de la vie au joueur à qui appartient le projectile
                        if ((player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getHp()+10) <= 100)
                            player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->setHp(player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getHp()+10);
                        else player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->setHp(100);
                    }
                }
                else if (player_ships_set.size() == 1) {    // si 1 joueur sur la map -> player_ships_set.at(0) =  ce joueur
                    player_ships_set.at(0)->setScore(player_ships_set.at(0)->getScore() + 10);
                    if(e->getHp()==0 && player_ships_set.at(0)->getCurrentBonus()==lifeSteal && player_ships_set.at(0)->getHp()<100){
                        // si LifeSteal est activé, on ajoute de la vie à ce joueur
                        if ((player_ships_set.at(0)->getHp()+10) <= 100)
                            player_ships_set.at(0)->setHp(player_ships_set.at(0)->getHp()+10);
                        else player_ships_set.at(0)->setHp(100);
                    }
                }
            }
        }
    }
    //collision enemy2/projectile
    for(EnemyShip2* e : enemy_ships2_set){      // IDEM QU'AU DESSUS
        for(auto & proj : projectiles_set){
            if(e->getBounds().contains(proj->getPos()) && e->getHp()>0){
                e->touched(proj->getDamage());
                proj->touched(e->getDammage());
                if(player_ships_set.size() == 2){
                    player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->setScore(player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getScore() + 10);
                    if(e->getHp()==0 && player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getCurrentBonus()==lifeSteal && player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getHp()<100){
                        if ((player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getHp()+10) <= 100)
                            player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->setHp(player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getHp()+10);
                        else player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->setHp(100);
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

    //collision Boss/projectile
    for(Boss* b : boss_set){        // IDEM QU'AU DESSUS
        for(auto & proj : projectiles_set){
            if(b->getBounds().contains(proj->getPos()) && b->getHp()>0){
                b->touched(proj->getDamage());
                proj->touched(b->getDammage());
                if(player_ships_set.size() == 2){
                    player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->setScore(player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getScore() + 10);
                    if(b->getHp()==0 && player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getCurrentBonus()==lifeSteal && player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getHp()<100){
                        if ((player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getHp()+10) <= 100)
                            player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->setHp(player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->getHp()+10);
                        else player_ships_set.at(static_cast<size_t>(proj->getPlayer()-1))->setHp(100);
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
                p->touched(p->getHp()); // on explose directement le playership
                b->touched(p->getDammage());    // on enleve des hp au boss
            }
        }
    }

    //collison player/bonus
    for(PlayerShip* p : player_ships_set){
        for(auto & b : bonuses_set){
            if(p->getBounds().contains(b->getPos()) && p->getHp()>0){
                p->catchBonus(b);       // set le currentBonus du joueur qui a attapé le bonus
                b->touched(b->getHp());
            }
        }
    }

    // SUPPRIME LES OBJETS QUI N'ONT PLUS DE HP----------------------------------------------------------------
    // suppression premier type d'ennemi
    for(size_t e = 0; e < enemy_ships_set.size(); e++){
        if(enemy_ships_set.at(e)->getHp() <= 0){
            if (rand()%100<=probaBonus){    // fait tomber un bonus lors de la suppression de l'objet ennemi en fonction de la probabilité choisie avant la partie
                int posx = static_cast<int>(enemy_ships_set.at(e)->getPos().x);
                int posy = static_cast<int>(enemy_ships_set.at(e)->getPos().y);
                if(customGame)
                    spawnBonuses(posx,posy,enemy_ships_set.at(e)->getBonusType());  // si game custom, on spawn le bonus choisi de l'ennemi
                else spawnBonuses(posx, posy);
            }
            enemy_ships_set.erase(enemy_ships_set.begin() + static_cast<std::vector<vec2i*>::difference_type>(e));
            if(enemyCount == enemyLimit && changingLevel && enemy_ships_set.empty() && enemy_ships2_set.empty()){   
                // apres la suppression de l'ennemi, si la limite d'ennemis a été atteinte, on change de niveau
                levelTick = t;
                enemyCount = 0;
                currentLevel++;
            }
        }
    }

    // suppression deuxieme type d'ennemi
    for(size_t e = 0; e < enemy_ships2_set.size(); e++){    // IDEM QU'AU DESSUS
        if(enemy_ships2_set.at(e)->getHp() <= 0){
            if (rand()%100<=probaBonus){
                int posx = static_cast<int>(enemy_ships2_set.at(e)->getPos().x);
                int posy = static_cast<int>(enemy_ships2_set.at(e)->getPos().y);
                if(customGame)
                    spawnBonuses(posx,posy,enemy_ships2_set.at(e)->getBonusType());
                else spawnBonuses(posx, posy);
            }
            enemy_ships2_set.erase(enemy_ships2_set.begin() + static_cast<std::vector<vec2i*>::difference_type>(e));
            if(enemyCount == enemyLimit && changingLevel && enemy_ships2_set.empty() && enemy_ships_set.empty()){
                levelTick = t;
                enemyCount = 0;
                currentLevel++;
            }
        }
    }

    // suppression du boss
    for(size_t e = 0; e < boss_set.size(); e++){
        if(boss_set.at(e)->getHp() <= 0){
            boss_set.erase(boss_set.begin() + static_cast<std::vector<vec2i*>::difference_type>(e));
            // le boss compte comme un niveau, si le boss meurt, on change automatiquement de niveau
            levelTick = t;
            enemyCount = 0;
            currentLevel++;
            bossSpawned = false;
            changingLevel=true;
        
        }
    }
    // suppression du bonus
    for(size_t bon = 0; bon < bonuses_set.size(); bon++){
        if (bonuses_set.at(bon)->getHp() <= 0) 
            bonuses_set.erase(bonuses_set.begin() + static_cast<std::vector<vec2i*>::difference_type>(bon));    // bon est ka pos dans le vecteur
    }

    //erase obstacle
    for(size_t obs = 0; obs < obstacles_set.size(); obs++) {
        if (obstacles_set.at(obs)->getHp() <= 0)
            obstacles_set.erase(obstacles_set.begin() + static_cast<std::vector<vec2i*>::difference_type>(obs));    // obs est la pos dans le vecteur
    }
    //erase projectiles
    for(size_t proj = 0; proj < projectiles_set.size(); proj++){
        if (projectiles_set.at(proj)->getHp() <= 0) 
            projectiles_set.erase(projectiles_set.begin() + static_cast<std::vector<vec2i*>::difference_type>(proj));   // proj est la pos dans le vecteur
    }   

    //erase enemy projectiles
    for(size_t projE = 0; projE < projectilesEnemy_set.size(); projE++){
        if (projectilesEnemy_set.at(projE)->getHp() <= 0)
            projectilesEnemy_set.erase(projectilesEnemy_set.begin() + static_cast<std::vector<vec2i*>::difference_type>(projE));    // projE est la pos dans le vecteur
    }
}



std::string MapHandler::getState(int nlives_j1,int nlives_j2,int tick){     // créer le string contenant les etats des objets qui sera envoyé par le pipe
    std::string state{};
    vec2i pos{};
    std::string x, y, bossHp;
    int lives[2] = {nlives_j1,nlives_j2};
    // DISPLAY OBJECTS


    // boss_set;
    for (auto boss : boss_set){             // A_EB_x_y
        pos = boss->getPos();
        x = std::to_string(pos.x);
        y = std::to_string(pos.y);
        bossHp = std::to_string(boss->getHp()); 
        if (boss->getBossType()==1)
            state.append("A_EB_");
        else
            state.append("A_EB2_");
        state.append(x);
        state.append("_");
        state.append(y);
        state.append("_");
        state.append(bossHp);
        state.append("&");
    }

    // obstacles_set;
    for (auto obst : obstacles_set){         // A_O_x_y
        pos = obst->getPos();
        x = std::to_string(pos.x);
        y = std::to_string(pos.y);
        state.append("A_O_");
        state.append(x);
        state.append("_");
        state.append(y);
        state.append("&");
    }

    // projectiles_set;
    for (auto proj : projectiles_set){         // A_PJ_x_y
        pos = proj->getPos();
        x = std::to_string(pos.x);
        y = std::to_string(pos.y);
        if(proj->getPlayer() == 1){
            state.append("A_PJ_");
        }else{
            state.append("A_PJ2_");
        }
        state.append(x);
        state.append("_");
        state.append(y);
        state.append("&");
    }

    // projectilesEnemy_set;
    for (auto proj : projectilesEnemy_set){         // A_PE_x_y
        pos = proj->getPos();
        x = std::to_string(pos.x);
        y = std::to_string(pos.y);
        state.append("A_PE_");
        state.append(x);
        state.append("_");
        state.append(y);
        state.append("&");
    }
    

    // player_ships_set;
    for (auto player : player_ships_set){           // A_1_x_y_explosion  or  A_2_x_y_explosion
        pos = player->getPos();
        x = std::to_string(pos.x);
        y = std::to_string(pos.y);
        std::string hp = std::to_string(player->getHp());
        int player_nb = player->getPlayerNb();
        state.append("A_");
        if(player_nb == 0){
            state.append("1_");
        }
        else if(player_nb == 1){
            state.append("2_");
        }
        state.append(x);
        state.append("_");
        state.append(y);
        state.append("_");

        if(lives[player->getPlayerNb()] > 0){
            // show player looses a life

            if(player->getHp()<=0 && tick < player->getKillTime()+300){
                state.append(std::to_string(1));
            }
            else state.append(std::to_string(0));
        }
        state.append("_");
        state.append(std::to_string(tick));
        state.append("&");
    }

    // enemy_ships_set
    bool enemy_explosion= false;
    for( PlayerShip* p : player_ships_set){
        if(lives[p->getPlayerNb()] > 0){
            if(tick % 20 < 10 && p->getHp()<=0 && tick<p->getKillTime()+100){
                enemy_explosion = true;
                break;
            }

        }
    }

    for (auto enemy : enemy_ships_set){         // A_PE_x_y
        pos = enemy->getPos();
        x = std::to_string(pos.x);
        y = std::to_string(pos.y);
        state.append("A_E_");
        state.append(x);
        state.append("_");
        state.append(y);
        state.append("_");
        state.append(std::to_string(static_cast<int>(enemy_explosion)));
        state.append("&");
    }
    //enemy2
    for (auto enemy : enemy_ships2_set){         // A_PE2_x_y
        pos = enemy->getPos();
        x = std::to_string(pos.x);
        y = std::to_string(pos.y);
        state.append("A_E2_");
        state.append(x);
        state.append("_");
        state.append(y);
        state.append("_");
        state.append(std::to_string(static_cast<int>(enemy_explosion)));
        state.append("&");
    }

    // bonuses_set;
    for (auto bonus : bonuses_set){         // A_B_x_y_type
        pos = bonus->getPos();
        x = std::to_string(pos.x);
        y = std::to_string(pos.y);
        bonusType typ = bonus->getBonusType();
        std::string res;
        if(typ == damageUp)  // [TODO]  pourquoi faire comme ca (-_-)
            res = "0";
        else if(typ == damageUp)
            res = "1";
        else if(typ == tripleShot)
            res = "2";
        else if (typ == lifeSteal)
            res = "3";
        else if(typ == minigun)
            res = "4";
        else if(typ == noBonus)
            res = "5";
        state.append("A_B_");
        state.append(x);
        state.append("_");
        state.append(y);
        state.append("_");
        state.append(std::to_string(static_cast<int>(bonus->getBonusType())));
        state.append("&");
    }
    //E_3_tick_levelTick_currentLevel
    if(changingLevel){
        state.append("A_L_");
        state.append(std::to_string(tick));
        state.append("_");
        state.append(std::to_string(levelTick));
        state.append("_");
        state.append(std::to_string(currentLevel));
        state.append("&");
    }


    return state;
}
