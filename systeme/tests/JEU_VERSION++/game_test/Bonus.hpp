
#ifndef BONUS_H
#define BONUS_H

#include "MapHandler.hpp"



class Bonus: public MapObject{
    bonusType bonustype;
public:
    Bonus(){this->hp=20;};
    Bonus(int nx, int ny,bonusType bonus_t) :MapObject(),bonustype(bonus_t)  {this->pos.x = nx; this->pos.y = ny; this->hp=10;};
    bonusType const getBonusType() const {return bonustype;}
};

#endif