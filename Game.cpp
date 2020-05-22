// Game.cpp
#include "Game.h"
#include "utilities.h"
#include "Dungeon.h"
#include "Goblin.h"
#include <iostream>
#include "Player.h"
using namespace std;

// Implement these and other Game member functions you may have added.

Game::Game(int goblinSmellDistance){
    clearScreen();
    dg = new Dungeon(-1); // Start from -1 since start() has level++ in it
    dg->start();
    dg->getPlayer()->setGoblinsmellDistance(goblinSmellDistance);
}

Game::~Game(){delete dg;}
void Game::handleEnd()const{ // not quiting the game unless the player presses 'q'
    cout << "Press q to exit game." << endl;
    char end;
    do{
        end = getCharacter();
    } while(end !='q');    
}
void Game::play()
{
    dg->display();
    
    while(dg->getPlayer()->get_hp() > 0 && !dg->getPlayer()->win()){
        vector<string> messages;
        bool quit = dg->getPlayer()->action(messages); // action return true when user hit 'q'
        dg->updateMonster();
        dg->MonstersAttack(messages); // First attack then move
        dg->moveAllMonsters();
        if(quit) return; // use a quit design could call destructors normally
        clearScreen();

    //After everything, Dungeon should display
        dg->display();
        for(string i : messages)
            cout << i << endl;
    }
    handleEnd();
}

// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
