#include "Bogeyman.h"
#include "Dungeon.h"
#include "Player.h"
#include "Weapon.h"
#include "utilities.h"
using namespace std;

Bogeyman::Bogeyman(Player* p,  Dungeon* dg, int x, int y): 
Monster(p,dg,new Weapon(dg,x,y,MAGIC_AXE),new Weapon(dg,x,y,SHORT_SWORD), "Bogeyman",
0.1,randInt(5,10),2,
randInt(2,3),randInt(2,3),x,y){
    dg->setNode(x,y,'B');
}
bool Bogeyman::move(){
    if (distance() <= 5){ 
       return makeMove();
    }
    return false;
}
void Bogeyman::fightM(string& msg){
    msg += "the Bogeyman " + get_weapon()->getActionName() + " at the Player";
    Monster::fightM(msg);
}

