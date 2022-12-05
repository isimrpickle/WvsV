#pragma once


#include <list>
#include <vector>
using namespace std;

typedef enum {
    WEREWOLF, VAMPIRE, AVATAR, TREE, WATER, EARTH
} GraphicType;


class graphics {
    static unsigned num_of_graphics;
    const unsigned short int x;
    const unsigned short int y;
    const GraphicType type;
public:
    graphics(unsigned short int x_, unsigned short int y_, GraphicType type_) :x(x_), y(y_), type(type_) {
        num_of_graphics++;
    };
    static unsigned get_num_of_graphics() { return num_of_graphics; };
    const unsigned short int get_y() { return y; };
    const unsigned short int get_x() { return x; };
};


void printing_map(unsigned short int x, unsigned short int y);


void map_create();
