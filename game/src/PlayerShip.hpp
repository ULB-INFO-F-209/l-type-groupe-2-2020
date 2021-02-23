
#ifndef PLAYER_SHIP_H
#define PLAYER_SHIP_H


#include "Ship.hpp"

class rect;

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

