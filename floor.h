#ifndef FLOOR_H
#define FLOOR_H

#include <vector>
#include <memory>
#include "cell.h"   
#include "chamber.h"
#include "player.h"
#include "enemy.h"
#include "gold.h"
#include "potion.h"


class Floor {
    int level;
    std::shared_ptr<Player> player;
    std::vector<std::vector<std::shared_ptr<Cell>>> grid;
    std::vector<std::unique_ptr<Chamber>> chambers;
    PRNG prng;

    // spawn player to a random position
    void setPlayer();

    // spawn the stair to a random position
    void setStair();

    // spawn the dragon to somewhere near the DragonHoard
    shared_ptr<Dragon> spawnDragon(int x, int y, int chamberIndex);

    // spawn the potion to a random position 
    void spawnPotion();

    // spawn the treasure to a random position 
    void spawnTreasure();

    // spawn the enemy to a random position
    void SpawnEnemies();

    // choose a random number from 1 to range 
    int chooseRandomNumber(int range);

public:
    Floor(int level, std::shared_ptr<Player> player, const std::string &filename);
    ~Floor();

    // print the mao of current floor 
    void showFloor() const;

    // initialize the floor (spawn everything to the grid)
    void initializeFloor();

    // move whatever on the "from " cell to "to" cell
    void moveBetweenCell(std::shared_ptr<Cell> from, std::shared_ptr<Cell> to, string & action);

    // check if (x, y) position is at the stair's position 
    bool stairReached(int x, int y) const;
    
    // player attack the enemy 
    void attackEnemy(int xNew, int yNew, std::string & action);

    // player use the potion 
    void usePotion(int xNew, int yNew, std::string & potion);

    void seesPotion(int x, int y, string & action);

    std::shared_ptr<Cell> getCell(int x, int y);

    void moveOneEnemy(int x, int y, string & action);

    void moveAllEnemies(string & action);

    bool doorwayReached(int x, int y) const;
};

#endif // FLOOR_H
