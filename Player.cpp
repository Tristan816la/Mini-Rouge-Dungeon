#include <iostream>
#include "Player.h"
#include "Actor.h"
#include "utilities.h"
#include "Menu.h"
#include "Scroll.h"
#include "Weapon.h"
#include "Dungeon.h"
#include "SnakeWoman.h"
#include "Goblin.h"
#include "Dragon.h"
#include "Bogeyman.h"
using namespace std;
Player::Player(int x, int y, Dungeon* dg): 
Actor(20,2,2,2,0,x,y,20,dg,new Weapon(dg,x,y,SHORT_SWORD)){
    dg->setNode(x,y,'@');
    menu = new Menu(this);
    success = false;
}
Player::~Player(){
    delete menu;
}
void Player::dfsGoblinLayout(int x, int y, int s){
    GoblinMap[y][x] = s;
    if (s == GoblinsmellDistance)
        return;
    if (get_dungeon()->getNode(x,y+1) != '#'){
        if(GoblinMap[y+1][x] == 9999 || GoblinMap[y+1][x] > s+1)
            dfsGoblinLayout(x,y+1,s+1);
    }
    if (get_dungeon()->getNode(x,y-1) != '#'){
        if(GoblinMap[y-1][x] == 9999 || GoblinMap[y-1][x] > s+1)
            dfsGoblinLayout(x,y-1,s+1);
    }
    if (get_dungeon()->getNode(x+1,y) != '#'){
        if(GoblinMap[y][x+1] == 9999 || GoblinMap[y][x+1] > s+1)
            dfsGoblinLayout(x+1,y,s+1);
    }
    if (get_dungeon()->getNode(x-1,y) != '#'){
        if(GoblinMap[y][x-1] == 9999 || GoblinMap[y][x-1] > s+1)
            dfsGoblinLayout(x-1,y,s+1);
    }
}
void Player::moveTo(int x, int y){
    get_dungeon()->swapNode(get_x(),get_y(),x,y);
    set_x(x); set_y(y);
}
void Player::setGoblinMap(int x, int y, int c){
    GoblinMap[y][x] = c;
}
bool Player::move(char act, string& msg) {
    if (act == ARROW_LEFT){
        if(ableMove(get_x()-1,get_y()))
            moveTo(get_x()-1,get_y());
        else if(get_dungeon()->hasMonster(get_x()-1,get_y()))
            fightP(msg,get_dungeon()->getMonster(get_x()-1,get_y()));
        return true;
    }
    if (act == ARROW_RIGHT){
        if(ableMove(get_x()+1,get_y()))
            moveTo(get_x()+1,get_y());
        else if(get_dungeon()->hasMonster(get_x()+1,get_y()))
            fightP(msg,get_dungeon()->getMonster(get_x()+1,get_y()));
        return true;
    }
    if (act == ARROW_DOWN){
        if(ableMove(get_x(),get_y()+1))
            moveTo(get_x(),get_y()+1);
        else if(get_dungeon()->hasMonster(get_x(),get_y()+1))
            fightP(msg,get_dungeon()->getMonster(get_x(),get_y()+1));
        return true;
    }
    if (act == ARROW_UP){
        if(ableMove(get_x(),get_y()-1))
            moveTo(get_x(),get_y()-1);
        else if(get_dungeon()->hasMonster(get_x(),get_y()-1))
            fightP(msg,get_dungeon()->getMonster(get_x(),get_y()-1));
        return true;
    }
    return false; 
}
void Player::fightP(string& msg, Monster* m){
    msg = "Player " + get_weapon()->getActionName() + " at the " + m->getName(); 
    fight(msg,m);
    // When the player is wielding a magic fang
    if(m->get_hp() > 0 && get_weapon()->get_name() == "magic fangs of sleep" && trueWithProbability(0.2)){
        msg = msg.substr(0,msg.size()-1);
        m->set_sleep(max(m->get_sleep(),randInt(2,6)));
        string name;
        msg += (", putting the " + m->getName() + " to sleep.");
    }
}
void Player::cheat(){
    set_hp(50);
    set_strength(9);
}
bool Player::win() const {return success;}
bool Player::grab(string& msg){
    if(menu->size() > 25){msg = "Your knapsack is full; you can't pick that up."; return false;}
    if(get_dungeon()->getItem(get_x(),get_y()) != ' ' && get_dungeon()->getItem(get_x(),get_y()) != '>' ){
        if(get_dungeon()->getItem(get_x(),get_y()) == '&'){
            msg = "You pick up the golden idol\nCongratulations, you won!";
            success = true; return true;
        }
        get_dungeon()->setItem(get_x(),get_y(),' ');
        menu->addItem(get_dungeon()->get_item(get_x(),get_y()));
        msg = "You pick up " + get_dungeon()->get_item(get_x(),get_y())->get_name();
        get_dungeon()->deleteItem(get_dungeon()->get_item(get_x(),get_y()));
        return true;
    }
    return false; // if nothing could be picked up
}
void Player::wearWeapon(Weapon* a, string& msg){
    set_weapon(a);
    msg = "You are wielding " + a->get_name();
}

void Player::inspect() const {getCharacter();}
void Player::utilize(char c, string& msg){
    char t = getCharacter(); int index = int(t-'a');
    if (index > menu->size()- 1 || index < 0 || index > 26) return; // avoid overflow
    if(c == 'r'){
        Scroll* temp = dynamic_cast<Scroll*>(menu->getItem(index));
        if(temp != nullptr) {temp->effect(msg); menu->removeItem(index);}
        else msg = "You can't read a " + menu->getItem(index)->get_name();
    }else{
        Weapon* temp = dynamic_cast<Weapon*>(menu->getItem(index));
        if(temp != nullptr) wearWeapon(temp, msg);
        else msg = "You can't wield " + menu->getItem(index)->get_name();
    }
}
bool Player::action(vector<string>& msg) {
    if(trueWithProbability(0.1) && get_hp() < get_max_hp()) {set_hp(get_hp()+1);}
    char act = getCharacter();
    if(get_sleep() > 0) {set_sleep(get_sleep()-1); return false;} // Cannot make any move if slept
    string message;
    if (act == ARROW_DOWN || act == ARROW_LEFT || act == ARROW_RIGHT || act == ARROW_UP)
        move(act,message);
    else if (act == 'q')
        return true;
    else if (act == 'c')
        cheat();
    else if (act == 'g')
        grab(message);
    else if (act == 'i' || act == 'r' || act == 'w'){
        menu->displayMenu();
        act == 'i' ? inspect() : utilize(act,message);
    }
    else if (act == '>'){
        if(get_dungeon()->getItem(get_x(),get_y()) == '>')
            get_dungeon()->start();
    }
    dfsGoblinLayout(get_x(),get_y(), 0);
    if(!message.empty()) msg.push_back(message);
    return false;
}
void Player::setGoblinsmellDistance(int a){GoblinsmellDistance = a;}
int Player::getGoblinSmellDistance() const{return GoblinsmellDistance;}
int Player::getDistance(int x, int y) const{return GoblinMap[y][x];}



