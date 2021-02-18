//
// Created by ubuntu on 2/6/21.
//

#ifndef JEU_MAPHANDLER_HPP
#define JEU_MAPHANDLER_HPP
#include "game.hpp"
#include <cstdlib>
#include <vector>
#include <cstdint>
#include <list>
#include "Player.hpp"

class MapObject{
public:
    virtual void move();
    vec2i getPos() const;
    void setPos(int x, int y){pos.x = x; pos.y = y;}
    enum type{star,obstacle,playership,projectile,bonus,enemyship};
    virtual void touched(int damage);
    type typ;

    virtual void setHp(int h){hp =h;}

    virtual int getHp(){return hp;}

protected:
    vec2i pos;
    int hp;
};

class Star: public MapObject{ //background
public:
    Star(int nx, int ny) { pos.x = nx; pos.y = ny;typ=star; }
};

class Obstacle: public MapObject{
    int damage;
public:

    Obstacle(int nx, int ny,int dam,int h) {pos.x = nx; pos.y = ny; damage=dam;typ=obstacle;hp=h;}
    int get_damage() {return damage;};
    void touched(int damage);
};

class Ship: public MapObject{
    int damage;
    int fireRate;
    char disp_char;
    rect bounds;

public:
    Ship(){};
    char getChar(){return disp_char;}
    void setChar(char c){disp_char=c;}
    void setBounds(rect b){bounds = b;}
    rect getBounds(){return bounds;}
    void setDammage(int dam){damage=dam;}
    int getDammage(){return damage;}

};

class Projectile: public MapObject{
    int damage;
    bool shipType;
    int player;   // 0 = enemy; 1 = player1; 2 = player2
public:
    void move() override;
    Projectile(int nx, int ny,int dam,bool ship_t, int h, int p) {pos.x = nx; pos.y = ny; damage=dam; shipType=ship_t;typ=projectile; hp = h; player = p;}
    int getDamage(){return damage;}
    bool getShipType(){return shipType;}
    int getPlayer(){return player;}
};

class Bonus: public MapObject{
    int bonusType;
public:
    Bonus(int nx, int ny,int bonus_t) { pos.x = nx; pos.y = ny; bonusType=bonus_t;typ=bonus;}
};

class PlayerShip : public Ship{
    int killTime;
    bool isAlive;
    int playerNb;
    int score;

public:
    PlayerShip(int x, int y, rect b, char c, int h, int nb, int dam, int s){pos.x = x; pos.y = y; setBounds(b); setHp(h); setChar(c);isAlive=true; playerNb = nb; setDammage(dam); score = s;}
    int getKillTime(){return killTime;}
    bool getIsAlive(){return isAlive;}
    void setKillTime(int t){killTime=t;}
    void setisAlive(bool b){isAlive=b;}
    int getPlayerNb(){return playerNb;}
    int getScore(){return score;}
    void setScore(int s){score = s;}
    
};

class EnemyShip : public Ship{
    double bonusDropProb;
    int shootTime;
public:
    EnemyShip(int x, int y, rect b, char c,int h,int dam, int t){pos.x = x; pos.y = y; setBounds(b); setHp(h); setChar(c); setDammage(dam);shootTime=t;}
    void setShootTime(int t){shootTime=t;}
    int getShootTime(){return shootTime;}
};

class MapHandler{
public:
    void update(MapObject::type, int);
    void erase(size_t, MapObject::type);
    std::vector<Star*> getStars() const;
    std::vector<Obstacle*> getObstacles() const;
    std::vector<Projectile*> getProjectiles() const;
    std::vector<EnemyShip*> getEnemy() const;
    void setBounds(rect);
    void spawnProjectile(int, int, int, bool, int, int);
    void checkCollision();
    rect field_bounds;
    void playerInit(PlayerShip* p1,PlayerShip* p2);
    void updatePlayerBounds();
    std::vector<PlayerShip*>  getListPlayer()const;
    void enemyShoot(int tick);
private:

    std::vector<Star*> stars_set;
    std::vector<Obstacle*> obstacles_set;
    std::vector<Projectile*> projectiles_set;
    std::vector<PlayerShip*> player_ships_set;
    std::vector<EnemyShip*> enemy_ships_set;


};
#endif //JEU_MAPHANDLER_HPP
