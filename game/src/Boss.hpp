//
// Created by jean on 24/02/2021.
//
#ifndef JEU_BOSS_HPP
#define JEU_BOSS_HPP
#include "MapHandler.hpp"

class Boss : public Ship{
    int shootTime{};
    bool movingRight;
public:
    Boss()= default;
    Boss(int x, int y, rect b, char c,int h, int t, int shootDam){pos.x = x; pos.y = y; bounds=b; hp=h; disp_char=c; collisionDamage=100;shootTime=t; shootDamage = shootDam; projectileHp = 30;}
    void move() override;
};




#endif //JEU_BOSS_HPP
