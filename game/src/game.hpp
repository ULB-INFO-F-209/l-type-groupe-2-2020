#ifndef GAME_H
#define GAME_H
#include <cstdint>


// at least 16-bit int 2D vector
typedef struct {
    uint_fast16_t x;
    uint_fast16_t y;
} vec2i;


// simple integer rectangle type
struct rect {
    vec2i offset;
    vec2i bounds;

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


struct enemy{
    vec2i pos;
};

struct star {
    vec2i pos;
};
int init();
void run();
void close();
void drawEnergyBar(int);

#endif
