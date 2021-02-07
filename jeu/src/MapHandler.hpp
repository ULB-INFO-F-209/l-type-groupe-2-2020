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
    void move();
    vec2i getPos() const;
    void setPos(vec2i);
    enum type{star,obstacle,ship,projectile,bonus};
    type typ;

protected:
    vec2i pos;

};

class Stars: public MapObject{ //background
public:
    Stars(int nx, int ny) { pos.x = nx; pos.y = ny;typ=star; }
};

class Obstacle: public MapObject{
    int damage;
public:

    Obstacle(int nx, int ny,int dam) { pos.x = nx; pos.y = ny; damage=dam;typ=obstacle;}

};

class Ship: public MapObject{
    int damage;
    int fireRate;
public:
    Ship(int nx, int ny,int dam,int fire_r) {pos.x = nx; pos.y = ny; damage=dam; fireRate=fire_r;typ=ship;}
};

class Projectile: public MapObject{
    int damage;
    bool shipType;
    //PlayerShip player;
public:
    Projectile(int nx, int ny,int dam,bool ship_t) {pos.x = nx; pos.y = ny; damage=dam; shipType=ship_t;typ=projectile;}
};

class Bonus: public MapObject{
    int bonusType;
public:
    Bonus(int nx, int ny,int bonus_t) { pos.x = nx; pos.y = ny; bonusType=bonus_t;typ=bonus; }
};

class MapHandler{
public:
    void update(MapObject::type, int);
    void erase(size_t, MapObject::type);
    std::vector<MapObject*> getData(MapObject::type) const;

    void setBounds(rect);

private:
    rect field_bounds;
    
    std::vector<MapObject*> stars_set;
    std::vector<MapObject*> asteroids_set;
    std::vector<MapObject*> object_set[2] = {stars_set, asteroids_set};
     
    
};
#endif //JEU_MAPHANDLER_HPP
