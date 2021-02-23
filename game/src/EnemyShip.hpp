#ifndef ENEMY_SHIP_H
#define ENEMY_SHIP_H



class EnemyShip : public Ship{
    double bonusDropProb;
    int shootTime;
public:
    EnemyShip(int x, int y, rect b, char c,int h,int dam, int t){pos.x = x; pos.y = y; setBounds(b); setHp(h); setChar(c); setDammage(dam);shootTime=t;}
    void setShootTime(int t){shootTime=t;}
    int getShootTime(){return shootTime;}
};
