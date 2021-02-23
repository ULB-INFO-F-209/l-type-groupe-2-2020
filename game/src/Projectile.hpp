
#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "MapObject.hpp"


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
#endif



