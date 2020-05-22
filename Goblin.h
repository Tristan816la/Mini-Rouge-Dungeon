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
    virtual bool fightM(std::string& msg);
    bool goblinMove();
private:
};


#endif //GOBLIN_H