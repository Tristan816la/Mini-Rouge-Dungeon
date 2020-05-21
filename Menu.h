#ifndef MENU_H
#define MENU_H
#include<vector>
class Player;
class Item;
class Menu{
    public:
        Menu(Player* p);
        ~Menu();
        Item* getItem(int i) const;
        int size() const;

        void addItem(Item* i);
        void removeItem(int j);
        void displayMenu() const;

    private:
        std::vector<Item*> items;
        Player* pl;
};


#endif // MENU_H