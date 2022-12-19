#pragma once
#include <vector>
#include <stdlib.h>
#include "graphics.h"
using namespace std;

void map_destroy_array(string*** array_for_map);

string** create_array_for_map(); // creates an array that consists of the graphics of the game

void printing_map(string** array_for_map, vector<vampires>vamps, vector<werewolves> lykoi, avatars av, graphics,bool day); // prints the map of the game 

string** map_create(); // creates the map with user input

void game_update(string** array, vector<vampires> vec, vector<werewolves>, avatars& i, graphics&);

void move_update(string** array, graphics& i, int move);

void will_it_attack(graphics&, graphics&, string**);

void next_to_me(string** array, vector<vampires> vamps, vector<werewolves>lukoi); // checks and finds whether a character has someonenext to him 

bool check_if_allowed(unsigned short  x, unsigned short y, string** array, graphics);// if a character has an enemy next to him there is a posibility of attack

void healing(graphics&, graphics&);// if a character has an ally then there is a posibilty of healing

void run_away(graphics&, string**);

void paused(vector<vampires> vamps, vector<werewolves> lukoi, avatars& i);





