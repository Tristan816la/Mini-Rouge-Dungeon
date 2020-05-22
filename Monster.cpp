#include "Monster.h"
#include "Player.h"
#include "Dungeon.h"
#include "Weapon.h"
#include "utilities.h"
#include <cmath>
using namespace std;
Monster::Monster(Player* p, Dungeon* dg, Item* d, Weapon* wp, 
string name,double dropP,int hp,int ar, int str, int de,int x, int y) 
:Actor(hp,ar,str,de,0,x,y,hp,dg,wp){this->p = p; drop = d; this->name = name; dropProb = dropP;}
Monster::~Monster(){} 
//Distance is the absolute sum of x and y
int Monster::distance() const{return abs(get_x() - p->get_x()) + abs(get_y() - p->get_y());}
Player* Monster::getPlayer() const {return p;}
Item* Monster::getDrop() const {return drop;}
std::string Monster::getName() const{return name;}
void Monster::dropUpdate(){ // update the drop to the monster's position
    drop->set_x(get_x());
    drop->set_y(get_y());
}
bool Monster::checkMove(int x, int y) const{
    if(!ableMove(x,y)) return false;
    if(abs(x-p->get_x()) + abs(y - p->get_y()) < distance()) return true;
    return false;
}
bool Monster::move() {exit(1);} // Monster is not an ABS, so just leave it here
bool Monster::fightM(string& msg){ // the monster needs to be currently alive after player's attack
    if(get_hp() > 0 && get_sleep() == 0) 
        return fight(msg,p);
    return false;
}
bool Monster::makeMove(){// Cannot make any move if slept
    if(get_sleep() > 0) {set_sleep(get_sleep()-1); return false;} 
    if(checkMove(get_x()+1,get_y())){
        get_dungeon()-> swapNode(get_x()+1,get_y(),get_x(),get_y());
        set_x(get_x()+1); return true;
    }else if(checkMove(get_x()-1,get_y())){
        get_dungeon()-> swapNode(get_x()-1,get_y(),get_x(),get_y());
        set_x(get_x()-1); return true;
    }else if(checkMove(get_x(),get_y()+1)){
        get_dungeon()-> swapNode(get_x(),get_y()+1,get_x(),get_y());
        set_y(get_y()+1); return true;
    }else if(checkMove(get_x(),get_y()-1)){
        get_dungeon()-> swapNode(get_x(),get_y()-1,get_x(),get_y());
        set_y(get_y()-1); return true;
    }
    return false;
}
bool Monster::diedandDrop(){ // return true if monster is died, set the drop
    if(get_hp() <= 0){
        get_dungeon()->setNode(get_x(),get_y(),' ');
        if(trueWithProbability(dropProb)){
            dropUpdate(); 
            drop->placeItem(get_x(),get_y());
            get_dungeon()->addItem(drop); 
        }
        else
            delete drop;
        return true;
    }
    return false;
}
void Monster::deleteMonsterDrop(){delete drop;}
