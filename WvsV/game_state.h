#pragma once
#include <vector>
#include <stdlib.h>
#include "graphics.h"
using namespace std;


// creates an array that consists of the graphics of the game
string** create_array_for_map(); 


 // prints the map of the game 
void printing_map(string** array_for_map, vector<vampires>vamps, vector<werewolves> lykoi, avatars av, graphics,bool day);


//fixes position for the graphics only when they are spawned, so that they don't collide
void fix_position(string** array, graphics& graphic);


// checks if a character has someone next to him
bool check_position(int one, int two); 


// checks and finds whether a character has someonenext to him 
void next_to_me(string** array, vector<vampires>& vamps, vector<werewolves>& lukoi, size_t*, size_t*);


// if a character has an enemy next to him there is a posibility of attack
bool check_if_allowed(unsigned short  x, unsigned short y, string** array, graphics);


 // pauses the game and allows the user toseehow many characters are alive 
void paused(vector<vampires> vamps, vector<werewolves> lukoi, avatars& i);


// has the loop that implements the game
void game_update(string** array, vector<vampires> vamps, vector<werewolves> lukoi, avatars& i, graphics& potion); 


// moves both the characters and the avatar in the game
void move_update(string** array, graphics& i, int move); 


 // creates the map with user input
void map_create_and_play();


// function that is used if a defender run away before an attack
void run_away(graphics& graphic, string** array); 


 // function that determines if and which character will attack
void will_it_attack(graphics*, graphics*, string**);


// if a character has an ally then there is a posibilty of healing
void healing(graphics*, graphics*);






