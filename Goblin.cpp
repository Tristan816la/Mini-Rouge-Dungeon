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
        return makeMove();
    return false;
}

void Goblin::fightM(string& msg){
    msg += "the Goblin " + get_weapon()->getActionName() + " at the Player";
    Monster::fightM(msg);
}

