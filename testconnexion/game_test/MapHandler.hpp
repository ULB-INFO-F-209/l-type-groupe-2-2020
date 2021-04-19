//
// Created by ubuntu on 2/6/21.
//

#ifndef JEU_MAPHANDLER_HPP
#define JEU_MAPHANDLER_HPP
#include <cstdlib>
#include <vector>
#include <cstdint>
#include "Player.hpp"
#include "InternGameObject.hpp"
#include "Rect.hpp"
#include "Template.hpp"
#include <iostream>

using namespace Template;
enum bonusType{damageUp, tripleShot, lifeSteal, minigun,noBonus};


class MapObject{
/**
 * Tous les objets sur la map  
 * 
*/
public:
    virtual void move();
    virtual vec2i getPos() const;
    void setPos(uint_fast16_t x, uint_fast16_t y){pos.x = x; pos.y = y;}
    enum type{star,obstacle,playership,projectile,bonus,enemyship,enemyship2,boss};
    virtual void touched(int damage);
    virtual void setHp(int h){hp =h;}
    virtual int getHp(){return hp;}
    virtual ~MapObject(){};
    type typ=star;

protected:
    vec2i pos{}; // (x, y)
    int hp=0;
};

class Star final : public MapObject{ //background
public:
    Star()=default;
    Star(uint_fast16_t nx, uint_fast16_t ny) { pos.x = nx; pos.y = ny;typ=star;}
    ~Star(){};
};

class Obstacle final: public MapObject{
    int damage=0;
public:
    Obstacle()=default;
    Obstacle(uint_fast16_t nx, uint_fast16_t ny,int dam,int h) {pos.x = nx; pos.y = ny; damage=dam;typ=obstacle;hp=h;}
    int get_damage() const {return damage;};
    ~Obstacle(){};
};

class Ship: public MapObject{
protected:
    int collisionDamage=0; // dégats causés par une collision
    char disp_char{}; // caractère représentant le Ship
    rect bounds{}; // dimension du ship (rectangle)
    int shootDamage=0; // dégats causés par le projectile envoyé
    int projectileHp=0; // vie du projectile


public:
    Ship(){};
    char getChar() const{return disp_char;}
    void setChar(char c){disp_char=c;}
    void setBounds(rect b){bounds = b;}
    rect getBounds(){return bounds;}
    void setDammage(int dam){collisionDamage=dam;} //change name
    int getDammage() const{return collisionDamage;}   //change name
    void setShootDamage(int s_dam){shootDamage=s_dam;}
    int getShootDamage() const{return shootDamage;}
    void setProjectileHp(int p_hp){projectileHp = p_hp;}
    int getProjectileHp() const{return projectileHp;}
    virtual ~Ship()=default;

};

class Projectile final: public MapObject{
    int damage{};
    bool shipType{}; // enlever TODO
    int player{};   // 0 = enemy; 1 = player1; 2 = player2
public:
    Projectile()=default;
    void move() override;
    Projectile(int nx, int ny,int dam,bool ship_t, int h, int p) {pos.x = static_cast<uint_fast16_t>(nx); pos.y = static_cast<uint_fast16_t>(ny); damage=dam; shipType=ship_t;typ=projectile; hp = h; player = p;}
    int getDamage() const{return damage;}
    bool getShipType() const{return shipType;}
    int getPlayer() const{return player;}
    ~Projectile(){};
};

class Bonus final: public MapObject{
    bonusType bonustype{};
public:
    Bonus(){hp=20;};
    Bonus(int nx, int ny,bonusType bonus_t) :bonustype(bonus_t)  {pos.x = static_cast<uint_fast16_t>(nx); pos.y = static_cast<uint_fast16_t>(ny); hp=10;};
    bonusType getBonusType() const {return bonustype;}
    ~Bonus(){};

};

class PlayerShip final: public Ship{
    int killTime{}; // sauvegarde du moment où Playership est mort (pour faire clignoter)
    bool isAlive{};  
    int playerNb{}; // 0, 1
    int score{};
    bonusType currentBonus{};


public:
    PlayerShip()=default;
    PlayerShip(uint_fast16_t x, uint_fast16_t y, rect b, char c, int h, int nb, int dam, int s){pos.x = x; pos.y = y; bounds=b; hp=h; disp_char=c;isAlive=true; playerNb = nb; collisionDamage=dam; score = s;currentBonus=noBonus;shootDamage=10; projectileHp = 10;}
    int getKillTime() const{return killTime;}
    bool getIsAlive() const{return isAlive;}
    void setKillTime(int t){killTime=t;}
    void setisAlive(bool b){isAlive=b;}
    int getPlayerNb() const{return playerNb;}
    int getScore() const{return score;}
    void setScore(int s){score = s;}
    void catchBonus (const Bonus* b); // mise à jour de currentBonus (lors d'une collision avec un bonus)
    bonusType getCurrentBonus(){return currentBonus;}
    void setCurrentBonus(bonusType b){currentBonus=b;}
    ~PlayerShip()=default;

};

class EnemyShip : public Ship{
protected:
    int shootTime{};
    bonusType bonus{};
public:
    EnemyShip()=default;
    EnemyShip(uint_fast16_t x, uint_fast16_t y, rect b, char c,int h, int t, int shootDam, bonusType bon=noBonus){pos.x = x; pos.y = y; setBounds(b); setHp(h); setChar(c); setDammage(10); shootTime=t; shootDamage = shootDam; projectileHp = 10; bonus=bon;}
    void setShootTime(int t){shootTime=t;}
    int getShootTime() const{return shootTime;}
    bonusType getBonusType() const{return bonus;}
    ~EnemyShip(){};
};

class EnemyShip2 : public EnemyShip{
    public:
    EnemyShip2()=default;
    EnemyShip2(uint_fast16_t x, uint_fast16_t y, rect b, char c,int h, int t, int shootDam, bonusType bon=noBonus){pos.x = x; pos.y = y; setBounds(b); setHp(h); setChar(c); setDammage(10); shootTime=t; shootDamage = shootDam; projectileHp = 10; bonus=bon;}
    void move() override {pos.x += 1;}
};



class Boss : public Ship{
    int shootTime{};
    bool movingRight{};
    int bossType{};
public:
    Boss()= default;
    Boss(uint_fast16_t x, uint_fast16_t y, rect b, char c,int h, int t,int shootDam, int typ) {pos.x = x; pos.y = y; bounds=b; hp=h; disp_char=c; collisionDamage=100; shootTime = t;shootDamage = shootDam; bossType = typ; projectileHp = 30; movingRight=true;}
    void move() override{
        if(movingRight)
            pos.x++;
        else pos.x--;
    }
    void setMovingRight(bool b){movingRight=b;}
    bool getMovingRight() const{return movingRight;}
    void setShootTime(int t){shootTime=t;}
    int getShootTime() const{return shootTime;}
    int getBossType() const{return bossType;}
    ~Boss(){};

};

class MapHandler final{
    /**
     * MapHandler va s'occuper de tous les objets de la map ainsi que leurs interactions (création, collision, destruction)
     *  
    **/
    int probaBonus{}; // probabilité qu'un bonus apparaissent 
    int currentLevel = 1;
    int levelTick = 0; // sauvegarde du moment où on change de niveau
    bool changingLevel = false;
    bool bossSpawned = false;

    int enemyCount = 0;
    int enemyLimit=10; //nombre d'ennemis max par niveau
    int enemyStartHp = 30;
    int enemyStartProjectileDamage = 10;
    int obstacleStartHp = 10;
    int obstacleStartDamage = 10;
    bool customGame = false;
    difficulty dif{};
    int customMultiplier = 0;

    // Vecteur d'objets de la map
    std::vector<Boss*> boss_set;
    std::vector<Star*> stars_set;
    std::vector<Obstacle*> obstacles_set;
    std::vector<Projectile*> projectiles_set;
    std::vector<Projectile*> projectilesEnemy_set;
    std::vector<PlayerShip*> player_ships_set;
    std::vector<EnemyShip*> enemy_ships_set;
    std::vector<EnemyShip2*> enemy_ships2_set;
    std::vector<Bonus*> bonuses_set;
    
public:
    MapHandler()=default;
    MapHandler(int p,difficulty d);
    int getCurrentLevel() const{return currentLevel;}
    void setCurrentLevel(int l){currentLevel = l;}
    int getLevelTick() const{return levelTick;}
    void setLevelTick(int t){levelTick = t;}
    bool getChangingLevel() const{return changingLevel;}
    void setChangingLevel(bool c){changingLevel = c;}
    void setCustomGame(bool c){customGame = c;}
    bool getCustomGame() const{return customGame;}
    void erase(size_t, MapObject::type);
    std::vector<Star*> getStars() const;
    std::vector<Obstacle*> getObstacles() const;
    std::vector<Projectile*> getProjectiles() const;
    std::vector<Projectile*> getProjectilesEnemy() const;
    std::vector<EnemyShip*> getEnemy() const;
    std::vector<EnemyShip2*> getEnemy2() const;
    std::vector<Bonus*> getBonus() const;
    std::vector<Boss*> getBoss() const;
    std::vector<PlayerShip*>  getListPlayer()const;

    bool getBossSpawned() const{return bossSpawned;}
    void setBossSpawned(bool b){bossSpawned=b;}
    int getEnemyCount() const{return enemyCount;}
    void setBounds(rect);
    void spawnProjectile(int x, int y, int damage, bool type, int hp, int player);
    rect field_bounds;
    void playerInit(PlayerShip* p1,PlayerShip* p2); // insertion des playership dans le vecteur
    void updateBounds(); // mise à jour de l'emplacement du rectangle du ship
    void explosion(); // lorsque Playership meurt, tous les ennemyShips perdent des HP
    int spawnBonuses(int x, int y);
    int spawnBonuses(int x, int y, bonusType bonus);
    void changeLevel(); // changement des paramètres en fonction du niveau
    void update_server(MapObject::type typ,int i);
    void bossShoot_server(int tick);
    void enemyShoot_server(int tick); // tire automatique des ennemis
    void checkCollision_server(int t, bool friendlyFire);
    void add_object_server(MapObject::type type,int i);
    void add_object_server(MapObject::type typ,int t,std::vector<Enemy_template> *enemy_list,std::vector<Obstacle_template> *obs_list);
    void spawnObstacle(int posx);
    void spawnEnemy(int posx,int tick);
    void spawnBoss(int tick);
    std::string getState(int nlives_j1,int nlives_j2,int tick); // pour le server
    ~MapHandler()= default;
};



#endif //JEU_MAPHANDLER_HPP
