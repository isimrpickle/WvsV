
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
    unsigned short int x;
    unsigned short int y;
    GraphicType type;
public:
    graphics();
    graphics(unsigned short int x_, int y_, GraphicType type_ = EARTH);

    //fuction that returna value for the movement of the graphic
    virtual int move(); 

    //functions that sets and return the Graphictype of the graphic
    void set_type(GraphicType type_);
    GraphicType get_type();

    //functions that sets the position of the graphic
    void set_x(unsigned short int i);
    void set_y(unsigned short int i);

    //functions that return the x,y position
    unsigned short int get_y();
    unsigned short int get_x();

    //GraphicType get_id(graphics example);

    // functions that returns the stats of a graphic
    virtual int getpower()const;
    virtual int getdefense()const;
    virtual int gethealth()const;
    virtual int get_potions();

    //functions that change the hp of vampires and werewolves
    virtual void health_decrease(int);
    virtual void health_increase(int);
   
};



class vampires : public graphics {
    unsigned short int health;
    unsigned short int power;
    unsigned short int defense;
    unsigned short int potions;

public:
    vampires();
    int move();
    // everyone gains back full hp after avatar uses the potion
    void health_regain();

    //functions that set and return characters's stats
    void set_power(int i);
    void set_defense(int i);
    int getpower() const;
    int getdefense()const;
    int gethealth()const;
    int get_potions()const;

   // void printstats()const;

    void health_decrease(int);
    void health_increase(int);
   

};



class werewolves : public graphics {
    unsigned short int  power,defense, health, potions;
public:
    werewolves();
    void health_regain();
    void set_power(int i);
    int getpower() const;
    void set_defense(int i);
    int getdefense()const;
    int gethealth()const;
    int get_potions()const;
    //void printstats_w()const;
    void health_decrease(int);
    void health_increase(int);

};




class avatars : public graphics {
    int potions;
    char A;
public:
    avatars();

    //function that return the team of the avatar
    char get_team();

    void set_potions(int i);

    //function that changes the char or "team" of the avatr
    void set_char(char a);

    // the user moves the avatar
    int input(int i);
};
