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
#include <iostream>
//#include "settingServer.hpp"


enum bonusType{damageUp, tripleShot, lifeSteal, minigun, noBonus};
enum difficulty{easy, medium, hard};

class MapObject{
public:
    /*MapObject(){
        hp = 500;
    }*/
    virtual void move();
    virtual vec2i getPos() const;
    void setPos(int x, int y){pos.x = x; pos.y = y;}
    enum type{star,obstacle,playership,projectile,bonus,enemyship,boss};
    virtual void touched(int damage);
    virtual void setHp(int h){hp =h;}
    virtual int getHp(){return hp;}
    virtual ~MapObject(){};
    type typ;

protected:
    vec2i pos;
    int hp;
};

class Star: public MapObject{ //background
public:
    Star()=default;
    Star(int nx, int ny) { pos.x = nx; pos.y = ny;typ=star; }
};

class Obstacle: public MapObject{
    int damage;
public:
    Obstacle()=default;
    Obstacle(int nx, int ny,int dam,int h) {pos.x = nx; pos.y = ny; damage=dam;typ=obstacle;hp=h;}
    int get_damage() const {return damage;};
};

class Ship: public MapObject{
protected:
    int collisionDamage;
    int fireRate;
    char disp_char;
    rect bounds;
    int shootDamage;
    int projectileHp;


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
    ~Ship()=default;

};

class Projectile: public MapObject{
    int damage;
    bool shipType;
    int player;   // 0 = enemy; 1 = player1; 2 = player2
public:
    Projectile()=default;
    void move() override;
    Projectile(int nx, int ny,int dam,bool ship_t, int h, int p) {pos.x = nx; pos.y = ny; damage=dam; shipType=ship_t;typ=projectile; hp = h; player = p;}
    int getDamage() const{return damage;}
    bool getShipType() const{return shipType;}
    int getPlayer() const{return player;}
};

class Bonus: public MapObject{
    bonusType bonustype;
public:
    Bonus(){hp=20;};
    Bonus(int nx, int ny,bonusType bonus_t) :bonustype(bonus_t)  {pos.x = nx; pos.y = ny; hp=10;};
    bonusType const getBonusType() const {return bonustype;}
};

class PlayerShip : public Ship{
    int killTime;
    bool isAlive;
    int playerNb;
    int score;
    bonusType currentBonus;


public:
    PlayerShip()=default;
    PlayerShip(int x, int y, rect b, char c, int h, int nb, int dam, int s){pos.x = x; pos.y = y; bounds=b; hp=h; disp_char=c;isAlive=true; playerNb = nb; collisionDamage=dam; score = s;currentBonus=noBonus;shootDamage=10; projectileHp = 10;}
    int getKillTime() const{return killTime;}
    bool getIsAlive() const{return isAlive;}
    void setKillTime(int t){killTime=t;}
    void setisAlive(bool b){isAlive=b;}
    int getPlayerNb() const{return playerNb;}
    int getScore() const{return score;}
    void setScore(int s){score = s;}
    void catchBonus (const Bonus* b);
    bonusType getCurrentBonus(){return currentBonus;}
    void setCurrentBonus(bonusType b){currentBonus=b;}
    ~PlayerShip()=default;

};

class EnemyShip : public Ship{
    double bonusDropProb;
    int shootTime;
public:
    EnemyShip()=default;
    EnemyShip(int x, int y, rect b, char c,int h, int t, int shootDam){pos.x = x; pos.y = y; setBounds(b); setHp(h); setChar(c); setDammage(10); shootTime=t; shootDamage = shootDam; projectileHp = 10;}
    void setShootTime(int t){shootTime=t;}
    int getShootTime() const{return shootTime;}
};

class Boss : public Ship{
    int shootTime;
    bool movingRight;
public:
    Boss()= default;
    Boss(int x, int y, rect b, char c,int h, int t,int shootDam) {pos.x = x; pos.y = y; bounds=b; hp=h; disp_char=c; collisionDamage=100; shootTime = t;shootDamage = shootDam; projectileHp = 30; movingRight=true;}
    void move() override{
        if(movingRight)
            pos.x++;
        else pos.x--;
    }
    void setMovingRight(bool b){movingRight=b;}
    bool getMovingRight() const{return movingRight;}
    void setShootTime(int t){shootTime=t;}
    int getShootTime() const{return shootTime;}
};

class MapHandler{
    int probaBonus;
    int currentLevel = 1;
    int levelTick = 0;
    bool changingLevel = false;
    bool bossSpawned=false;
    int enemyCount = 0;
    int enemyLimit=5;
    int enemyStartHp = 30;
    int enemyStartProjectileDamage = 10;
    int obstacleStartHp = 10;
    int obstacleStartDamage = 10;
    difficulty dif;
    std::vector<Boss*> boss_set;
    std::vector<Star*> stars_set;
    std::vector<Obstacle*> obstacles_set;
    std::vector<Projectile*> projectiles_set;
    std::vector<Projectile*> projectilesEnemy_set;
    std::vector<PlayerShip*> player_ships_set;
    std::vector<EnemyShip*> enemy_ships_set;
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
    void update(MapObject::type, int);
    void erase(size_t, MapObject::type);
    std::vector<Star*> getStars() const;
    std::vector<Obstacle*> getObstacles() const;
    std::vector<Projectile*> getProjectiles() const;
    std::vector<Projectile*> getProjectilesEnemy() const;
    std::vector<EnemyShip*> getEnemy() const;
    std::vector<Bonus*> getBonus() const;
    std::vector<Boss*> getBoss() const;
    std::vector<PlayerShip*>  getListPlayer()const;

    std::vector<PlayerShip*> * getPlayerShipPointeur(){return &player_ships_set;}
    std::vector<Star*> *getStarsPointeur(){return &stars_set;} ;
    std::vector<Obstacle*> *getObstaclesPointeur(){return &obstacles_set;} ;
    std::vector<Projectile*>* getProjectilesPointeur(){return &projectiles_set;};
    std::vector<Projectile*> *getProjectilesEnemyPointeur() {return &projectilesEnemy_set;};
    std::vector<EnemyShip*> *getEnemyPointeur(){return &enemy_ships_set;} ;
    std::vector<Bonus*> *getBonusPointeur(){return &bonuses_set;} ;
    std::vector<Boss*> *getBossPointeur(){return &boss_set;} ;

    bool getBossSpawned() const{return bossSpawned;}
    void setBounds(rect);
    void spawnProjectile(int x, int y, int damage, bool type, int hp, int player);
    void checkCollision(int t, bool firendlyFire);
    rect field_bounds;
    void playerInit(PlayerShip* p1,PlayerShip* p2);
    void updateBounds();
    void enemyShoot(int tick);
    void bossShoot(int tick);
    void explosion();
    int spawnBonuses(int x, int y);
    void changeLevel();
    //void getSettings(settingServer2* obj);
    ~MapHandler()= default;
    void update_server(MapObject::type typ,int i,std::string *to_fill);
    void spawnProjectile_server(int x, int y, int damage, bool type, int hp, int player,std::string *to_fill);
    void bossShoot_server(int tick,std::string *to_fill);
    void enemyShoot_server(int tick,std::string *to_fill);
    void checkCollision_server(int t, bool friendlyFire,std::string * to_fill);
    void add_object_server(MapObject::type type,int i, std::string *to_fill);
    void spawnObstacle(int posx);
    void spawnEnemy(int posx,int tick);
    void spawnBoss(int tick);
    void spawnBonus_client(int x, int y,int rand_spawn_bonus);
    void update_client(MapObject::type typ, int t);
    void checkCollision_client(int t, bool friendlyFire) ;

};



#endif //JEU_MAPHANDLER_HPP