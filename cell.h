#ifndef CELL_H
#define CELL_H

#include <memory>

class Gold;
class Potion;
class Enemy;

class Cell {
    int x, y;
    char type; // wall, floorTile, passange, doorway (may be covered by displayChar)
    char displayChar; // the character on the top 
    bool isOccupied; // if a player/gold/enemy/posion/stair enter this cell
    std::shared_ptr<Gold> gold;
    std::shared_ptr<Potion> potion;
    std::shared_ptr<Enemy> enemy;
    bool isPlayer;
    bool isStair;
    bool hasMoved;

public:
    // constructor 
    Cell(int x, int y, char type);

    // return true if it has been occupied 
    bool itIsOccupied() const;

    // return ture if it is a doorway(+) or passange (#) or an empty floortile (.) (the player can step on these thing)
    // if the player steps on the stair, it automatically go to the next floor
    // so I dont include it here 
    // else, false 
    bool validPlayerPosition() const;

    // return true if it is an empty floorTile (.)
    // enemy can step here
    bool validPosition() const;

    //player is on this cell 
    void setPlayer();

    // stair is on this cell 
    void setStair();

    // an enemy is on this cell,
    // e is the pointer to the enemy
    // c refers to the type
    //: (H)uman, d(W)arf, (E)lf, (O)rc, (M)erchant, (D)ragon, Half(L)ing
    void setEnemy(std::shared_ptr<Enemy> e, char c);

    // if a gold is on this cell , the displayChar is always 'G'
    void setGold(const std::shared_ptr<Gold> &t);

    // if a potion is on this cell, the displayChar is always 'P
    void setPotion(const std::shared_ptr<Potion> &p);
    
    // return true if isstair is true (the stair is on this cell)
    bool EnterStair() const;

    // return true if isPlayer is true (the player is on this cell)
    bool playerHere() const;
    
    // reset the cell to default (whatever on the cell leaves)
    void resetCell();

    // print the disPlayChar 
    // COLOUR !!! 
    void print() const;

    // return the x position of the cell
    int getX() const;

    // return the y position of the cell 
    int getY() const;

    // get the display Char
    char getChar() const;
     
    // get the pointer of the enemy/potion/gold
    std::shared_ptr<Enemy> getEnemy() const;
    std::shared_ptr<Potion> getPotion() const;
    std::shared_ptr<Gold> getGold() const;

    bool getHasMoved() const;
    void setHasMoved( bool );

    bool isDoorway() const;
};

#endif // CELL_H
