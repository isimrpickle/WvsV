#include <iostream>
#include"graphics.h"
#include <cstdlib> // in order to use srand and rand 

using namespace std;

void graphics::move() {
    switch (1 + rand() % 4) {  // οι περιπτωσεις να μετακινηθει προς οποιαδήποτε κατευθυνση είναι ισοπίθανη
    case 1:
        this->x += 1;
        break;
    case 2:
        this->x -= 1;
        break;
    case 3:
        this->y += 1;
        break;
    case 4:
        this->y -= 1;
    default:
        break;
    }
}

void werewolves::printstats_w()const {
    cout << "the power, the defense and the health are:" << getpower() << "," << getdefense() << "," << gethealth() << endl;
}

void vampires::printstats()const {
    cout << "the power, the defense and the health are:" << getpower() << "," << getdefense() << "," << gethealth() << endl;
}

void vampires::move() {
    switch (1 + rand() % 8) {  // οι περιπτωσεις να μετακινηθει προς οποιαδήποτε κατευθυνση είναι ισοπίθανη
    case 1:
        set_x(get_x() + 1);
        break;
    case 2:
        set_x(get_x() - 1);
        break;
    case 3:
        set_y(get_y() - 1);
        break;
    case 4:
        set_y(get_y() + 1);
        break;
    case 5:
        set_x(get_x() + 1);
        set_y(get_y() + 1);
        break;
    case 6:
        set_x(get_x() + 1);
        set_y(get_y() - 1);
        break;
    case 7:
        set_x(get_x() - 1);
        set_y(get_y() + 1);
        break;
    case 8:
        set_x(get_x() - 1);
        set_y(get_y() - 1);
    default:
        break;
    }
}

void graphics::update_charactes(graphics graphic, unsigned short int map_x, unsigned short int map_y) {
	unsigned short int compare_for_change_on_x = graphic.x;
	unsigned short int compare_for_change_on_y = graphic.y;
	while (graphic.x == compare_for_change_on_x || graphic.y == compare_for_change_on_y) {
	int movement = rand() % 4; // there 4 basic ways for a chracter to move

	if (movement == 1 && graphic.x < map_x) 
		graphic.set_x(graphic.x++);
	if (movement == 2 && graphic.y < map_y)
		graphic.set_y(graphic.y++);
	if (movement == 3 && graphic.x > 0)
		graphic.set_x(graphic.x--);
	if (movement == 0 && graphic.y > 0)
		graphic.set_y(graphic.y--);
	}

	
}