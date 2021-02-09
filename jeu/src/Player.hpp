#ifndef PLAYER_HPP
#define PLAYER_HPP
#include"game.hpp"
#include"MapHandler.hpp"

class PlayerShip : public Ship{
    rect bounds;
    char disp_char;
    

    public:
    PlayerShip(int x, int y, rect b, char c, int h){pos.x = x; pos.y = y; bounds = b; setHp(h); disp_char = c;}
    void setBounds(rect b){bounds = b;}
    rect getBounds(){return bounds;}
    char getChar(){return disp_char;}
    };
    

class Player{
    int nLives, score;
    PlayerShip* ship;
    
};

#endif