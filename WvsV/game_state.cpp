
#include "game_state.h"
#include "graphics.h"
#include <string>
#include <windows.h>
#include <conio.h> //χρηση του getch() για αμεσο input στη κινηση του αβαταρ (δεν χρειαζεται το εντερ)
#include <algorithm>

using namespace std;

unsigned short x_for_map, y_for_map;

string** create_array_for_map() { // dynamic memory allocation for the 2d array used for the map
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

void printing_map(string** array_for_map, vector<vampires>vamps,vector<werewolves> lykoi, avatars av, graphics potion, bool day) {
    // prints the map and usefull information for the user 
    cout << system("cls") << endl;

    av.get_team() == 'v' ? cout << "Your team is Vampires \nYou can you your potion when it's day" : cout << "Your team is Werewolves \nYou can use your potion when it's night \n" << endl;
    if (day) {
        system("color 6"); //yellow
        cout << " \nThere's currently Sunlight" << endl; 
    }
    else {
        system("color 8"); //gray
         cout << "\nThere's currently Moonlight" << endl;
    }
    for (int i = 0; i < x_for_map; i++) {
        for (int n = 0; n < y_for_map; n++) {
            if(array_for_map[i][n]!= " || " && array_for_map[i][n] != " ~~ " && array_for_map[i][n]!= "  P ")
            array_for_map[i][n] = ":__:";
        }
    }
    array_for_map[av.get_x()][av.get_y()] = "  A ";
    for (int i = 0; i < vamps.size(); i++) {
        array_for_map[vamps[i].get_x()][vamps[i].get_y()] = "  V ";
    }

    for (int i = 0; i < lykoi.size(); i++) {
       
        array_for_map[lykoi[i].get_x()][lykoi[i].get_y()] = "  W ";
    }

    for (int i = 0; i < x_for_map; i++) {
        for (int n = 0; n < y_for_map; n++) {
            cout << array_for_map[i][n];
        }
        cout << endl;
    }
}

void fix_position(string** array, graphics& graphic) { // checks if a graphic spawned on an occupied place and fixes it 

    while (array[graphic.get_x()][graphic.get_y()] != ":__:") {
        graphic.set_x(rand() % x_for_map);
        graphic.set_y(rand() % y_for_map);
    }
};

bool check_position(int one, int two) { //checks if the numbers given have a difrence value of one 
    if (one == two++ || one == two--)
        return true;
    return false;
};

void next_to_me(string** array, vector<vampires>& vamps, vector<werewolves>& lukoi, size_t* vampires_size, size_t* werewolves_size) {
    bool healed = 0; //bool to use if an action happenedto stop the search
    int p = 0;
    for (int i = 0; i != vamps.size() - 1; i++) { //starts from the first vampire and searches from there if it has an ally next to it to heal
        p++;
        for (int f = p; f != vamps.size(); f++) {
            if (vamps[i].get_x() == vamps[f].get_x() && check_position(vamps[i].get_y(), vamps[f].get_y())) {
                healing(&vamps[i], &vamps[f]);
                if (vamps[i].get_potions() != 1 || vamps[f].get_potions() != 1)     // if an entity uses a potion,anaction has been taken so break the loop
                    healed = 1;

                break;
            }
            if (vamps[i].get_y() == vamps[f].get_y() && check_position(vamps[i].get_x(), vamps[f].get_x())) {
                healing(&vamps[i], &vamps[f]);
                if (vamps[i].get_potions() != 1 || vamps[f].get_potions() != 1)
                    healed = 1;

                break;
            }
        }
        if (healed)
            break;
        for (int p = 0; p != lukoi.size(); p++) {
            if (lukoi[p].get_x() == vamps[i].get_x() && check_position(lukoi[p].get_y(), vamps[i].get_y())) {
                will_it_attack(&lukoi[p], &vamps[i], array);

                if (lukoi[p].gethealth() == 0) { // if an entity dies erase it fromthe vector and decrease the variable used to check the size  
                   // lukoi.erase(lukoi.begin() + p);
                    werewolves_size--;
                }
                if (vamps[i].gethealth() == 0) {
                   // vamps.erase(vamps.begin() + i);
                    vampires_size--;
                }
                healed = 1;
                cout << '\a';
            }
            if (healed)
                break;
            if (lukoi[p].get_y() == vamps[i].get_y() && check_position(lukoi[p].get_x(), vamps[i].get_x())) {
                will_it_attack(&lukoi[p], &vamps[i], array);

                if (lukoi[p].gethealth() == 0 || vamps[i].gethealth() == 0) {
                    if (lukoi[p].gethealth() == 0) {
                       // lukoi.erase(lukoi.begin() + p);
                        werewolves_size--;
                    }
                    if (vamps[i].gethealth() == 0) {
                     //   vamps.erase(vamps.begin() + i);
                        vampires_size--;
                    }
                    healed = 1;
                    cout << '\a';
                }
            }
        }
    }
    p = 0;
    for (int i = 0; i != lukoi.size(); i++) { //starts from the first werewolf and searches from there if it has an ally next to it to heal
        p++;
        for (int f = p; f != lukoi.size(); f++) {
            if (lukoi[i].get_x() == lukoi[f].get_x() && check_position(lukoi[i].get_y(), lukoi[f].get_y())) {
                healing(&lukoi[i], &lukoi[f]);
                if (lukoi[i].get_potions() != 1 || lukoi[f].get_potions() != 1)
                    healed = 1;
                break;
            }
            if (lukoi[i].get_y() == lukoi[f].get_y() && check_position(lukoi[i].get_x(), lukoi[f].get_x())) {
                healing(&lukoi[i], &lukoi[f]);
                if (lukoi[i].get_potions() != 1 || lukoi[f].get_potions() != 1)
                    healed = 1;
                break;
            }

        }
    }
};

bool check_if_allowed(unsigned short x, unsigned short y, string** array, graphics i) {
    if (x >= x_for_map || y >= y_for_map)
        return false;
    if (i.get_type() == AVATAR) {
        if (array[x][y] != ":__:" && array[x][y] != "  P ")
            return false;
        array[x][y] = "  A "; 
    }
    else {
        if (array[x][y] != ":__:" || array[x][y]=="A")
            return false;
        if (i.get_type() == VAMPIRE) {
            array[x][y] = "  V ";
        }
        else
            array[x][y] = "  W ";
    }
    return true;
};

void paused(vector<vampires> vamps, vector<werewolves> lukoi, avatars& i) {
    int exit = 0;
    cout <<" The game is paused \nNumber of vampires : " << vamps.size() << "\nNumber of werewolves : " << lukoi.size();
    /*for (int i = 0; i < vamps.size(); i++) {
        
        cout << endl<<"the health of vampire " <<i+1    << "is: "<< vamps[i].gethealth() << endl;
        cout << "the health of werewolf" << i + 1 << "is: " << lukoi[i].gethealth() << endl;
        cout << endl<<"the health of vampire " <<i+1    << "is: "<< vamps[i].gethealth() << endl;
        cout << "the health of werewolf" << i + 1 << "is: " << lukoi[i].gethealth() << endl;

    }*/
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
    size_t for_werewolves = vamps.size();
    size_t for_vampires = lukoi.size();
    do {
    bool day = rand() % 2; // rand() % 2 to change from day to night

    if (i.get_x() == potion.get_x() && i.get_y() == potion.get_y()) // if the avatar reaches the potion, his potions number increase by one
        i.set_potions(i.get_potions() + 1);

        next_to_me(array, vamps, lukoi,&for_werewolves, &for_vampires); // function that checks if a character is next to each other in order to call attack or heal function

        movement = _getch(); // gets the user's input for te avatar without ENTER

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
    } while (for_vampires > 0 || for_werewolves > 0);
}

void move_update(string** array, graphics& i, int move) { 
    if (i.get_type() == WEREWOLF) { // checks for the type of the character 
        switch (move) {
        case 1:
            if (check_if_allowed(i.get_x() + 1, i.get_y(), array,i)) // based on the case the character moves 
                i.set_x(i.get_x() + 1);

            break;
        case 2:
            if (check_if_allowed(i.get_x() - 1, i.get_y(), array,i)) 
                i.set_x(i.get_x() - 1);
            
            break;
        case 3:
            if (check_if_allowed(i.get_x(), i.get_y() + 1, array,i)) 
                i.set_y(i.get_y() + 1);
            
            break;
        case 4:
            if (check_if_allowed(i.get_x(), i.get_y() - 1, array,i)) 
                i.set_y(i.get_y() - 1);

            break;
        default:
            break;
        }
    }
    else if (i.get_type() == VAMPIRE) { // vampires have 8 cases in total while werewolves and avatar have 4 
        switch (move) {
        case 1:
            if (check_if_allowed(i.get_x() + 1, i.get_y(), array,i))
                i.set_x(i.get_x() + 1);
            break;
        case 2:
            if (check_if_allowed(i.get_x() - 1, i.get_y(), array,i)) 
                i.set_x(i.get_x() - 1);
            

            break;
        case 3:
            if (check_if_allowed(i.get_x(), i.get_y() + 1, array,i)) 
                i.set_y(i.get_y() + 1);
            

            break;
        case 4:
            if (check_if_allowed(i.get_x(), i.get_y() - 1, array,i))
                i.set_y(i.get_y() - 1);
            break;
        case 5:
            if (check_if_allowed(i.get_x() + 1, i.get_y() + 1, array,i)) {
                i.set_x(i.get_x() + 1);
                i.set_y(i.get_y() + 1);
            }

            break;
        case 6:
            if (check_if_allowed(i.get_x() + 1, i.get_y() - 1, array,i)) {
                 i.set_x(i.get_x() + 1);
                i.set_y(i.get_y() - 1);
            }
               
            break;
        case 7:
            if (check_if_allowed(i.get_x() - 1, i.get_y() + 1, array,i)) {
                i.set_x(i.get_x() - 1);
                i.set_y(i.get_y() + 1);
            }
            break;
        case 8:
            if (check_if_allowed(i.get_x() - 1, i.get_y() + 1, array,i)) {
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
            if (check_if_allowed(i.get_x() + 1, i.get_y(), array,i)) 
                i.set_x(i.get_x() + 1);
           
            break;
        case 2:
            if (check_if_allowed(i.get_x() - 1, i.get_y(), array,i)) 
                i.set_x(i.get_x() - 1);
            break;
        case 3:
            if (check_if_allowed(i.get_x(), i.get_y() + 1, array,i))
                i.set_y(i.get_y() + 1);
            break;
        case 4:
            if (check_if_allowed(i.get_x(), i.get_y() - 1, array,i)) 
                i.set_y(i.get_y() - 1);
        default:
            break;
        }
    }
}

void map_create_and_play() {
    int x = 0, y = 0;
    char team='o';
    
    while (team != 'v' && team != 'w') { // the user chooses his team, v for vampires and W for werewolves
        cout << "What team are you? V for Vampires or W for Werewolves" << endl;
        try {
            cin >> team;
            if(team!='v'&&team!='w')
                throw   runtime_error("Typing is hard...");  //Βασίστηκα εδώ: https://stackoverflow.com/questions/27179011/c-exception-throw-a-string
        }
         catch (const exception& x) {
            cout<<"ERROR TYPE: "<< x.what()<< "\n";
        }
    }

    while (x * y <= 15 || x < 4 || y < 4) { // user picks the map dimensions , both need to be bigger than 4 in order for the gameto be playable
        cout << "Please enter the dimensions you want! \n x: " << endl;
        cin >> x;
        cout << " y: " << endl;
        cin >> y;
        x_for_map = x;
        y_for_map = y;

    };
    vector<vampires>the_vampires;
    vector<werewolves> lukoi;

    string** array_for_map = create_array_for_map(); // 2D array to print the map 

    avatars avatar;  // creates and put the avatar on the map
    avatar.set_type(AVATAR);
    avatar.set_x(rand() % x_for_map);
    avatar.set_y(rand() % y_for_map);
    avatar.set_char(team);

    array_for_map[avatar.get_x()][avatar.get_y()] = "  A ";

    graphics potion(rand() % x_for_map, rand() % y_for_map, POTION); // creates the potion on the map for the avatar
    fix_position(array_for_map, potion);
    array_for_map[potion.get_x()][potion.get_y()] = "  P ";


    for (int i = 0; i <= (x_for_map * y_for_map) / 100; i++) { // loop to create the hazard of the game, 10% of the map.
        graphics tree(rand() % x_for_map, rand() % y_for_map, TREE);
        fix_position(array_for_map, tree);

        array_for_map[tree.get_x()][tree.get_y()] = " || ";

        graphics water(rand() % x_for_map, rand() % y_for_map, WATER);
        fix_position(array_for_map, water);

        array_for_map[water.get_x()][water.get_y()] = " ~~ ";
    }
    werewolves werewolf;
    vampires vampire;

    for (int i = 0; i < (x_for_map * y_for_map) / 15; i++) {  // loop to create the enemies to the game and insert them to vectors  

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

    game_update(array_for_map,the_vampires,lukoi, avatar, potion); // the function where the main game loop happens
    
    delete[] array_for_map;

};


//checks all positions of the defender until he moves
void run_away(graphics& graphic, string** array) {
   
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

void will_it_attack(graphics* i, graphics* y, string** array) {
    if (i->getpower() > y->getpower()) { // checks who has greater attack power to attack
        switch (rand() % 2) {
        case 0:
            run_away(*y, array); // the defender has 1/2 chance to escape
            break;
        case 1:
            if (i->getpower() > y->getdefense()) 
                y->health_decrease(i->getpower() - y->getdefense()); 
            cout << y->gethealth() << endl;
            cout << '\a';  //bell sound
        default:
            break;
        }
    }
    if (y->getpower() > i->getpower()) {
        switch (rand() % 2) {
        case 0:
            run_away(*i, array); 
            break;
        case 1:
            if (y->getpower() > i->getdefense())
                i->health_decrease(y->getpower() - i->getdefense());
            cout << i->gethealth() << endl;
            cout << '\a'; //bell sound
        default:
            break;
        }
    }
}


//checks if a full hp ally has a potion and can heal someone
void healing(graphics* i, graphics* y) { 
    if (i->gethealth() < 10 && y->gethealth() == 10) {
        if (y->get_potions() > 0) {
            switch (rand() % 2) {
            case 1:
                i->health_increase(1);
                cout << '\a';//bell sound
            default:
                break;
            }
        }
    }
    if (y->gethealth() < 10 && i->gethealth() == 10) {
        if (i->get_potions() > 0) {
            switch (rand() % 2) {
            case 1:
                y->health_increase(1);
                cout << '\a'; //bell sound
            default:
                break;
            }
        }
    }
}


