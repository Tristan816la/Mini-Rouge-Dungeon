#ifndef GOBLIN_H
#define GOBLIN_H
#include "Monster.h"
#include <iostream>
class Dungeon;
class Weapon;

class Goblin : public Monster{
public: 
    Goblin(Player* p,  Dungeon* dg, int x, int y);
    virtual bool move();
    virtual void fightM(std::string& msg);
private:
};


#endif //GOBLIN_H