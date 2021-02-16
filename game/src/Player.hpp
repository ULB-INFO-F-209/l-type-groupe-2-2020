#ifndef PLAYER_HPP
#define PLAYER_HPP
#include"game.hpp"
#include"MapHandler.hpp"
class PlayerShip;

class Player{
    int nLives, score;
    
    public:
    int getnLives(){return nLives;}
    void setnLives(int lives){nLives = lives;}
    Player( int lives, int s){nLives = lives, score = s;}
};

#endif