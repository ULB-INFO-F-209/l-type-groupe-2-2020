#ifndef RECT_H
#define RECT_H

#include "InternGameObject.hpp"
#include <cstdint>

class rect {
    //class representing a rectangle
    vec2i offset; //position
    vec2i bounds; //size
public:

    rect(vec2i o, vec2i b):offset(o),bounds(b){};
    rect()=default;

    //getters
    uint_fast16_t top() { return offset.y; }
    uint_fast16_t bot() { return offset.y + bounds.y; }
    uint_fast16_t left() { return offset.x; }
    uint_fast16_t right() { return offset.x + bounds.x; }

    uint_fast16_t width() { return bounds.x; }
    uint_fast16_t height() { return bounds.y; }

    bool contains(vec2i a) {
        //check if the position a is in this rectangle
        return (a.x >= offset.x && a.x < right()) && (a.y >= offset.y && a.y < bot()); 
        }
    bool contains(rect r){
        //check if a point of the rectangle r is in this rectangle
        for (uint_fast16_t i = left(); i < right(); ++i) {
            for (uint_fast16_t j = top(); j < bot(); ++j) {
                vec2i test;
                test.x=i;
                test.y=j;
                if (r.contains(test))
                    return true;
            }
        }
        return false;
    }
};


#endif // RECT_H