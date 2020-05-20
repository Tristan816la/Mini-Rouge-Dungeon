#include "SnakeWoman.h"
#include "Dungeon.h"
#include "Player.h"
#include "Weapon.h"
#include "utilities.h"
#include <cmath>
using namespace std;

SnakeWoman::SnakeWoman(Player* p,  Dungeon* dg, int x, int y): 
Monster(p,dg,new Weapon(dg,x,y,MAGIC_FANG_OF_SLEEP),
new Weapon(dg,x,y,MAGIC_FANG_OF_SLEEP), "the snakewoman",
0.3,randInt(3,6),3,2,3,x,y){
    dg->setNode(x,y,'S');
}
bool SnakeWoman::move(){
    if (distance() <= 3){ 
       return makeMove();
    }
    return false;
}
void SnakeWoman::fightM(string& msg){
    msg += "the Snakewoman " + get_weapon()->getActionName() + " at the Player";
    Monster::fightM(msg);
    if(getPlayer()->get_hp() > 0 && trueWithProbability(0.2)){
        getPlayer()->set_sleep(max(getPlayer()->get_sleep(),randInt(2,6)));
        msg = msg.substr(0,msg.size()-1); // delete '.' at the end
        msg += ", putting Player to sleep.";
    }
}

