#ifndef SNAKEWOMAN_H
#define SNAKEWOMAN_H
#include "Monster.h"
#include <iostream>
class Dungeon;
class Weapon;

class SnakeWoman : public Monster{
public: 
    SnakeWoman(Player* p,  Dungeon* dg, int x, int y);
    virtual bool move();
    virtual bool fightM(std::string& msg);
private:

};

#endif // SNAKEWOMAN_H