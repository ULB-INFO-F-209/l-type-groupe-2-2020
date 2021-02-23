#ifndef PLAYER_HPP
#define PLAYER_HPP
//#include"game.hpp"
//class PlayerShip;

class Player{
    int nLives;

public:
    int getnLives(){return nLives;}
    void setnLives(int lives){nLives = lives;}
    Player( int lives){nLives = lives;}
};

#endif