#include <cstring>
#include <iostream>
#include "game_state.h"
#include <string>
#include <vector>

using namespace std;

void printing_map(unsigned short int x, unsigned short int y) {
    vector <vector<string>> map(x, vector<string>(y, ":__:"));
    for (int i = 0; i < x; i++) {
        for (int n = 0; n < y; n++) {
            cout << map[i][n];
        }
        cout << endl;
    }
}
void map_create() {};