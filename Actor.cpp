#include "Actor.h"
#include "Dungeon.h"
#include "Weapon.h"
#include "utilities.h"
#include <cmath>
using namespace std;
Actor :: Actor(int hp, int ar, int str, int de, int sl,int x, int y, int mh, Dungeon* d, Weapon* w) :
hp(hp),armor(ar),strength(str),dexterity(de), sleep(sl), x(x), y(y),max_hp(mh),dg(d),wp(w)
{}
Actor:: ~Actor(){delete wp;}
int Actor::get_x() const {return x;}
int Actor::get_y() const {return y;}
int Actor::get_hp() const {return hp;}
int Actor::get_max_hp() const {return max_hp;}
int Actor:: get_armor() const {return armor;}
int Actor:: get_strength() const {return strength;}
int Actor:: get_dexterity() const {return dexterity;}
int Actor:: get_sleep() const {return sleep;}
Weapon* Actor::get_weapon() const {return wp;}
void Actor::set_x(int a) {
    if (x >= 0 && x < 70){
        x = a;
    }
}
void Actor::set_y(int a) {
    if (y >= 0 && y < 18){
        y = a;
    }
}
void Actor::set_weapon(Weapon* w){wp = w;}
void Actor::set_hp(int n) {hp = n;}
void Actor::set_max_hp(int n){
    if (n > 0 && n < 100){
        max_hp = n;
    }
}
void Actor::set_armor(int s){
    if (s > 0 && s < 100){
        armor = s;
    }
}
void Actor::set_dexterity(int d){
    if (d > 0 && d < 100){
        dexterity = d;
    }
}
void Actor::set_sleep(int s){sleep = s;}
void Actor::set_strength(int s){
     if (s > 0 && s < 100){
        strength = s;
    }
}
Dungeon* Actor::get_dungeon() const {return dg;}
bool Actor::ableMove(int x, int y) const{
    if(y < 0 || y > 17 || x < 0 || x > 69) return false;
    return dg->getNode(x,y) == ' ';
}
void Actor::fight(std::string& msg, Actor* def){
    if(def->hp > 0){
        int attackerPoints = dexterity+ wp->getDexterityBonus();
        int defenderPoints = def->get_dexterity() + def->get_armor();
        if(randInt(1,attackerPoints) >= randInt(1, defenderPoints)){
            def->set_hp(def->get_hp()-randInt(0,strength+ wp->getDamage()-1));
            if(def->get_hp() <= 0){msg += " dealing a final blow."; return;}
            else 
                msg +=" and hits.";
        }
        else
            msg +=" and misses.";
    }
}
