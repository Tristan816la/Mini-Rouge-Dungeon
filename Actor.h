#ifndef ACTOR_H
#define ACTOR_H
#include <iostream>
class Weapon;
class Dungeon;
class Actor{
    public:
        Actor(int hp, int ar, int str, int de, int sl,int x, int y, int mh, Dungeon* d, Weapon* w);
        virtual ~Actor();
        bool ableMove(int x, int y) const;
        bool fight(std::string& msg, Actor* def);

        // Accessor
        int get_x() const;
        int get_y() const;
        int get_hp() const;
        int get_max_hp() const;
        int get_armor() const;
        int get_strength() const;
        int get_dexterity() const;
        int get_sleep() const;
        Dungeon* get_dungeon() const;
        Weapon* get_weapon() const;
        
        // Mutator
        void set_x(int x);
        void set_y(int y);
        void set_hp(int h);
        void set_max_hp(int n);
        void set_armor(int a);
        void set_strength(int s);
        void set_dexterity(int d);
        void set_sleep(int s);
        void set_weapon(Weapon* w);
        

    private:
        int hp; // Hit points
        int max_hp;
        int armor;
        int strength;
        int dexterity;
        int sleep;
        int x; 
        int y;
        
        Dungeon* dg;
        Weapon* wp;
};

#endif // ACTOR_H