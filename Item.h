#ifndef ITEM_H
#define ITEM_H
#include<iostream>
class Dungeon;
class Item{
public:
    Item(Dungeon* dg, int x, int y);
    Item(const Item&);
    virtual ~Item();
    bool ablePlace(int x, int y) const;
    virtual void placeItem(int x, int y) = 0; 

    //Acessors
    Dungeon* get_dungeon() const;
    int get_x() const;
    int get_y() const;
    std::string get_name() const;

    //Mutators
    void set_name(std::string a);
    void set_x(int x);
    void set_y(int y);

private:
    std::string name;
    Dungeon* dg;
    int x;
    int y;
};

#endif // ITEM_H