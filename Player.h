#ifndef PLAYER_H
#define PLAYER_H
#include "Actor.h"
#include <iostream>
#include <vector>
class Dungeon;
class Menu;
class Weapon;
class Monster;
class Player : public Actor{
    public:
        Player(int x, int y, Dungeon* dg);
        ~Player();

        //For Goblin's detection
        void dfsGoblinLayout(int x, int y, int smellDistance);
        int getDistance(int x, int y) const;
        int getGoblinSmellDistance() const;
        void setGoblinsmellDistance(int a);
        void setGoblinMap(int x, int y, int c);

        //Identify player's key and make corresponding actions
        bool action(std::vector<std::string>& msg); 
        bool move(char a, std::string& msg);
        void wearWeapon(Weapon* a, std::string& msg);
        void fightP(std::string& msg, Monster* m);
        void moveTo(int x, int y);
        bool win() const;
        bool grab(std::string& msg); // 'g'
        void inspect() const; // 'i'
        void utilize(char c,std::string& msg); // 'r' or 'w'
        void cheat(); // 'c'

    private:
        int GoblinsmellDistance;
        int GoblinMap[18][70];
        Menu* menu;
        bool success;
};


#endif// PLAYER_H
