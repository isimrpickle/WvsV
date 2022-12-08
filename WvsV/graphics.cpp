#include <iostream>
#include"graphics.h"
#include <cstdlib> // in order to use srand and rand 

using namespace std;

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