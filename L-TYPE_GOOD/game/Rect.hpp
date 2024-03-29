#ifndef RECT_H
#define RECT_H

#include "InternGameObject.hpp"
#include <cstdint>

class rect {
    //représente la taille et la position d'un rectangle
    vec2i offset;
    vec2i bounds;
public:
    rect(vec2i o, vec2i b):offset(o),bounds(b){};
    rect()=default;

    uint_fast16_t top() { return offset.y; }
    uint_fast16_t bot() { return offset.y + bounds.y; }
    uint_fast16_t left() { return offset.x; }
    uint_fast16_t right() { return offset.x + bounds.x; }

    uint_fast16_t width() { return bounds.x; }
    uint_fast16_t height() { return bounds.y; }

    bool contains(vec2i a) { return (a.x >= offset.x && a.x < right()) &&
                                    (a.y >= offset.y && a.y < bot()); }
    bool contains(rect r){
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