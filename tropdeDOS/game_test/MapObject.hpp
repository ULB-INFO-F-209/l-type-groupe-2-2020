
#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

#include "InternGameObject.hpp"
#include "Rect.hpp"


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

#endif