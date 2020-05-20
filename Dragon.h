#ifndef DRAGON_H
#define DRAGON_H
#include "Monster.h"
#include <iostream>
class Dungeon;
class Weapon;

class Dragon : public Monster{
public: 
    Dragon(Player* p, Dungeon* dg, int x, int y);
    virtual bool move();
    virtual void fightM(std::string& msg);
private:
};

#endif // DRAGON_H