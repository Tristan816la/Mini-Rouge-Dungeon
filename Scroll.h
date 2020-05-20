#ifndef SCROLL_H
#define SCROLL_H
#include "Item.h"
#include <iostream>
class Player;
const int TELEPORTATION = 0;
const int IMPROVE_ARMOR = 1;
const int RAISE_STRENGTH = 2;
const int ENHANCE_HEALTH = 3; 
const int ENHANCE_DEXTERITY = 4;

class Scroll : public Item{
public:
    Scroll(Dungeon* dg, int x, int y, int n);
    void effect(std::string& msg);
    virtual void placeItem(int x, int y);
private:
    Player* p;
};

#endif // SCROLL_H