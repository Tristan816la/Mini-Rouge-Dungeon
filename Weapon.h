#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"
#include <iostream>
class Dungeon;
const int SHORT_SWORD = 0;
const int LONG_SWORD = 1;
const int MACE = 2;
const int MAGIC_FANG_OF_SLEEP = 3;
const int MAGIC_AXE = 4;

class Weapon : public Item{
    public:
        Weapon(Dungeon*dg, int x, int y, int n);
        Weapon(const Weapon& a); 
        virtual void placeItem(int x, int y);
        int getDexterityBonus() const;
        int getDamage() const;
        std::string getActionName() const;

    private:
        std::string actionName;
        int d_b; // Dexterity Bonus
        int damage;
};

#endif // WEAPON_H