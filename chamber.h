#ifndef CHAMBER_H
#define CHAMBER_H

#include <vector>
#include <random>
#include <memory>
#include "PRNG.h"
#include "cell.h" 

class Chamber{
  PRNG prng;       // random number generator                   
  bool hasPlayer;           // if player is in this chamber (used for generating stairs)                     
  std::vector<std::shared_ptr<Cell>> floorTiles; // the list that save the empty floorTiles in the chamber 
  class Iterator {
    friend class chamber;
    int row,col;
    int rowEnd;
    Iterator( int,int,int );
    public:
      bool operator==(const Iterator& other)const;
      std::shared_ptr<Cell>& operator*()const;
      Iterator& operator++();
   };
public:
  // constructor 
  Chamber(); 

  Iterator begin(int, int, int);
  Iterator end();
  void swapTwo(int, int);
  void moveOnePlayer(int, int);
  void moveOneEnemy(int, int);
  void moveAllEnemies();
  
  // set the hasPlayer to be true
  // this is used when generating Chamber
  // making sure that they are not in the same chamber
  void setPlayer();

  // return true if hasPlayer == true,
  // this is used when generating Chamber
  // making sure that they are not in the same chamber
  bool playerHere() const;   

  // add a cell to the floorTiles list                       
  void addCell(const std::shared_ptr<Cell> &cell); 

  // update the floorTiles list, making sure it only has empty floorTiles 
  void update();    

  // generate a random empty floorTile                                
  std::shared_ptr<Cell> randomFloorTile();         
};

#endif 
