#include <iostream>
#include"graphics.h"
#include <cstdlib> // in order to use srand and rand 
#include<windows.h>
#include"game_state.h"

using namespace std;


graphics::graphics() {
    this->x = 0;
    this->y = 0;
    this->type = EARTH;
};
graphics::graphics(unsigned short int x_, int y_, GraphicType type_ ) {
    this->x = x_;
    this->y = y_;
    this->type = type_;
};
void graphics::set_type(GraphicType type_) { 
    this->type = type_; 
};
GraphicType graphics::get_type() { 
    return this->type;
};
void graphics::set_x(unsigned short int i) {
    this->x = i; 
};
void graphics::set_y(unsigned short int i) { 
    this->y = i; 
};
unsigned short int graphics::get_y() { 
    return y; 
};
unsigned short int graphics::get_x() {
    return x; 
};
GraphicType graphics::get_id(graphics example) { 
    return example.type; 
};
int graphics::getpower()const { 
    return NULL; 
}
int graphics::getdefense()const { 
    return NULL; 
}
int graphics::gethealth()const { 
    return NULL; 
}
int graphics::get_potions() { 
    return NULL; 
}

int graphics::move() {
    switch (1 + rand() % 4) {  // οι περιπτωσεις να μετακινηθει προς οποιαδήποτε κατευθυνση είναι ισοπίθανη
    case 1:
        return 1; // x++, goes one place down
        break;
    case 2:
        return 2; // x--, goes one place up
        break;
    case 3:
        return 3; // y++, goes right
        break;
    case 4:
        return 4; //y--, goes left
    default:
        break;
    }
    return NULL;
}


void graphics::health_decrease(int i) {}
void graphics::health_increase(int i) {}

vampires::vampires() {
    srand((unsigned)time(0));
    this->power = rand() % 4 + 1;
    this->defense = rand() % 3;
    this->health = 10;
    this->potions = rand() % 2;
};
void vampires::health_regain() {
    health = 10; 
};
void vampires::set_power(int i) { 
    this->power = i; 
}
void vampires::set_defense(int i) {
    this->defense = i;
}
int vampires::getpower() const { 
    return this->power; 
}
int vampires::getdefense()const { 
    return defense; 
}
int vampires::gethealth()const { 
    return this->health; 
}
int vampires::get_potions()const { 
    return this->potions; 
}
void vampires::printstats() const {
    cout << "the power, the defense and the health are:" << getpower() << "," << getdefense() << "," << gethealth() << endl;
}

int vampires::move() {
    switch (1 + rand() % 8) {  // οι περιπτωσεις να μετακινηθει προς οποιαδήποτε κατευθυνση είναι ισοπίθανη
    case 1:
        return 1; // x++, v goes down
        break;
    case 2:
        return 2; //x--, v goes up
        break;
    case 3:
        return 3; // y++
        break;
    case 4:
        return 4; // y--
        break;
    case 5:
        return 5; // x++ and y++
        break;
    case 6:
        return 6; // x++ and y-- 
        break;
    case 7:
        return 7; // x-- and y++
        break;
    case 8:
        return 8; // x-- and y--
    default:
        break;
    }
    return NULL;
}
void vampires::health_decrease(int i) { this->health -= i; }
void vampires::health_increase(int i) { this->health += i; }

werewolves::werewolves() {
    srand((unsigned)time(0));
    this->power = rand() % 4;
    this->defense = rand() % 3;
    this->health = 10;
    this->potions = rand() % 2;
};
void werewolves::health_regain() { 
    health = 10; 
};
void werewolves::set_power(int i) { 
    this->power = i; 
}
int werewolves::getpower() const { 
    return this->power; 
}
void werewolves::set_defense(int i) { 
    this->defense = i; 
}
int werewolves::getdefense()const { 
    return this->defense; 
}
int werewolves::gethealth()const { 
    return this->health; 
}
int werewolves::get_potions()const { 
    return this->potions; 
}

void werewolves::health_decrease(int i) { 
    this->health -= i; 
}
void werewolves::health_increase(int i) { 
    this->health += i; 
}

void werewolves::printstats_w()const {
    cout << "the power, the defense and the health are:" << getpower() << "," << getdefense() << "," << gethealth() << endl;
}

avatars::avatars() {
    potions = rand() % 2;
    A = 'b';
}
char avatars::get_team() { 
    return A; 
};
void avatars::set_potions(int i) { 
    potions = i; 
};
void avatars::set_char(char a) {
    A = a; 
};

int avatars::input(int i) {
    switch (i) {
    case 's': 
        return 1; //x++
        break;  
    case  'w': 
        return 2; //x--
        break;
    case 'd':
        return 3; //y++
        break;
    case 'a': 
        return 4; //y--
    default:
        break;
    }
    return NULL;
}