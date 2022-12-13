
#include "game_state.h"
#include "graphics.h"
#include <string>
#include<windows.h>

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

bool check_position(int one, int two) {
    if (one == two++ || one == two--)
        return true;

    return false;
};

void next_to_me(string** array, vector<graphics>vec) {
    for (auto i = vec.begin(); i != vec.end(); i++) {
        graphics part_one = *i;
        int p = 1;
        for (auto f = vec.begin() +p; f != vec.end(); f++) {
            graphics part_two = *f;

            if(part_one.get_x() == part_two.get_x()&&
               check_position(part_one.get_y(), part_two.get_y())){
                if (part_one.get_type() == part_two.get_type())
                    healing(part_one, part_two);
                else
                    will_it_attack(part_one, part_two);
            }
            if (part_one.get_y() == part_two.get_y() &&
                check_position(part_one.get_x(), part_two.get_x())) {
                if (part_one.get_type() == part_two.get_type())
                    healing(part_one, part_two);
                else
                    will_it_attack(part_one, part_two);
            }

        }
    }

};

bool check_if_allowed(unsigned short  x, unsigned short y, string** array) {
    if (x > x_for_map || y > y_for_map)
        return false;

    if (array[x][y] != ":__:")
        return false;
    
    return true;
};


void game_update(string** array,vector<graphics> vec,avatars& i) {
    bool changed = false;
    while (!changed) {
    unsigned short new_place = i.input();
        switch (new_place) {
            case 1:
                changed = check_if_allowed(i.get_x() + 1, i.get_y(), array) == true ? true : false;
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() + 1);
                array[i.get_x()][i.get_y()] = "  A ";

           case 2:
               changed = check_if_allowed(i.get_x() - 1, i.get_y(), array) == true ? true : false;
               array[i.get_x()][i.get_y()] = ":__:";
               i.set_x(i.get_x() - 1);
               array[i.get_x()][i.get_y()] = "  A ";

            case 3:
                changed = check_if_allowed(i.get_x(), i.get_y() + 1, array) == true ? true : false;
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_y(i.get_y() + 1);
                array[i.get_x()][i.get_y()] = " A ";
            case 4:
                changed = check_if_allowed(i.get_x(), i.get_y() - 1, array) == true ? true : false;
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_y(i.get_y() - 1);
                array[i.get_x()][i.get_y()] = "  A ";
        }
             
    }
    



    for (auto graph = vec.begin(); graph != vec.end(); graph++) {
        graphics current_character = *graph;

    }
}


string** map_create() {
    srand((unsigned)time(NULL));

    int x=0, y=0;

    while (x * y <= 15 || x<4 || y<4 ) {
        cout << "Hello! \n Please enter the dimensions you want! \n x: " << endl;
        cin >> x;
        cout << " y: " << endl;
        cin >> y;
        x_for_map = x;
        y_for_map = y;
    };

    vector<graphics> enemies;

    string** array_for_map = create_array_for_map();

    avatars avatar;
    avatar.set_x(rand() % x_for_map);
    avatar.set_y(rand() % y_for_map);

    array_for_map[avatar.get_x()][avatar.get_y()] = "  A ";

    for (int i = 0; i <= (x_for_map * y_for_map) / 100; i++) {
        graphics tree(rand() % x_for_map, rand() % y_for_map, TREE);
        fix_position(array_for_map, tree);

        array_for_map[tree.get_x()][tree.get_y()] = " || ";

        graphics water(rand() % x_for_map, rand() % y_for_map, WATER);
        fix_position(array_for_map,water);  
        
        array_for_map[water.get_x()][water.get_y()] = " ~~ ";
    }

    for (int i = 0; i < (x_for_map * y_for_map) / 15; i++) {

        vampires vampire;
        vampire.set_type(VAMPIRE);
        vampire.set_x(rand() % x_for_map);
        vampire.set_y(rand() % y_for_map);
       
        fix_position(array_for_map, vampire);
        
        array_for_map[vampire.get_x()][vampire.get_y()] = "  V ";

        werewolves werewolf;
        werewolf.set_x(rand() % x_for_map);
        werewolf.set_y(rand() % y_for_map);
        werewolf.set_type(WEREWOLF);

        fix_position(array_for_map, werewolf);

        array_for_map[werewolf.get_x()][werewolf.get_y()] = "  W ";

        enemies.push_back(vampire);
        enemies.push_back(werewolf);


      
    }

    printing_map(array_for_map);

    next_to_me(array_for_map, enemies);

    return array_for_map;
    
};


void map_destroy_array(string*** array_for_map) {
    delete[] array_for_map;
};


void will_it_attack(graphics& i, graphics& y) {
    if (i.getpower() > y.getpower()) {   //βλεπουμε ποιος κανει το attack
        switch (rand() % 2) {
        case 0:
            y.move();  //επιτυγχανεται η αποφυγη με συναρτηση move. Θα διορθωθει και αλλο!!
            break;
        case 1:
            if (i.getpower() > y.getdefense())  //Ελεγχουμε αν ο ατακερ εχει μεγαλυτερη δυναμη
                y.health_decrease(i.getpower()); //μειωνουμε τη ζωη του αμυνομενου αναλογα το power του επιτεθομενου
        default:
            break;
        }
        if (y.getpower() > i.getpower()) {
            switch (rand() % 2) {
            case 0:
                i.move();  //επιτυγχανεται η αποφυγη με συναρτηση move. Θα διορθωθει και αλλο!!
                break;
            case 1:
                if (y.getpower() > i.getdefense())
                    i.health_decrease(y.getpower());
            default:
                break;
            }
        }

    }
}

void healing(graphics &i,graphics &y) {  //Η συναρτηση αυτη χρησιμοπειται αφου εχει γινει ελεγχος οτι 2 ιδια αντικειμενα βρισκονται σε διπλανες θεσεις
    if (i.gethealth() < 10 && y.gethealth()==10) {
        if (y.get_potions() > 0) {
            switch (rand() % 2) {
            case 1:
                i.health_increase(1);
            default:
                break;   
            }
        }
    }
    if (y.gethealth() < 10 && i.gethealth() == 10) {
        if (i.get_potions() > 0) {
            switch (rand() % 2) {
            case 1:
                y.health_increase(1);
            default:
                break;
            }
        }
    }
}
