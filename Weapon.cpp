#include "Weapon.h"
#include "Dungeon.h"
using namespace std;

Weapon::Weapon(Dungeon* dg, int x, int y, int n) : Item(dg,x,y){
    if(n == SHORT_SWORD){
        set_name("short sword");
        damage = 2;
        d_b = 0;
        actionName = "slashes short sword";
    }else if(n == MACE){
        set_name("mace");
        damage = 2;
        d_b = 0;
        actionName = "swings mace";
    }else if(n == LONG_SWORD){
        set_name("long sword");
        damage = 4;
        d_b = 2;
        actionName = "swings long sword";
    }else if(n == MAGIC_AXE){
        set_name("magic axe");
        damage = 5;
        d_b = 5;
        actionName = "chops magic axe";
    }else if(n == MAGIC_FANG_OF_SLEEP){
        set_name("magic fangs of sleep");
        damage = 2;
        d_b = 3;
        actionName = "strikes magic fangs";
    }
}
void Weapon::placeItem(int x, int y){
    if(ablePlace(x,y)){
        get_dungeon()->setItem(x,y,')');   
    }
}
int Weapon::getDexterityBonus() const{return d_b;}
int Weapon::getDamage() const {return damage;}
string Weapon::getActionName() const{return actionName;}




