#ifndef PLAYER_HPP
#define PLAYER_HPP


class Player{
    int nLives = 0; //lives of a player

public:
    Player()=default;
    Player( int lives){nLives = lives;}
    int getnLives(){return nLives;}
    void setnLives(int lives){nLives = lives;}
    
};

#endif