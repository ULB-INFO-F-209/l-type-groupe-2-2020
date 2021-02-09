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

class MapObject{
public:
    void virtual move();
    vec2i getPos() const;
    void setPos(int x, int y){pos.x = x; pos.y = y;}
    enum type{star,obstacle,ship,projectile,bonus};
    type typ;

protected:
    vec2i pos;

};

class Star: public MapObject{ //background
public:
    Star(int nx, int ny) { pos.x = nx; pos.y = ny;typ=star; }
};

class Obstacle: public MapObject{
    int damage;
public:

    Obstacle(int nx, int ny,int dam) { pos.x = nx; pos.y = ny; damage=dam;typ=obstacle;}
    int get_damage() {return damage;};
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

class MapHandler{
public:
    void update(MapObject::type, int);
    void erase(size_t, MapObject::type);
    std::vector<Star*> getStars() const;
    std::vector<Obstacle*> getObstacles() const;
    std::vector<Projectile*> getProjectiles() const;
    void setBounds(rect);
    void spawnProjectile(int, int, int, bool );
    
    rect field_bounds;
private:
    
    
    std::vector<Star*> stars_set;
    std::vector<Obstacle*> obstacles_set;
    std::vector<Projectile*> projectiles_set;
    
};
#endif //JEU_MAPHANDLER_HPP
