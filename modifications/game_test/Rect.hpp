#ifndef RECT_H
#define RECT_H

#include "InternGameObject.hpp"
#include <cstdint>

class rect {
    vec2i offset;
    vec2i bounds;
public:
    rect(vec2i o, vec2i b):offset(o),bounds(b){};
    rect()=default;

<<<<<<< HEAD
    uint_fast16_t top() { return offset.y; }
    uint_fast16_t bot() { return offset.y + bounds.y; }
    uint_fast16_t left() { return offset.x; }
    uint_fast16_t right() { return offset.x + bounds.x; }

    uint_fast16_t width() { return bounds.x; }
    uint_fast16_t height() { return bounds.y; }
=======
    int top() { return offset.y; }
    int bot() { return offset.y + bounds.y; }
    int left() { return offset.x; }
    int right() { return offset.x + bounds.x; }

    int width() { return bounds.x; }
    int height() { return bounds.y; }
>>>>>>> systeme

    bool contains(vec2i a) { return (a.x >= offset.x && a.x < right()) &&
                                    (a.y >= offset.y && a.y < bot()); }
    bool contains(rect r){
<<<<<<< HEAD
        for (uint_fast16_t i = left(); i < right(); ++i) {
            for (uint_fast16_t j = top(); j < bot(); ++j) {
=======
        for (int i = left(); i < right(); ++i) {
            for (int j = top(); j < bot(); ++j) {
>>>>>>> systeme
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