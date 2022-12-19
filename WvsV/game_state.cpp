
#include "game_state.h"
#include "graphics.h"
#include <string>
#include <windows.h>
#include <conio.h> //χρηση του getch() για αμεσο input στη κινηση του αβαταρ (δεν χρειαζεται το εντερ)
using namespace std;

unsigned short x_for_map, y_for_map;
string** create_array_for_map() {
    string** array_for_map = new string * [x_for_map + 1];
    for (int i = 0; i < y_for_map; i++) {
        array_for_map[i] = new string[y_for_map + 1];
    }

    for (int i = 0; i < x_for_map; i++) {
        for (int n = 0; n < y_for_map; n++) {
            array_for_map[i][n] = ":__:";
        }
    }

    return array_for_map;
}
void printing_map(string** array_for_map, vector<vampires>vamps,vector<werewolves> lykoi, avatars av, graphics potion, bool day) {
    cout << system("cls") << endl;
    if (day) {
        system("color 6"); //yellow
        cout << "Sunlight" << endl; 
    }
    else {
        system("color 8"); //gray
         cout << "Moonlight" << endl;
    }
    for (int i = 0; i < x_for_map; i++) {
        for (int n = 0; n < y_for_map; n++) {
            if(array_for_map[i][n]!= " || " && array_for_map[i][n] != " ~~ " && array_for_map[i][n]!= " P ")
            array_for_map[i][n] = ":__:";
        }
    }
    array_for_map[av.get_x()][av.get_y()] = " A ";
    for (int i = 0; i < vamps.size(); i++) {
        array_for_map[vamps[i].get_x()][vamps[i].get_y()] = " V ";
    }

    for (int i = 0; i < lykoi.size(); i++) {
       
        array_for_map[lykoi[i].get_x()][lykoi[i].get_y()] = " W ";
    }

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
                break;
            }
            if (part_one.get_y() == part_two.get_y() && check_position(part_one.get_x(), part_two.get_x())) {
                healing(part_one, part_two);
                break;
            }
        }
        for (auto p = lukoi.begin(); p != lukoi.end(); p++) {
            werewolves lukos = *p;
            if (lukos.get_x() == part_one.get_x() && check_position(lukos.get_y(), part_one.get_y())) {
                will_it_attack(lukos, part_one, array);
                if(lukos.gethealth() == 0) 
                    lukoi.erase(p);
                if (part_one.gethealth()) 
                    vamps.erase(i);
                break;
            }

            if (lukos.get_y() == part_one.get_y() && check_position(lukos.get_x(), part_one.get_x())) {
                will_it_attack(lukos, part_one, array);
                if (lukos.gethealth() == 0 || part_one.gethealth() == 0) {
                    if (lukos.gethealth() == 0) 
                        lukoi.erase(p);
                    if (part_one.gethealth()) 
                        vamps.erase(i); 
                    break;
                }
            }
        }
    }
        for (auto i = lukoi.begin(); i != lukoi.end(); i++) {
            werewolves part_one = *i;
            int p = 1;
            for (auto f = lukoi.begin() + p; f != lukoi.end(); f++) {
                werewolves part_two = *f;
                if (part_one.get_x() == part_two.get_x() && check_position(part_one.get_y(), part_two.get_y())) {
                    healing(part_one, part_two);
                    break;
                }
                
                if (part_one.get_y() == part_two.get_y() && check_position(part_one.get_x(), part_two.get_x())) {
                    healing(part_one, part_two);
                    break;
                }
            }
        }
   
};
bool check_if_allowed(unsigned short x, unsigned short y, string** array) {
    if (x > x_for_map || y > y_for_map)
        return false;
    if (array[x][y] != ":__:" && array[x][y]!=" P ")
        return false;

    return true;
};

void paused(vector<vampires> vamps, vector<werewolves> lukoi, avatars& i) {
    int exit = 0;
    cout <<" The game is paused \nNumber of vampires : " << vamps.size() << "\nNumber of werewolves : " << lukoi.size();
    for (int i = 0; i < vamps.size(); i++) {
        vampires y;
        werewolves z;
        vamps[i] = y;
        lukoi[i] = z;
        cout << endl<<"the health of vampire " <<i+1    << "is: "<< y.gethealth() << endl;
        cout << "the health of werewolf" << i + 1 << "is: " << z.gethealth() << endl;

    }
    cout << endl << "the key 'h' is for healing your team and the key'esc' is for ending the game" << endl;
    cout << "press p again for exiting the pause menu" << endl;
    while (exit != 1) {
        exit = _getch();
        if (exit == 'p') 
            exit = 1;       
    }
};

void game_update(string** array, vector<vampires> vamps,vector<werewolves> lukoi, avatars& i, graphics& potion) {
    int  movement;
    do {
    bool day = rand() % 2;
    if (i.get_x() == potion.get_x() && i.get_y() == potion.get_y()) 
        i.set_potions(i.get_potions() + 1);
        this_thread::sleep_for(200ms);
        next_to_me(array, vamps, lukoi);
        movement = _getch();    
        if (day == true && i.get_potions() > 0 && i.get_team() == 'v' && movement == 'h') {
            for (int i = 0; i < vamps.size(); i++) {
                vamps[i].health_regain();
                cout << '\a';
            }
         }
        if (day != true && i.get_potions() > 0 && i.get_team() == 'w' && movement == 'h') {
            for (int i = 0; i < vamps.size(); i++) {
                vamps[i].health_regain();
                cout << '\a';
            }
        }

         if (movement== '\x1B')  //vk number for esc
             break;
        if (movement == 'p')
            paused(vamps, lukoi, i);
        else {
            move_update(array, i, i.input(movement));
            for (int i = 0; i < vamps.size(); i++) {
                move_update(array, vamps[i], vamps[i].move());
            }
            for (int i = 0; i < lukoi.size(); i++) {
                move_update(array, lukoi[i], lukoi[i].move());
            }
        }

        
        
        printing_map(array,vamps,lukoi,i,potion,day);
    } while (vamps.size() > 0 || lukoi.size() > 0);
}

void move_update(string** array, graphics& i, int move) { // συναρτηση που προυποθετει να γινεται διασχιση του vector απο πριν καθως και ελεγχος πως καλειται μόνο σε Αβαταρ ή werewolf!
    // unsigned short int result;
    if (i.get_type() == WEREWOLF) {
        // result = i.move();
        switch (move) {
        case 1:
            if (check_if_allowed(i.get_x() + 1, i.get_y(), array)) 
                i.set_x(i.get_x() + 1);

            break;
        case 2:
            if (check_if_allowed(i.get_x() - 1, i.get_y(), array)) 
                i.set_x(i.get_x() - 1);
            
            break;
        case 3:
            if (check_if_allowed(i.get_x(), i.get_y() + 1, array)) 
                i.set_y(i.get_y() + 1);
            
            break;
        case 4:
            if (check_if_allowed(i.get_x(), i.get_y() - 1, array)) 
                i.set_y(i.get_y() - 1);

            break;
        default:
            break;
        }
    }
    else if (i.get_type() == VAMPIRE) {
        //  result = i.move();
        switch (move) {
        case 1:
            if (check_if_allowed(i.get_x() + 1, i.get_y(), array))
                i.set_x(i.get_x() + 1);
            break;
        case 2:
            if (check_if_allowed(i.get_x() - 1, i.get_y(), array)) 
                i.set_x(i.get_x() - 1);
            

            break;
        case 3:
            if (check_if_allowed(i.get_x(), i.get_y() + 1, array)) 
                i.set_y(i.get_y() + 1);
            

            break;
        case 4:
            if (check_if_allowed(i.get_x(), i.get_y() - 1, array))
                i.set_y(i.get_y() - 1);
            break;
        case 5:
            if (check_if_allowed(i.get_x() + 1, i.get_y() + 1, array)) {
                i.set_x(i.get_x() + 1);
                i.set_y(i.get_y() + 1);
            }

            break;
        case 6:
            if (check_if_allowed(i.get_x() + 1, i.get_y() - 1, array)) {
                 i.set_x(i.get_x() + 1);
                i.set_y(i.get_y() - 1);
            }
               
            break;
        case 7:
            if (check_if_allowed(i.get_x() - 1, i.get_y() + 1, array)) {
                i.set_x(i.get_x() - 1);
                i.set_y(i.get_y() + 1);
            }
            break;
        case 8:
            if (check_if_allowed(i.get_x() - 1, i.get_y() + 1, array)) {
                i.set_x(i.get_x() - 1);
                i.set_y(i.get_y() + 1);
            }
        default:
            break;
        }
    }
    else {
        switch (move) {
        case 1:
            if (check_if_allowed(i.get_x() + 1, i.get_y(), array)) 
                i.set_x(i.get_x() + 1);
           
            break;
        case 2:
            if (check_if_allowed(i.get_x() - 1, i.get_y(), array)) 
                i.set_x(i.get_x() - 1);
            break;
        case 3:
            if (check_if_allowed(i.get_x(), i.get_y() + 1, array))
                i.set_y(i.get_y() + 1);
            break;
        case 4:
            if (check_if_allowed(i.get_x(), i.get_y() - 1, array)) 
                i.set_y(i.get_y() - 1);
        default:
            break;
        }
    }
}

string** map_create() {
    int x = 0, y = 0;
    char team='o';
    
    while (team != 'v' && team != 'w') {
        cout << "What team are you? V for Vampires or W for Werewolves" << endl;
        cin >> team;
    }

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
    avatar.set_char(team);

    array_for_map[avatar.get_x()][avatar.get_y()] = "  A ";

    graphics potion(rand() % x_for_map, rand() % y_for_map, POTION);
    fix_position(array_for_map, potion);
    array_for_map[potion.get_x()][potion.get_y()] = " P ";


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

        werewolf.set_x(rand() % x_for_map);
        werewolf.set_y(rand() % y_for_map);
        werewolf.set_type(WEREWOLF);
        werewolf.set_power(rand() % 4 + 1);
        werewolf.set_defense(rand() % 3);

        fix_position(array_for_map, werewolf);

        lukoi.push_back(werewolf);
        the_vampires.push_back(vampire);

    }

    printing_map(array_for_map, the_vampires,lukoi, avatar, potion, rand() % 2);

    game_update(array_for_map,the_vampires,lukoi, avatar, potion);
    
    map_destroy_array(&array_for_map);

    return array_for_map;
};
void map_destroy_array(string*** array_for_map) {
    delete[] array_for_map;
};

void run_away(graphics& graphic, string** array) {
    bool changes = false;
    int saved_x = graphic.get_x();
    int saved_y = graphic.get_y();
    if (graphic.get_type() == WEREWOLF) {
        for (int i = 1; i <= 4; i++) {
            move_update(array, graphic, i);
            if (saved_x != graphic.get_x() || saved_y != graphic.get_y())
                break;
        }
    }
    else {
        for (int i = 1; i <= 8; i++) {
            move_update(array, graphic, i);
            if (saved_x != graphic.get_x() || saved_y != graphic.get_y())
                break;
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
            cout << y.gethealth() << endl;
            cout << '\a';  //bell sound
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
            cout << i.gethealth() << endl;
            cout << '\a'; //bell sound
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
                cout << '\a';//bell sound
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
                cout << '\a'; //bell sound
            default:
                break;
            }
        }
    }
}


