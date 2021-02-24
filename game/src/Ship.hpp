#ifndef SHIP_H
#define SHIP_H

class Ship: public MapObject{
    int damage;
    int fireRate;
    char disp_char;
    rect bounds;

public:
    Ship(){};
    char getChar() const{return disp_char;}
    void setChar(char c){disp_char=c;}
    void setBounds(rect b){bounds = b;}
    rect getBounds(){return bounds;}
    void setDammage(int dam){damage=dam;}
    int getDammage() const{return damage;}

};


#endif
