// Gameflow.h
#ifndef GAMEFLOW_H
#define GAMEFLOW_H

#include <iostream>
#include "string.h"
#include "player.h"
#include "floor.h"

using namespace std;
class GameFlow {
public:
    int level;
    std::shared_ptr<Player> player;
    std::shared_ptr<Floor> floor;
    bool enemyMoving;

    // constructor 
    GameFlow();

    // destructor 
    ~GameFlow();

    // initialize the game: 
    // 1, generate the floor 
    // 2, call initialize floor to spawn everything 
    void newFloor( int, std::shared_ptr<Player>, const std::string&, bool empty );

    // if f presseed, if enemymove == true, set enemy movement to fail; vice versa 
    // set all enemy in the enemy list to false 
    void enemyMovement();
    
    // update the x, y position according to the command given
    // make change to action according to str move/attack/usepotion
    void updatePosition(string command, int &xNew, int &yNew, std::string &action, const std::string str);
    
    void attackPlayer(int x, int y, std::string & action, bool& b); 

    // check if the player's hp < 0 or not
    void checkPlayerDeath(bool & start);

    // check if the command is a valid direction (one of no so ea we etc)
    bool validDirection(std::string command);

    // main game logic 
    void startGame(std::string filename = "emptyfloor.txt");
};

#endif 
