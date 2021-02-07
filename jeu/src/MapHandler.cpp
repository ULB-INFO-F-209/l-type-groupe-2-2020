//
// Created by ubuntu on 2/6/21.
//

#include "MapHandler.hpp"
void MapHandler::erase(size_t i, MapObject::type typ) { //1ier elem=index(0)
    object_set[typ].erase(object_set[typ].begin() + i);
}

std::vector<MapObject*> MapHandler::getData(MapObject::type typ) const  { return object_set[typ]; } // renvoyer le vect du map handler

void MapHandler::setBounds(rect a) { field_bounds = a; }

void MapObject::move() {pos.y += 1;}

vec2i MapObject::getPos() const {return pos;}

void MapHandler::update(MapObject::type typ, int t) {
    // update existing objects
    for(size_t i = 0; i < object_set[typ].size(); i++) {
        if(object_set[typ].at(i)->getPos().y > field_bounds.bot())
            object_set[typ].erase(object_set[typ].begin() + i);

        object_set[typ].at(i)->move();
    }

    // spawn a new object
    
    if(typ == MapObject::star)
        object_set[typ].push_back(new Stars(rand() % field_bounds.width(), 0));
    else if(typ == MapObject::obstacle && t % 10 == 0)
        object_set[typ].push_back(new Obstacle(rand() % field_bounds.width(), 0, 10));
}