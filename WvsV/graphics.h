#pragma once


#include <list>
#include <stdlib.h>

using namespace std;

typedef enum {
    WEREWOLF, VAMPIRE, AVATAR, TREE, WATER, EARTH
} GraphicType;


class graphics {
    //static unsigned num_of_graphics;
     unsigned short int x;
     unsigned short int y;
    const GraphicType type;
public:
    graphics(unsigned short int x_, unsigned short int y_, GraphicType type_) :x(x_), y(y_), type(type_) {
        // num_of_graphics++;
    };
    void set_x(unsigned short int i) { this->x = i; };
    void set_y(unsigned short int i) { this->y = i; };
    //static unsigned get_num_of_graphics() { return num_of_graphics; };
    const unsigned short int get_y() { return y; };
    const unsigned short int get_x() { return x; };
    GraphicType get_id(graphics example) { return example.type; };
    void update_charactes(graphics example, unsigned short int map_x, unsigned short int map_y);
};


