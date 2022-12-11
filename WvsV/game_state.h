#pragma once


#include <vector>
#include <stdlib.h>
#include "graphics.h"

using namespace std;

//bool is_someone_next_to_me(string** array, graphics graphic);

//void fix_position(string** array, graphics& graphic);

string** create_array_for_map(); // creates an array that consists of the graphics of the game


void printing_map(string** array_for_map); // prints the map of the game 


string** map_create(); // creates the map with user input

void next_to_me(string** array, vector<graphics>vec);

//bool can_i_move(unsigned short place, string** array_for_map, unsigned short x, unsigned short y);

