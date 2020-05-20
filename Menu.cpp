#include "Menu.h"
#include "Weapon.h"
#include "Dungeon.h"
#include "Player.h"
#include "utilities.h"
using namespace std;
Menu::Menu(Player* p) : pl(p){
    items.push_back(pl->get_weapon());
}
Menu::~Menu(){
    for(Item* i : items){
        if(i != pl->get_weapon()) // Don't delete the current weapon of the player
        delete i;
    }     
}
int Menu::size() const{return items.size();}
Item* Menu::getItem(int i) const {return items[i];}
void Menu::displayMenu() const{
    clearScreen();
    cout << "Inventory: " << endl;
    for(int i = 0; i < items.size();i++){
        cout << char('a' + i) << ". ";
        string temp = items[i]->get_name();
        if (temp[0] == 'a') // Scroll's first letter in menu needed to be capitalized
            cout << "A" << temp.substr(1) << endl;
        else // for weapon, just print its name
            cout << temp << endl;
    }
}
bool Menu::addItem(Item* i){
    if(items.size() < 27){
        items.push_back(i);
        return true;
    }
    return false;
}
void Menu::removeItem(int j) {
    delete items[j];
    items.erase(items.begin()+j);
}