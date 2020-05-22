#include "Goblin.h"
#include "Dungeon.h"
#include "Player.h"
#include "Weapon.h"
#include "utilities.h"
using namespace std;

Goblin::Goblin(Player* p,  Dungeon* dg, int x, int y): 
Monster(p,dg,new Weapon(dg,x,y,randInt(MAGIC_FANG_OF_SLEEP,MAGIC_AXE)),
new Weapon(dg,x,y,SHORT_SWORD),"Goblin", (1.0/3),
randInt(15,20),1,3,1,x,y){
    dg->setNode(x,y,'G');
}

bool Goblin::move(){
    if(getPlayer()->getDistance(get_x(),get_y()) <= getPlayer()->getGoblinSmellDistance())
        return goblinMove();
    return false;
}

bool Goblin::fightM(string& msg){
    if(get_sleep() > 0){set_sleep(get_sleep()-1); return false;}
    msg += "the Goblin " + get_weapon()->getActionName() + " at the Player";
    return Monster::fightM(msg);
}

bool Goblin::goblinMove(){
    //Move only when the num on goblin map on a specific direction
    // is smaller than the distance of goblin's current distance
    int distance = getPlayer()->getDistance(get_x(),get_y());
    if(get_sleep() > 0) {set_sleep(get_sleep()-1); return false;} 
    if(ableMove(get_x()+1,get_y()) && getPlayer()->getDistance(get_x()+1,get_y()) < distance){
        get_dungeon()-> swapNode(get_x()+1,get_y(),get_x(),get_y());
        set_x(get_x()+1); return true;
    }else if(ableMove(get_x()-1,get_y()) && getPlayer()->getDistance(get_x()-1,get_y()) < distance){
        get_dungeon()-> swapNode(get_x()-1,get_y(),get_x(),get_y());
        set_x(get_x()-1); return true;
    }else if(ableMove(get_x(),get_y()+1) && getPlayer()->getDistance(get_x(),get_y()+1) < distance){
        get_dungeon()-> swapNode(get_x(),get_y()+1,get_x(),get_y());
        set_y(get_y()+1); return true;
    }else if(ableMove(get_x(),get_y()-1) && getPlayer()->getDistance(get_x(),get_y()-1) < distance){
        get_dungeon()-> swapNode(get_x(),get_y()-1,get_x(),get_y());
        set_y(get_y()-1); return true;
    }
    return false;
}

