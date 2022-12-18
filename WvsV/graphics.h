
#pragma once


#include <list>
#include <stdlib.h>
//#include "game_state.h"
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>


using namespace std;

typedef enum {
    WEREWOLF, VAMPIRE, AVATAR, TREE, WATER, EARTH, POTION
} GraphicType;



class graphics {
    //static unsigned num_ofgraphics;
    unsigned short int x;
    unsigned short int y;
    GraphicType type;
    //unsigned short int power, defense, health, potions;
public:
    graphics() {
        this->x = 0;
        this->y = 0;
        this->type = EARTH;
     //   this->power = 0;
    }
    graphics(unsigned short int x_, int y_, GraphicType type_ = EARTH, unsigned short int p = rand() % 4 + 1) {
        this->x = x_;
        this->y = y_;
        this->type = type_;
     //   this->power = p;
    };
    virtual int move();
    void set_type(GraphicType type_) { this->type = type_; };
    GraphicType get_type() { return this->type; };
    void set_x(unsigned short int i) { this->x = i; };
    void set_y(unsigned short int i) { this->y = i; };
    //static unsigned get_num_of_graphics() { return num_of_graphics; };
    unsigned short int get_y() { return y; };
    unsigned short int get_x() { return x; };
    GraphicType get_id(graphics example) { return example.type; };
    virtual int getpower()const { return NULL; }
    virtual int getdefense()const { return NULL; }
    virtual int gethealth()const { return NULL; }
    virtual void health_decrease(int);
    virtual void health_increase(int);
    virtual int get_potions() { return NULL; }
  //  virtual void set_power(int i) { this->power = i; };
    //void update_charactes(graphics example, unsigned short int map_x, unsigned short int mapy);
};



class vampires : public graphics {
    unsigned short int health;

    unsigned short int power;
    unsigned short int defense;
    unsigned short int potions;

public:
    vampires() {
        srand((unsigned)time(0));
        this->power = rand() % 4 + 1;
        this->defense = rand() % 3;
        this->health = 10;
        this->potions = rand() % 2;
    };
    int move();
    void health_regain() { health = 10; };
     void set_power(int i) { this->power = i; }
     void set_defense(int i) { this->defense = i; }
     int getpower() const { return this->power; }
     int getdefense()const { return defense; }
     int gethealth()const { return this->health; }
     void printstats()const;
     void health_decrease(int);
     int get_potions()const { return this->potions; }
     void health_increase(int);

};



class werewolves : public graphics {
    unsigned short int  power,defense, health, potions;
public:
    werewolves() {
        srand((unsigned)time(0));
        this->power = rand() % 4;
        this->defense = rand() % 3;
        this->health = 10;
        this->potions = rand() % 2;
    };
    void health_regain() { health = 10; };
    void set_power(int i) { this->power = i; }
    int getpower() const { return this->power; }
    void set_defense(int i) { this->defense = i; }
    int getdefense()const { return this->defense; }
    int gethealth()const { return this->health; }
    int get_potions()const { return this->potions; }
    void printstats_w()const;
    void health_decrease(int);
    void health_increase(int);
};




class avatars : public graphics {
    int potions;
    char A;
public:
    avatars() {
        potions = rand() % 2;
        A = 'b';
    }
    char get_team() { return A; };
    void set_potions(int i) { potions = i; };
    void set_char(char a) { A = a; };
    int input(int i); // the user moves the avatar
};
