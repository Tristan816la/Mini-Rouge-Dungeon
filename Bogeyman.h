#ifndef BOGEYMAN_H
#define BOGEYMAN_H
#include <iostream>
#include "Monster.h"
class Player;
class Dungeon;
class Bogeyman : public Monster{
public: 
    Bogeyman(Player* p,  Dungeon* dg, int x, int y);
    virtual bool move();
    virtual bool fightM(std::string& msg);
private:
};
#endif // BOGEYMAN_H