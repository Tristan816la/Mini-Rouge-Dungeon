#include "Item.h"
#include "Dungeon.h"
Item::Item(Dungeon* d, int x, int y) : dg(d),x(x),y(y){}

Item::~Item(){};

std::string Item::get_name() const{return name;}
void Item:: set_name(std::string a){name = a;}
bool Item::ablePlace(int x, int y) const{
    return dg->getNode(x,y) == ' '&& dg->getItem(x,y) == ' ';
}

//Acessors
Dungeon* Item::get_dungeon() const {return dg;}
int Item:: get_x() const {return x;}
int Item:: get_y() const {return y;}

//Mutators
void Item::set_x(int a){x = a;}
void Item::set_y(int a){y = a;}