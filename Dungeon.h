#ifndef DUNGEON_H
#define DUNGEON_H
#include<vector>
#include<iostream>
const int MAX_ROW = 18;
const int MAX_COL = 70;
class Monster;
class Actor;
class Player;
class Item;

class Dungeon{
    public:
        Dungeon(int level);
        ~Dungeon();

        //Accessor
        char getNode(int x, int y) const; // get specific Node's character
        char getItem(int x, int y) const;
        Item* get_item(int x, int y) const; // get item in itemLayer
        Player* getPlayer() const;
        Monster* getMonster(int x, int y) const;

        //Mutator
        void setNode(int x, int y, char c);
        void setItem(int x, int y, char c);

        void display();
        bool swapNode(int x1, int y1, int x2, int y2);

        // call @ start of the game or @ the new floor
        void start(); 
        void moveAllMonsters();
        void MonstersAttack(std::vector<std::string>& a);

        bool hasMonster(int x, int y) const;
 
        void reSetGoblinTable();
        void addItem(Item* i);
        void deleteItem(Item* i);
        void updateMonster();
        void teleportPlayer();
        void deleteGround();


    private:
        struct Coord{
            Coord(){}
            Coord(int x, int y): x(x), y(y){}
            int x;
            int y;
        };

        struct Room {
            Room(){}
            Room(Coord uL, Coord lR) : upperLeft(uL), lowerRight(lR){}
            Coord upperLeft;
            Coord lowerRight;
        };

        //For room generation
        std::vector<Room> roomGenerator();
        void corridorGenerator(std::vector<Room>& a); 
        void shuffle(int arr[]);
        
        //Update Nodes status
        void updateEmptyNodes();
        void nextGenerator(); 
        void monsterGenerator();
        void itemGenerator();
        void realGenerate();

        std::vector<Coord> emptyNodes; // store empty nodes for rendering objects
        std::vector<Monster*> monsters;
        std::vector<Item*> items;

        char nodes[MAX_ROW][MAX_COL];
        char itemLayer[MAX_ROW][MAX_COL]; // A new layer to items
        int level;
        Player* p;
};




#endif // DUNGEON_H
