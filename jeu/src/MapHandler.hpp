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
    enum type{star,obstacle,ship,projectile,bonus};
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
    int hp;
    int damage;
    int fireRate;
public:
    Ship(){};
    Ship(int nx, int ny,int dam,int fire_r, int h) {pos.x = nx; pos.y = ny; damage=dam; fireRate=fire_r;typ=ship;hp = h;}
    void setHp(int h){hp = h;}
    int getHp(){return hp;}
};

class Projectile: public MapObject{
    int damage;
    bool shipType;
    //PlayerShip player;
public:
    void move() override;
    Projectile(int nx, int ny,int dam,bool ship_t) {pos.x = nx; pos.y = ny; damage=dam; shipType=ship_t;typ=projectile;}
};

class Bonus: public MapObject{
    int bonusType;
public:
    Bonus(int nx, int ny,int bonus_t) { pos.x = nx; pos.y = ny; bonusType=bonus_t;typ=bonus;}
};

class PlayerShip : public Ship{
    rect bounds;
    char disp_char;


public:
    PlayerShip(int x, int y, rect b, char c, int h){pos.x = x; pos.y = y; bounds = b; setHp(h); disp_char = c;}
    void setBounds(rect b){bounds = b;}
    rect getBounds(){return bounds;}
    char getChar(){return disp_char;}
    Player check;
};

class MapHandler{
public:
    void update(MapObject::type, int);
    void erase(size_t, MapObject::type);
    std::vector<Star*> getStars() const;
    std::vector<Obstacle*> getObstacles() const;
    std::vector<Projectile*> getProjectiles() const;
    void setBounds(rect);
    void spawnProjectile(int, int, int, bool );
    void checkCollision();
    rect field_bounds;
    void playerInit(PlayerShip* p1,PlayerShip* p2);
    void updatePlayerBounds();
    std::vector<PlayerShip*>  getListPlayer()const;
private:
    
    
    std::vector<Star*> stars_set;
    std::vector<Obstacle*> obstacles_set;
    std::vector<Projectile*> projectiles_set;
    std::vector<PlayerShip*> player_ships_set;
    
};
#endif //JEU_MAPHANDLER_HPP
