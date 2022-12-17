
#include "game_state.h"
#include "graphics.h"
#include <string>
#include <windows.h>
#include <conio.h> //χρηση του getch() για αμεσο input στη κινηση του αβαταρ (δεν χρειαζεται το εντερ)
using namespace std;
#define esc 27;
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

void next_to_me(string** array, vector<vampires> vamps,vector<werewolves>lukoi) {
    for (auto i = vamps.begin(); i != vamps.end(); i++) {
        vampires part_one = *i;
        int p = 1;
        for (auto f = vamps.begin() + p; f != vamps.end(); f++) {
            vampires part_two = *f;
            if (part_one.get_x() == part_two.get_x() && check_position(part_one.get_y(), part_two.get_y())) {
                healing(part_one, part_two);
            }
            if (part_one.get_y() == part_two.get_y() && check_position(part_one.get_x(), part_two.get_x())) {
                if (part_one.get_type() == part_two.get_type())
                    healing(part_one, part_two);
            }
        }
        for (auto p = lukoi.begin(); p != lukoi.end(); p++) {
            werewolves lukos = *p;
            if (lukos.get_x() == part_one.get_x() && check_position(lukos.get_y(), part_one.get_y()))
                will_it_attack(lukos, part_one, array);
            if (lukos.get_y() == part_one.get_y() && check_position(lukos.get_x(), part_one.get_x()))
                will_it_attack(lukos, part_one, array);
        }
    }
        for (auto i = lukoi.begin(); i != lukoi.end(); i++) {
            werewolves part_one = *i;
            int p = 1;
            for (auto f = lukoi.begin() + p; f != lukoi.end(); f++) {
                werewolves part_two = *f;
                if (part_one.get_x() == part_two.get_x() && check_position(part_one.get_y(), part_two.get_y())) 
                    healing(part_one, part_two);
                
                if (part_one.get_y() == part_two.get_y() && check_position(part_one.get_x(), part_two.get_x())) 
                        healing(part_one, part_two);    
            }
        }
   
};
bool check_if_allowed(unsigned short x, unsigned short y, string** array) {
    if (x > x_for_map || y > y_for_map)
        return false;
    if (array[x][y] != ":__:")
        return false;

    return true;
};
void game_update(string** array, vector<vampires> vamps,vector<werewolves> lukoi, avatars& i) {
    // int movement = GetKeyState(VK_NUMPAD0) & 0x8000;
    int  movement;
    do {
        this_thread::sleep_for(200ms);
        next_to_me(array, vamps, lukoi);
        movement = _getch();
         if (movement== '27')  // ascii code for esc
             break;
        // VkKeyScanA(movement);
        move_update(array, i, i.input(movement));
        for (auto graph = vamps.begin(); graph != vamps.end(); graph++) {
            graphics current_character = *graph;
            move_update(array, current_character, current_character.move());
        }
        for (auto graph = lukoi.begin(); graph != lukoi.end(); graph++) {
            graphics current_character = *graph;
            move_update(array, current_character, current_character.move());
        }
        printing_map(array);
    } while (vamps.size() > 0 || lukoi.size() > 0);
}

void move_update(string** array, graphics& i, int move) { // συναρτηση που προυποθετει να γινεται διασχιση του vector απο πριν καθως και ελεγχος πως καλειται μόνο σε Αβαταρ ή werewolf!
    // unsigned short int result;
    if (i.get_type() == WEREWOLF) {
        // result = i.move();
        switch (move) {
        case 1:
            if (check_if_allowed(i.get_x() + 1, i.get_y(), array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() + 1);
                array[i.get_x()][i.get_y()] = "  W  ";
            }

            break;
        case 2:
            if (check_if_allowed(i.get_x() - 1, i.get_y(), array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() - 1);
                array[i.get_x()][i.get_y()] = "  w  ";
            }
            break;
        case 3:
            if (check_if_allowed(i.get_x(), i.get_y() + 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_y(i.get_y() + 1);
                array[i.get_x()][i.get_y()] = " W ";
            }
            break;
        case 4:
            if (check_if_allowed(i.get_x(), i.get_y() - 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_y(i.get_y() - 1);
                array[i.get_x()][i.get_y()] = "  w ";
            }
            break;
        default:
            break;
        }
    }
    else if (i.get_type() == VAMPIRE) {
        //  result = i.move();
        switch (move) {
        case 1:
            if (check_if_allowed(i.get_x() + 1, i.get_y(), array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() + 1);
                array[i.get_x()][i.get_y()] = "  V ";
            }
            break;
        case 2:
            if (check_if_allowed(i.get_x() - 1, i.get_y(), array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() - 1);
                array[i.get_x()][i.get_y()] = "  V ";
            }

            break;
        case 3:
            if (check_if_allowed(i.get_x(), i.get_y() + 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_y(i.get_y() + 1);
                array[i.get_x()][i.get_y()] = " V ";
            }

            break;
        case 4:
            if (check_if_allowed(i.get_x(), i.get_y() - 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_y(i.get_y() - 1);
                array[i.get_x()][i.get_y()] = "  V ";
            }
            break;
        case 5:
            if (check_if_allowed(i.get_x() + 1, i.get_y() + 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() + 1);
                i.set_y(i.get_y() + 1);
                array[i.get_x()][i.get_y()] = "  V ";
            }
            break;
        case 6:
            if (check_if_allowed(i.get_x() + 1, i.get_y() - 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() + 1);
                i.set_y(i.get_y() - 1);
                array[i.get_x()][i.get_y()] = "  V ";
            }
            break;
        case 7:
            if (check_if_allowed(i.get_x() - 1, i.get_y() + 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() - 1);
                i.set_y(i.get_y() + 1);
                array[i.get_x()][i.get_y()] = "  V ";
            }
            break;
        case 8:
            if (check_if_allowed(i.get_x() - 1, i.get_y() + 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() - 1);
                i.set_y(i.get_y() + 1);
                array[i.get_x()][i.get_y()] = "  V ";
            }
        default:
            break;
        }
    }
    else {
        switch (move) {
        case 1:
            if (check_if_allowed(i.get_x() + 1, i.get_y(), array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() + 1);
                array[i.get_x()][i.get_y()] = "  A ";
            }
            break;
        case 2:
            if (check_if_allowed(i.get_x() - 1, i.get_y(), array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_x(i.get_x() - 1);
                array[i.get_x()][i.get_y()] = "  A ";
            }
            break;
        case 3:
            if (check_if_allowed(i.get_x(), i.get_y() + 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_y(i.get_y() + 1);
                array[i.get_x()][i.get_y()] = "  A ";
            }
            break;
        case 4:
            if (check_if_allowed(i.get_x(), i.get_y() - 1, array)) {
                array[i.get_x()][i.get_y()] = ":__:";
                i.set_y(i.get_y() - 1);
                array[i.get_x()][i.get_y()] = "  A ";
            }
        default:
            break;
        }
    }
}

string** map_create() {
    srand((unsigned)time(NULL));
    int x = 0, y = 0;
    while (x * y <= 15 || x < 4 || y < 4) {
        cout << "Hello! \n Please enter the dimensions you want! \n x: " << endl;
        cin >> x;
        cout << " y: " << endl;
        cin >> y;
        x_for_map = x;
        y_for_map = y;
    };
    vector<vampires>the_vampires;
    vector<werewolves> lukoi;

    string** array_for_map = create_array_for_map();

    avatars avatar;
    avatar.set_type(AVATAR);
    avatar.set_x(rand() % x_for_map);
    avatar.set_y(rand() % y_for_map);

    array_for_map[avatar.get_x()][avatar.get_y()] = "  A ";

    for (int i = 0; i <= (x_for_map * y_for_map) / 100; i++) {
        graphics tree(rand() % x_for_map, rand() % y_for_map, TREE);
        fix_position(array_for_map, tree);
        array_for_map[tree.get_x()][tree.get_y()] = " || ";
        graphics water(rand() % x_for_map, rand() % y_for_map, WATER);
        fix_position(array_for_map, water);

        array_for_map[water.get_x()][water.get_y()] = " ~~ ";
    }
    werewolves werewolf;
    vampires vampire;

    for (int i = 0; i < (x_for_map * y_for_map) / 15; i++) {
        vampire.set_type(VAMPIRE);
        vampire.set_x(rand() % x_for_map);
        vampire.set_y(rand() % y_for_map);
        vampire.set_power(rand() % 4 + 1);
        vampire.set_defense(rand() % 3);

        fix_position(array_for_map, vampire);

        array_for_map[vampire.get_x()][vampire.get_y()] = "  V ";

        werewolf.set_x(rand() % x_for_map);
        werewolf.set_y(rand() % y_for_map);
        werewolf.set_type(WEREWOLF);
        werewolf.set_power(rand() % 4 + 1);
        werewolf.set_defense(rand() % 3);

        fix_position(array_for_map, werewolf);

        array_for_map[werewolf.get_x()][werewolf.get_y()] = "  W ";

        lukoi.push_back(werewolf);
        the_vampires.push_back(vampire);

    }
    for (int i = 0; i != the_vampires.size(); i++) {
        cout << the_vampires[i].gethealth() << " vamp \n";
        cout << lukoi[i].gethealth() << endl;
    }


    printing_map(array_for_map);
    // int exit;

   game_update(array_for_map,the_vampires,lukoi, avatar);
    // next_to_me(array_for_map, enemies);
    return array_for_map;
};
void map_destroy_array(string*** array_for_map) {
    delete[] array_for_map;
};

void run_away(graphics& graphic, string** array) {
    if (graphic.get_type() == WEREWOLF) {
        for (int i = 1; i <= 4; i++) {
            move_update(array, graphic, i);
        }
    }
    else {
        for (int i = 1; i <= 8; i++) {
            move_update(array, graphic, i);
        }
    }
}

void will_it_attack(graphics& i, graphics& y, string** array) {
    if (i.getpower() > y.getpower()) { // βλεπουμε ποιος κανει το attack
        switch (rand() % 2) {
        case 0:
            run_away(y, array); // επιτυγχανεται η αποφυγη με συναρτηση move. Θα διορθωθει και αλλο!!
            break;
        case 1:
            if (i.getpower() > y.getdefense()) // Ελεγχουμε αν ο ατακερ εχει μεγαλυτερη δυναμη
                y.health_decrease(i.getpower()); //μειωνουμε τη ζωη του αμυνομενου αναλογα το power του επιτεθομενου
        default:
            break;
        }
    }
    if (y.getpower() > i.getpower()) {
        switch (rand() % 2) {
        case 0:
            run_away(i, array); // επιτυγχανεται η αποφυγη με συναρτηση move. Θα διορθωθει και αλλο!!
            break;
        case 1:
            if (y.getpower() > i.getdefense())
                i.health_decrease(y.getpower());
        default:
            break;
        }
    }
}



void healing(graphics& i, graphics& y)
{ // Η συναρτηση αυτη χρησιμοπειται αφου εχει γινει ελεγχος οτι 2 ιδια αντικειμενα βρισκονται σε διπλανες θεσεις
    if (i.gethealth() < 10 && y.gethealth() == 10)
    {
        if (y.get_potions() > 0)
        {
            switch (rand() % 2)
            {
            case 1:
                i.health_increase(1);
            default:
                break;
            }
        }
    }
    if (y.gethealth() < 10 && i.gethealth() == 10)
    {
        if (i.get_potions() > 0)
        {
            switch (rand() % 2)
            {
            case 1:
                y.health_increase(1);
            default:
                break;
            }
        }
    }
}

