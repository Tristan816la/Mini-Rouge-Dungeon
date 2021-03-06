#include "Dragon.h"
#include "Dungeon.h"
#include "Player.h"
#include "Weapon.h"
#include "Scroll.h"
#include "utilities.h"
using namespace std;

Dragon::Dragon(Player* p,  Dungeon* dg, int x, int y): 
Monster(p,dg,new Scroll(dg,x,y,randInt(0,4)),new Weapon(dg,x,y,LONG_SWORD),"Dragon",
1,randInt(20,25),4,4,4,x,y){
    dg->setNode(x,y,'D');
}

bool Dragon::move(){ // Dragon only regenerates hp and doesn't move
    if(trueWithProbability(0.1))
        set_hp(get_hp()+1);
    return false;
}

bool Dragon::fightM(string& msg){
    if(get_sleep() > 0){set_sleep(get_sleep()-1); return false;}
    msg += "the Dragon " + get_weapon()->getActionName()+ " at the Player";
    return Monster::fightM(msg);
}

