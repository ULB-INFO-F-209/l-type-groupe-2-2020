//
// Created by ubuntu on 2/6/21.
//

#ifndef JEU_MAPHANDLER_HPP
#define JEU_MAPHANDLER_HPP
#include "game.hpp"
#include <cstdlib>
#include <vector>

class MapObject{
public:
    MapObject(int,int);
    void update();
    vec2i getPos() const;
    void setPos(vec2i);

private:
    vec2i pos;
};

class MapHandler{
public:
    void update();
    void erase(size_t);
    std::vector<MapObject> getData() const;

    void setBounds(rect);

private:
    rect field_bounds;
    std::vector<MapObject> object_set;
};
#endif //JEU_MAPHANDLER_HPP
