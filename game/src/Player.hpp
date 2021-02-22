#ifndef PLAYER_HPP
#define PLAYER_HPP
//#include"game.hpp"
//class PlayerShip;

class Player{
    int nLives;
    
    public:
    int getnLives() const{return nLives;}
    void setnLives(int lives){nLives = lives;}
    explicit Player( int lives){nLives = lives;}
};

#endif