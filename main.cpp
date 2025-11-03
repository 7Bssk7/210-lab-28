#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include <algorithm>
#include <numeric>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, HIGH_AGE = 15;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
void averageAge(const list<Goat>& );
void highAge( const list<Goat>& );
void findGoat( const list<Goat>& );
int main_menu();

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 11) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:    
                cout << "Average age.\n";
                averageAge(trip);
                break;  
            case 5:    
                cout << "High age.\n";
                highAge(trip);
                break; 
            case 6:    
                cout << "Find Goat.\n";
                findGoat(trip);
                break;      
            case 7:
            
                break;
            case 8:
            
                break;
            case 9:
            
                break;
            case 10:
            
                break;
            case 11:
            
                break;                
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Average age\n";
    cout << "[5] High age\n";
    cout << "[6] Find Goat.\n";
    cout << "[7] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 11) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 || input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void averageAge(const list<Goat>& trp){
    double avgAge = accumulate(trp.begin(), trp.end(), 0.0, [](double sum, const Goat& g){
        return sum + g.get_age();
    }) / trp.size();

    cout << "Average age: " << avgAge << endl;

    cout << endl;

}

void highAge(const list<Goat>& trp){
    bool hAge = any_of(trp.begin(), trp.end(), []( const Goat& g){ 
        return g.get_age() > HIGH_AGE;
    });

    cout << "There is a goat on the list that is over" << HIGH_AGE << " years old: " << (hAge ? "Yes" : "No") << endl;

}

void findGoat(const list<Goat>& trp){
    string name;
    cout << "Enter goat name to search: ";
    cin >> name;

    auto it = find(trp.begin(), trp.end(), name);

    if (it != trp.end()) {
        cout << "Found Goat: " << it->get_name()
             << " (" << it->get_age() << ", " << it->get_color() << ")" << endl;
    } else {
        cout << "Goat named '" << name << "' not found." << endl;
    }

} 

void allGoatSameAge(const list<Goat>& trp){
    int age;
    cout << "You have the choice to make all the goats the same age (0-20)" << endl;
    cout << "Your choice: ";
    cin >> age;
    while (age < 0 || age > 20) {
        cout << "Invalid age. Please enter a value between 0 and 20: ";
        cin >> age;
    }

    string name = trp.front().get_name();
    string color = trp.front().get_color();

    Goat g(name, age, color);
    
    fill(trp.begin(), trp.end(), g);
}