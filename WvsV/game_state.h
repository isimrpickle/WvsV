#pragma once


#include <list>
#include <stdlib.h>
#include "graphics.h"

using namespace std;

//bool is_someone_next_to_me(string** array, graphics graphic);

void fix_position(string** array, graphics& graphic);

string** create_array_for_map(unsigned  short int x, unsigned short y); // creates an array that consists of the graphics of the game


void printing_map(unsigned short int x, unsigned short int y, string** array_for_map); // prints the map of the game 


string** map_create(); // creates the map with user input


//bool can_i_move(unsigned short place, string** array_for_map, unsigned short x, unsigned short y);

