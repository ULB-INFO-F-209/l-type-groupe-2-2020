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

    uint_fast16_t top() const { return offset.y; }
    uint_fast16_t bot() const { return offset.y + bounds.y; }
    uint_fast16_t left() const { return offset.x; }
    uint_fast16_t right() const { return offset.x + bounds.x; }

    uint_fast16_t width() const { return bounds.x; }
    uint_fast16_t height() const { return bounds.y; }

    bool contains(vec2i a) const { return (a.x >= offset.x && a.x < right()) &&
                                    (a.y >= offset.y && a.y < bot()); }
    bool contains(rect r) const{
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

int init();
void run();
void close();
void drawEnergyBar(int);

#endif
