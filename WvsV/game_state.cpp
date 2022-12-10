
#include "game_state.h"
#include "graphics.h"
#include <string>


using namespace std;

unsigned short x_for_map, y_for_map;

string** create_array_for_map() {
    string** array_for_map = new string * [x_for_map];
        for (int i = 0; i < y_for_map; i++) {
            array_for_map[i] = new string[y_for_map];
        }
        for (int i = 0; i < x_for_map; i++) {
            for (int n = 0; n < y_for_map; n++) {
                array_for_map[i][n] = ":__:";
            }
        }

        return array_for_map;
}

void printing_map(string** array_for_map) {
    cout << system("cls") << endl;

    for (int i = 0; i < x_for_map; i++) {
        for (int n = 0; n < y_for_map; n++) {
            cout << array_for_map[i][n];
        }
        cout << endl;
    }

}
 

void fix_position(string** array, graphics& graphic) {
    while (array[graphic.get_x()][graphic.get_y()] != ":__:") {
        graphic.set_x(rand() % x_for_map);
        graphic.set_y(rand() % y_for_map);
    }
};


string** map_create() {
    srand((unsigned)time(NULL));

    int x=0, y=0;
    while(x* y <= 15) {
        cout << "Hello! \n Please enter the dimensions you want! \n x: " << endl;
        cin >> x;
        cout << " y: " << endl;
        cin >> y;
        x_for_map = x;
        y_for_map = y;
    };

    string** array_for_map = create_array_for_map();

    avatars avatar;
    avatar.set_x(rand() % x);
    avatar.set_y(rand() % y);

    array_for_map[avatar.get_x()][avatar.get_y()] = "  A ";

    for (int i = 0; i <= (x * y) / 100; i++) {
        graphics tree(rand() % x, rand() % y, TREE);
        fix_position(array_for_map, tree);

        array_for_map[tree.get_x()][tree.get_y()] = " || ";

        graphics water(rand() % x, rand() % y, WATER);
        fix_position(array_for_map,water);  
        
        array_for_map[water.get_x()][water.get_y()] = " ~~ ";
    }

    for (int i = 0; i < (x * y) / 15; i++) {
        vampires vampire;
        vampire.set_x(rand() % x);
        vampire.set_y(rand() % y);
        fix_position(array_for_map, vampire);
        
        array_for_map[vampire.get_x()][vampire.get_y()] = "  V ";

        werewolves werewolf;
        werewolf.set_x(rand() % x);
        werewolf.set_y(rand() % y);
        fix_position(array_for_map, werewolf);

        array_for_map[werewolf.get_x()][werewolf.get_y()] = "  W ";

        printing_map( array_for_map);
      
    }

    printing_map(array_for_map);

    return array_for_map;
    
};


void map_destroy_array(string*** array_for_map) {
    delete[] array_for_map;
};

