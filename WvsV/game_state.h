#pragma once


#include <list>
#include <stdlib.h>
#include "graphics.h"

using namespace std;

string** create_array_for_map(unsigned  short int x, unsigned short y); // creates an array that consists of the graphics of the game


void printing_map(unsigned short int x, unsigned short int y, string** array_for_map); // prints the map of the game 


string** map_create(); // creates the map with user input


//bool can_i_move(unsigned short place, string** array_for_map, unsigned short x, unsigned short y);

