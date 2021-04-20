#ifndef PLAYER_HPP
#define PLAYER_HPP
//#include"game.hpp"
//class PlayerShip;

class Player{
    int nLives;

public:
    Player()=default;
<<<<<<< HEAD
    int getnLives(){return nLives;}
    void setnLives(int lives){nLives = lives;}
    Player( int lives){nLives = lives;}
=======
    int getnLives()const {return nLives;}
    void decLives(){nLives--;};
    void setnLives(int lives){nLives = lives;}
    Player( int lives):nLives(lives){}
>>>>>>> systeme
};

#endif