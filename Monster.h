#ifndef MONSTER_H
#define MONSTER_H
#include "Actor.h"
#include <iostream>
class Player;
class Dungeon;
class Weapon;
class Item;

class Monster : public Actor{
    public:
        Monster(Player* p, Dungeon* dg, Item* d, Weapon* wp, std::string name, 
        double dropP,int hp, int ar, int str, int de, int x, int y);
        virtual ~Monster();
        virtual bool move();
        void deleteMonsterDrop();// delete drop
        virtual bool fightM(std::string& msg);
        void dropUpdate(); 
        bool checkMove(int x, int y) const; // check if it is able and optimal for a monster to move
        int distance() const; // distance between monster and player
        bool makeMove(); // make move when in certain distance, called by snakewoman and Bogeyman
        bool diedandDrop();

        Item* getDrop() const;
        std::string getName() const;  
        Player* getPlayer() const;
        
    private:
        Item* drop;
        double dropProb;
        Player* p;
        std::string name;
};

#endif // MONSTER_H