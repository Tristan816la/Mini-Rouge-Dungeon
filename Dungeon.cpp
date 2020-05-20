#include "Dungeon.h"
#include "utilities.h"
#include "Player.h"
#include "SnakeWoman.h"
#include "Weapon.h"
#include "Scroll.h"
#include "Goblin.h"
#include "Dragon.h"
#include "Bogeyman.h"
#include <iostream>
#include <list>
#include <vector>
#include <cmath>
using namespace std;
Dungeon::Dungeon(int l) : level(l){}
vector<Dungeon::Room> Dungeon::roomGenerator() {
    // Select six non-overlapping regions to generate random-size rooms
    vector<Dungeon::Room> tempR;

    int L = randInt(2,5); int R = L + randInt(8,13-L);
    int U = randInt(2,6); int D = U + randInt(4,10-U);
    Coord UL1(L, U); Coord LR1(R, D);
    Room first(UL1, LR1);
    tempR.push_back(first);

    L = randInt(31,47); R = L + randInt(8,55-L);
    U = randInt(2,6); D = U + randInt(4,10-U);
    Coord UL2(L, U); Coord LR2(R, D);
    Room second(UL2, LR2);
    tempR.push_back(second);

    L = randInt(58,60); R = L + randInt(8,68-L);
    U = randInt(2,6); D = U + randInt(4,10-U);
    Coord UL3(L, U); Coord LR3(R, D);
    Room third(UL3, LR3);
    tempR.push_back(third);

    L = randInt(3,5); R = L + randInt(8,13-L);
    U = 12; D = U + 4;
    Coord UL4(L, U); Coord LR4(R, D);
    Room fourth(UL4, LR4);
    tempR.push_back(fourth);

    L = randInt(15,21); R = L + randInt(8,29-L);
    U = randInt(2,12); D = U + randInt(4,16-U);
    Coord UL5(L, U); Coord LR5(R, D);
    Room fifth(UL5, LR5);
    tempR.push_back(fifth);

    L = randInt(35,59); R = L + randInt(8,67-L);
    U = 12; D = U + 4;
    Coord UL6(L, U); Coord LR6(R, D);
    Room sixth(UL6, LR6);
    tempR.push_back(sixth);
    return tempR;
}
char Dungeon::getNode(int x, int y) const{
    return nodes[y][x];
}
void Dungeon::teleportPlayer(){
    Coord a = emptyNodes[randInt(emptyNodes.size())];
    int x = a.x; int y = a.y;
    setNode(x,y,'@');
    p->set_x(x); p->set_y(y);
}
Item* Dungeon::get_item(int x, int y) const{
    for(Item* i : items){
        if (i->get_x() == x && i->get_y() == y)
        return i;
    }
    exit(1); // if have error, g32 requires
}
char Dungeon::getItem(int x, int y) const{
    return itemLayer[y][x];
}
bool Dungeon::swapNode(int x1, int y1, int x2, int y2){
    std::swap(nodes[y1][x1],nodes[y2][x2]);
    return true; // for now
}
bool Dungeon::hasMonster(int x, int y) const{
    return (nodes[y][x] == 'B' || nodes[y][x] == 'S' || nodes[y][x] == 'D' || nodes[y][x] == 'G');
}
Monster* Dungeon::getMonster(int x, int y) const{
    for(Monster* i : monsters){
        if(i->get_x() == x && i->get_y() == y)
            return i;
    }
    exit(1); // shouldn't be called, g32 requires
}
void Dungeon::shuffle(int a[]){ // Using Fisher-Yates shuffle
    for(int i = 5; i > 0; i--){
        int j = randInt(0,i);
        std::swap(a[i],a[j]);
    }
}
Player* Dungeon::getPlayer() const{return p;}
void Dungeon::setNode(int x, int y, char c){nodes[y][x] = c;}
void Dungeon::setItem(int x, int y, char c){itemLayer[y][x] = c;}
void Dungeon::addItem(Item* i){items.push_back(i);}
void Dungeon::realGenerate(){
    // Put every node the wall and make every node in the itemLayer blank 
    for (int i = 0; i < MAX_ROW; i++){
        for (int j = 0; j < MAX_COL; j++){
            nodes[i][j] = '#';
            itemLayer[i][j] = ' ';
        }
    }
    // Delete every items in the previous floor
    if(level != 0) deleteGround();

    monsters.resize(randInt(2, 5*(level+1)+1));
    vector<Room> tempRooms = roomGenerator();
    vector<Room> rooms; 
    rooms.resize(randInt(4,6));

    //Shuffle 1-6 and select 4-6 rooms with these random indices
    int rands[6] = {0,1,2,3,4,5}; shuffle(rands);
    for (int i = 0; i < rooms.size(); i++){
        rooms[i] = tempRooms[rands[i]];
    }

    // Check each room, make nodes " "
    for (vector<Room> :: iterator i = rooms.begin(); i != rooms.end(); i++){
        for(int j = ((i->upperLeft).x); j < ((i->lowerRight).x); j++){
            for(int k = ((i->upperLeft).y); k < ((i->lowerRight).y);k++){
                nodes[k][j] = ' ';
                emptyNodes.push_back(Coord(j,k));
            }
        }
    }

    corridorGenerator(rooms);

    if (level==0){ // 0 level, generate player
        int playerChoice = randInt(0, emptyNodes.size()-1);
        p = new Player(emptyNodes[playerChoice].x,emptyNodes[playerChoice].y, this);
        emptyNodes.erase(emptyNodes.begin()+playerChoice);
    }else{
        updateEmptyNodes();
        teleportPlayer();
        updateEmptyNodes(); // since we reset player's position, emptyNodes got changed
    }
}
void Dungeon::corridorGenerator(vector<Dungeon::Room>& a){
    for(int j = 1; j < a.size(); j++){
        int startX = a[j].upperLeft.x + randInt(1,2); 
        int startY = a[j].upperLeft.y + randInt(1,2);
        int endX = a[j-1].lowerRight.x- randInt(2,3);
        int endY= a[j-1].lowerRight.y- randInt(2,3);
        while (startX != endX){
            (startX > endX) ? startX-- : startX++;        
            nodes[startY][startX] = ' ';
            emptyNodes.push_back(Coord(startX,startY));
        }
        while (startY != endY){
            (startY > endY) ? startY-- : startY++;        
            nodes[startY][startX] = ' ';
            emptyNodes.push_back(Coord(startX,startY));
        }
    }    
}
void Dungeon::deleteGround(){
    for(auto i : monsters){ // first delete the moster's drop, then itself
        i->deleteMonsterDrop();
        delete i;
    }
    for(auto i : items){
        delete i;
    } // Clear vectors so size is 0 and no content in them
    monsters.clear();
    items.clear();
}
void Dungeon::deleteItem(Item* a){
    for(int i = 0; i < items.size(); i++){
        if(items[i] == a){
            items.erase(items.begin()+i);
            i--;
        }
    }
}
Dungeon::~Dungeon(){
    deleteGround();
    delete p;
}
void Dungeon::updateMonster(){
    for(int i= 0; i < monsters.size();i++){
        if(monsters[i]->diedandDrop()){
            delete monsters[i];
            monsters.erase(monsters.begin()+i);
            i--;
        }
    }
}
void Dungeon::display() {
    updateMonster();
    updateEmptyNodes();
    for (int i = 0; i < MAX_ROW; i++){
        for (int j = 0; j < MAX_COL; j++){
            if (nodes[i][j] == ' ' && itemLayer[i][j] != ' '){
                cout << itemLayer[i][j];
            }
            else
                cout << nodes[i][j];
        }
        cout << endl;
    }
    cout << "Dungeon Level: " << level << ", Hit points: " << p->get_hp() << ", Armor: " 
    << p->get_armor() << ", Strength: " << p->get_strength() << ", Dexterity: "  << 
    p->get_dexterity() << endl << endl;
}
void Dungeon::monsterGenerator(){
    int* monsterChoices = new int[monsters.size()];
    // Generate monsters' number of choices
    for (int i = 0; i < monsters.size(); i++){
        int monsterChoice = randInt(0, emptyNodes.size()-1);
        monsterChoices[i] = monsterChoice;
        emptyNodes.erase(emptyNodes.begin()+ monsterChoices[i]);
    }
    for (int i = 0; i < monsters.size(); i++){
        int rand; Monster* temp; 
        if(level <= 1) rand = randInt(0,1);
        if(level == 2) rand = randInt(0,2);
        if(level >= 3) rand = randInt(0,3);
        if (rand==0)
            temp = new SnakeWoman(p,this,emptyNodes[monsterChoices[i]].x,emptyNodes[monsterChoices[i]].y);
        if (rand==1)
            temp = new Goblin(p,this,emptyNodes[monsterChoices[i]].x,emptyNodes[monsterChoices[i]].y);
        if (rand==2)
            temp = new Bogeyman(p,this,emptyNodes[monsterChoices[i]].x,emptyNodes[monsterChoices[i]].y);
        if (rand==3)
            temp = new Dragon(p,this,emptyNodes[monsterChoices[i]].x,emptyNodes[monsterChoices[i]].y);
        monsters[i] = temp;
    }
    delete[] monsterChoices;
}
void Dungeon::nextGenerator(){
    if(level <= 3){
    int stepChoice = randInt(0,emptyNodes.size()-1);
    setItem(emptyNodes[stepChoice].x,emptyNodes[stepChoice].y,'>');
    emptyNodes.erase(emptyNodes.begin() + stepChoice);
    }else{
        int trophyChoice = randInt(0,emptyNodes.size()-1);
        setItem(emptyNodes[trophyChoice].x,emptyNodes[trophyChoice].y,'&');
        emptyNodes.erase(emptyNodes.begin()+trophyChoice);
    }
}
void Dungeon::itemGenerator(){
    items.resize(randInt(2,3));
    int* itemChoices = new int[items.size()];
    for (int i = 0; i < items.size(); i++){
        int itemChoice = randInt(0, emptyNodes.size()-1);
        itemChoices[i] = itemChoice;
        emptyNodes.erase(emptyNodes.begin() + itemChoice);
    }
    for (int i = 0; i < items.size(); i++){
        int option = randInt(0,1);
        Item* temp;
        if (option == 0)
            temp = new Weapon(this,emptyNodes[itemChoices[i]].x,emptyNodes[itemChoices[i]].y,randInt(0,2));    
        else
            temp = new Scroll(this,emptyNodes[itemChoices[i]].x,emptyNodes[itemChoices[i]].y,randInt(1,4));
        items[i] = temp;
    }
    for (Item* i : items){
        i->placeItem(i->get_x(),i->get_y());
    }
    delete[] itemChoices;
}
void Dungeon::reSetGoblinTable(){
    for(int i = 0; i < MAX_COL; i++){
        for(int j = 0; j < MAX_ROW; j++){
            p->setGoblinMap(i,j,9999);
        }
    }
}
void Dungeon::start(){ // Rewrite when we consider different types of monsters
    clearScreen();
    level++;
    realGenerate();
    reSetGoblinTable();
    nextGenerator();
    monsterGenerator();
    itemGenerator();
}

void Dungeon::moveAllMonsters(){
    for(Monster* i : monsters)
        i->move();
}
void Dungeon::MonstersAttack(std::vector<string>& msgs){
    for(int i = 0; i < monsters.size(); i++){
        if(monsters[i]->distance() == 1){
            string temp;
            monsters[i]->fightM(temp);
            msgs.push_back(temp);
        }
    }
}
void Dungeon::updateEmptyNodes(){
    vector<Coord> temp;
    for(int y = 0; y < MAX_ROW; y++){
       for (int x = 0; x < MAX_COL; x++){
           if (nodes[y][x] == ' '){
               temp.push_back(Coord(x,y));
           }
       }
    }
    emptyNodes = temp;
}
