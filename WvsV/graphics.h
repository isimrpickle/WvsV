#pragma once


#include <list>
#include <stdlib.h>
//#include "game_state.h"
#include <cstdlib>
#include <iostream>


using namespace std;

typedef enum {
    WEREWOLF, VAMPIRE, AVATAR, TREE, WATER, EARTH
} GraphicType;


class graphics {
    //static unsigned num_ofgraphics;
    unsigned short int x;
    unsigned short int y;
    GraphicType type;
public:
    graphics() {
        this->x = 0;
        this->y = 0;
        this->type = EARTH;
    }
    graphics(unsigned short int x_, int y_, GraphicType type_ = EARTH) {
        this->x = x_;
        this->y = y_;
        this->type = type_;
    };
    virtual void move();
    void set_x(unsigned short int i) { this->x = i; };
    void set_y(unsigned short int i) { this->y = i; };
    //static unsigned get_num_of_graphics() { return num_of_graphics; };
    unsigned short int get_y() { return y; };
    unsigned short int get_x() { return x; };
    GraphicType get_id(graphics example) { return example.type; };
    void update_charactes(graphics example, unsigned short int map_x, unsigned short int mapy);
};



class vampires : public graphics {
    unsigned short int power, defense, health;
public:
    vampires() {
        this->power = rand() % 4;
        this->defense = rand() % 3;
        this->health = 10;
    };
    void move();
    int getpower() const { return this->power; }
    int getdefense()const { return this->defense; }
    int gethealth()const { return this->health; }
    void printstats()const;
};



class werewolves : public graphics {
    unsigned short int power, defense, health;
public:
    werewolves() {
        this->power = rand() % 4;
        this->defense = rand() % 3;
        this->health = 10;
    };
    int getpower() const { return this->power; }
    int getdefense()const { return this->defense; }
    int gethealth()const { return this->health; }
    void printstats_w()const;
};

class avatars : public graphics {
    int potions;
public:
    avatars() {
        potions = rand() % 2;
    }

};
