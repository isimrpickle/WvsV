#include <iostream>
#include "game_state.h"

int main() {
    unsigned short int x, y;
    cout << "Enter the dimensions you wish! x: " << endl;
    cin >> x;
    cout << "y: " << endl;
    cin >> y;


    printing_map(x, y);

}