//
// Created by ubuntu on 2/6/21.
//

#include "MapHandler.hpp"
void MapHandler::erase(size_t i) { //1ier elem=index(0)
    object_set.erase(object_set.begin() + i);
}

std::vector<MapObject*> MapHandler::getData() const  { return object_set; } // renvoyer le vect du map handler

void MapHandler::setBounds(rect a) { field_bounds = a; }

void MapObject::move() {pos.y += 1;}

vec2i MapObject::getPos() const {return pos;}

void MapHandler::update() {
    // update existing objects
    for(size_t i = 0; i < object_set.size(); i++) {
        if(object_set.at(i)->getPos().y > field_bounds.bot())
            object_set.erase(object_set.begin() + i);

        object_set.at(i)->move();
    }

    // spawn a new object

    object_set.push_back(new Stars(rand() % field_bounds.width(), 0));
}