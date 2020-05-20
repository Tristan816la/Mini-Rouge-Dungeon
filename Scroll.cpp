# include "Scroll.h"
# include "Dungeon.h"
# include "Player.h"
# include "utilities.h"
using namespace std;

Scroll::Scroll(Dungeon* dg, int x, int y, int n): Item(dg,x,y){
    p = dg->getPlayer();
    if (n == TELEPORTATION)
        set_name("a scroll called scroll of teleportation");
    if (n == IMPROVE_ARMOR)
        set_name("a scroll called scroll of improve armor");
    if (n == RAISE_STRENGTH)
        set_name("a scroll called scroll of raise strength");
    if (n == ENHANCE_HEALTH)
        set_name("a scroll called scroll of enhance health");
    if (n == ENHANCE_DEXTERITY)    
        set_name("a scroll called scroll of enhance dexterity");
}

void Scroll::effect(string& msg){
    msg = "You read the " + get_name().substr(2);
    if (get_name() == "a scroll called scroll of teleportation"){
        p->get_dungeon()->setNode(p->get_x(),p->get_y(),' ');
        p->get_dungeon()->teleportPlayer();
        msg += "\nYou feel your body wrenched in space and time.";
    }else if (get_name() == "a scroll called scroll of improve armor"){
        p->set_armor(p->get_armor()+ randInt(1,3));
        msg+="\nYour armor glows silver.";
    }else if (get_name() == "a scroll called scroll of raise strength"){
        p->set_strength(p->get_strength() + randInt(1,3));
        msg += "\nYour muscles bulge.";
    }else if (get_name() == "a scroll called scroll of enhance health"){
        p->set_max_hp(p->get_max_hp() + randInt(3,8));
        msg += "\nYou feel your heart beating stronger.";
    }else if (get_name() == "a scroll called scroll of enhance dexterity"){
        p->set_dexterity(p->get_dexterity() + 2);
        msg += "\nYou feel less of a klutz.";
    }
}

void Scroll::placeItem(int x, int y){
    if(ablePlace(x,y)){
        get_dungeon()->setItem(x,y,'?');  
    }
}