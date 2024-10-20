#include "floor.h"
#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

//constructor 
Floor::Floor(int level, std::shared_ptr<Player> player,  const std::string& filename ):level(level), player(player) {
  std::random_device rd;
  prng.seed(rd());
  // initialize grid 
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error, I cannot find the file" << std::endl;
    return;
  }
  std::string line;
  int x = 0;
  // first create the grid 
  while (getline(file, line)) {
        std::vector<std::shared_ptr<Cell>> row; 
        for (size_t y = 0; y < line.size(); y++) {
          // start here : check for number 1 - 9
          if (('0' <= line[y] && line[y] <= '9') || line[y] == '@' || line[y] == '\\'|| line[y] == 'H' || line[y] == 'W'
          || line[y] == 'L'|| line[y] == 'E' || line[y] == 'O'|| line[y] == 'M' || line[y] == 'D') {
            // they can only appears on the empty floor tiles 
            row.push_back(std::make_shared<Cell>(x, y, '.'));
          } else {
            row.push_back(std::make_shared<Cell>(x, y, line[y]));
          }   
        }
        x++;
        grid.push_back(std::move(row));
  }
  std::ifstream file2(filename);
  // initialize the floor according to the number given
  int x2 = 0;
  while (getline(file2, line)) {
      for (size_t y = 0; y < line.size(); y++) {
        if (line[y] == '0') {
          std::shared_ptr<Potion> p = std::make_shared<RestoreHealth>(x2, y, player);
          grid[x2][y]->setPotion(p);
        } else if (line[y]== '1') {
          std::shared_ptr<Potion> p = std::make_shared<BoostAttack>(x2, y, player);
          grid[x2][y]->setPotion(p);
        }else if (line[y]== '2') {
          std::shared_ptr<Potion> p = std::make_shared<PoisonHealth>(x2, y, player);
          grid[x2][y]->setPotion(p);
        }else if (line[y]== '3') {
          std::shared_ptr<Potion> p = std::make_shared<BoostDef>(x2, y, player);
          grid[x2][y]->setPotion(p);
        }else if (line[y] == '4') {
          std::shared_ptr<Potion> p = std::make_shared<WoundAttack>(x2, y, player);
          grid[x2][y]->setPotion(p);
        }else if (line[y] == '5') {
          std::shared_ptr<Potion> p = std::make_shared<WoundDef>(x2, y, player);
          grid[x2][y]->setPotion(p);
        } else if (line[y] == '6') {
          std::shared_ptr<Gold> t = std::make_shared<Gold>(x2, y, 1, 0, 0, 0, 0, nullptr);
          grid[x2][y]->setGold(t);
        } else if (line[y] == '7') {
          std::shared_ptr<Gold> t = std::make_shared<Gold>(x2, y, 0, 2, 0, 0, 0, nullptr);
          grid[x2][y]->setGold(t);
        }else if (line[y] == '8') {
          std::shared_ptr<Gold> t = std::make_shared<Gold>(x2, y, 0, 0, 4, 0, 0, nullptr);
          grid[x2][y]->setGold(t);
        } else if (line[y] == '9') {
          std::shared_ptr<Gold> t = std::make_shared<Gold>(x2, y, 0, 0, 0, 6, 0, nullptr);
          grid[x2][y]->setGold(t);
        } else if (line[y] == '@') {
          grid[x2][y]->setPlayer();
          player->updatePos(x2, y);
        } else if (line[y] == '\\') {
          grid[x2][y]->setStair();
        } else if (line[y] == 'H') {
          std::shared_ptr<Enemy> c = std::make_shared<Human>(x2, y);
          grid[x2][y]->setEnemy(c,'H');
        } else if (line[y] == 'W') {
          int gold = chooseRandomNumber(2);
          std::shared_ptr<Enemy> c = std::make_shared<Dwarf>(gold,x2, y);
          grid[x2][y]->setEnemy(c, 'W');
        } else if (line[y] == 'L') {
          int gold = chooseRandomNumber(2);
          std::shared_ptr<Enemy> c = std::make_shared<Halfling>(gold, x2, y);
          grid[x2][y]->setEnemy(c, 'L');
        } else if (line[y] == 'E') {
          int gold = chooseRandomNumber(2);
          std::shared_ptr<Enemy> c = std::make_shared<Elf>(gold, x2, y);
          grid[x2][y]->setEnemy(c, 'E');
        } else if (line[y] == 'O') {
          int gold = chooseRandomNumber(2);
          std::shared_ptr<Enemy> c = std::make_shared<Orcs>(gold, x2, y);
          grid[x2][y]->setEnemy(c, 'O');
        } else if (line[y] == 'M') {
          std::shared_ptr<Enemy> c = std::make_shared<Merchant>(x2, y);
          grid[x2][y]->setEnemy(c, 'M');
        } else if (line[y] == 'D') {
          std::shared_ptr<Enemy> c = std::make_shared<Dragon>(x2, y);
          grid[x2][y]->setEnemy(c, 'D');
        }
     }
     x2++;
  } 
  // stop here

  // initialize chamber
  // add the floor tiles pointer to each of the chamber class
  // Initialize chambers
  for (int i = 0; i < 5; ++i) {
    chambers.push_back(std::make_unique<Chamber>());
  }
  // c0
  for (int x = 3; x < 7; x++) {
    for (int y =3; y < 29; y++) {
      chambers[0]->addCell(grid[x][y]);
    }
  }
  // c1
  for (int x = 15; x < 22; x++) {
    for (int y = 4; y <25; y++) {
      chambers[1]->addCell(grid[x][y]);
    }
  }
  // c2 (irregular)
  for (int x = 3; x < 7; x++ ) {
    for (int y = 39; y < 62; y++) {
      chambers[2]->addCell(grid[x][y]);
    }
  }
  for (int y = 62; y < 70; y++) {
    chambers[2]->addCell(grid[5][y]);
  }
  for (int y = 62; y < 73; y++) {
    chambers[2]->addCell(grid[6][y]);
  }
  for (int x = 7; x < 13 ; x++) {
    for (int y = 61; y < 76; y++) {
      chambers[2]->addCell(grid[x][y]);
    }
  }
  // c3
  for (int x = 10; x < 13; x++) {
    for (int y = 38; y < 50; y++) {
      chambers[3]->addCell(grid[x][y]);
    }
  }
  // c4 (irregular)
  for (int x = 16; x < 19; x++) {
    for (int y = 65; y < 76; y++) {
      chambers[4]->addCell(grid[x][y]);
    }
  }
  for (int x = 19; x < 22; x++) {
    for (int y = 37; y < 76; y++) {
      chambers[4]->addCell(grid[x][y]);
    }
  }
}
  

Floor::~Floor() {
  // smart pointer delete itself automatically 
}

// print the floor 
void Floor::showFloor() const {
    for (const auto &row : grid) {
        for (const auto &cell : row) {
            cell->print();
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}


// spawn the player, stair, postion, treausre and enemies to the floor 
void Floor::initializeFloor() {
    // Placeholder for methods to initialize different entities on the floor
    setPlayer();
    setStair();
    spawnPotion();
    spawnTreasure();
    SpawnEnemies();
}

// helper function to choose a random chamberNumber
int Floor::chooseRandomNumber(int range) {
  return prng(1, range);
}

void Floor::setPlayer() {
  if (chambers.empty()) {
      std::cerr << "Error: No chambers ! (call the constructor?)" << std::endl;
      return;
    }
    // first, randomly choose a chamber 
    // choose one random floorTile position from the chamber
    // set the player
    int chamberIndex = chooseRandomNumber(chambers.size()) - 1;
    chambers[chamberIndex]->setPlayer(); // update the info in the chamber
    std::shared_ptr<Cell> randomTile = chambers[chamberIndex]->randomFloorTile();
    if (!randomTile) {
      std::cerr << "sth is wrong when randomly choosing the floorTile" << std::endl;
    }
    randomTile->setPlayer();
    int x = randomTile->getX();
    int y = randomTile->getY();
    player->updatePos(x,y);
}

void Floor::setStair() {
  // stair should not be in the same room as the player 
  size_t chamberNumber;
  chamberNumber = chooseRandomNumber(chambers.size()) - 1;
  // if choose the chamber the player is at, choose the chamber 1 more than it
  if (chambers[chamberNumber]->playerHere()) {
      if (chamberNumber == chambers.size() - 1) {
        chamberNumber -=1;
      } else {
        chamberNumber +=1;
      }
  }
  auto randomTile = chambers[chamberNumber]->randomFloorTile();
  if (randomTile) {
        randomTile->setStair();
    } else {
        std::cerr << "Failed to get a random floor tile when setting stair " << chamberNumber << std::endl;
    }
}

std::shared_ptr<Dragon> Floor::spawnDragon(int x, int y, int chamberIndex) {
  // first find the cells around the randomcell
   std::vector<std::pair<int, int>> potentialPositions = {
        {x - 1, y - 1}, {x - 1, y}, {x- 1, y + 1},
        {x, y- 1},  {x, y + 1},
        {x + 1,  y - 1}, {x + 1, y}, {x + 1, y + 1}
    };
  // shuffle the listof potentialPosition
   unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
   std::default_random_engine rng1{seed};
   std::shuffle(potentialPositions.begin(), potentialPositions.end(), rng1);

   // checking if these positions is avaliable in the chamber, if so, set the dragon there
    for (const auto& position : potentialPositions) {
      if (grid[position.first][position.second]->validPosition()) {
        std::shared_ptr<Dragon> d = std::make_shared<Dragon>(position.first, position.second);
        grid[position.first][position.second]->setEnemy(d, 'D');
        // update chamber's floor Tile, making sure it only contains valid position
        chambers[chamberIndex]->update();
        return d;
      } 
    }
    return nullptr;
}

void Floor::spawnPotion() {
    for (int i = 0; i < 10; i++) {
        // Generate the potion
        // 0, 1, 2, 3, 4
        int chamberIndex = chooseRandomNumber(chambers.size()) - 1;
        auto randomTile = chambers[chamberIndex]->randomFloorTile();
        // check error
        if (!randomTile) {
            std::cerr << "Error: Can not find a  valid floortile when spawning potion" << std::endl;
            continue; 
        }
        // Choose the potion type and create the position, add to the cell
        std::shared_ptr<Potion> p;
        int positionNumber = chooseRandomNumber(6); // returns 1 to 6
        // generate the potion with required input (!!!!!!!!!!!!!!!!!!!!!)
        if (positionNumber == 1) {
          p = std::make_shared<RestoreHealth>(randomTile->getX(), randomTile->getY(), player);
        } else if (positionNumber == 2) {
          p = std::make_shared<BoostAttack>(randomTile->getX(), randomTile->getY(), player);
        } else if (positionNumber == 3) {
          p = std::make_shared<PoisonHealth>(randomTile->getX(), randomTile->getY(), player);
        } else if (positionNumber == 4) {
          p = std::make_shared<BoostDef>(randomTile->getX(), randomTile->getY(), player);
        } else if (positionNumber == 5) {
          p = std::make_shared<WoundAttack>(randomTile->getX(), randomTile->getY(), player);
        } else if (positionNumber == 6) {
          p = std::make_shared<WoundDef>(randomTile->getX(), randomTile->getY(), player);
        }
        if (p) {
            randomTile->setPotion(p);  // Assuming setItem is correctly implemented to accept shared_ptr
        } else {
            std::cerr << "Potion not generated." << std::endl;
        }
    }
}


void Floor::spawnTreasure() {
  int numTreasure = 15 / level; // adjust according to the level
    for (int i = 0; i < numTreasure; i++) {
        int chamberIndex = chooseRandomNumber(chambers.size()) - 1;
        auto randomTile = chambers[chamberIndex]->randomFloorTile();
        if (!randomTile) {
            std::cerr << "Error: No valid tile found when spawning treasure" << std::endl;
            continue; 
        }
        int treasureNumber = chooseRandomNumber(8);
        std::shared_ptr<Gold> t;
        // !!!!! input required to construct different types? 
        if (treasureNumber <= 5) {  
            t = std::make_shared<Gold>(randomTile->getX(), randomTile->getY(), 1,0,0,0,0,nullptr);
        } else if (treasureNumber <= 7) {  // Revised the range check
            t = std::make_shared<Gold>(randomTile->getX(), randomTile->getY(),0,2,0,0,0, nullptr);
        } else {
          // spawn the dragon first
          std::shared_ptr<Dragon> d = spawnDragon(randomTile->getX(), randomTile->getY(), chamberIndex);
          t = std::make_shared<Gold>(randomTile->getX(), randomTile->getY(), 0, 0,0,6,0, d); 
        }
        if (t) {
            randomTile->setGold(t);  
        } else {
            std::cerr << "error: Treasure not generated ! " << std::endl;
        }
    }
}


void Floor::SpawnEnemies() {
  for (int i = 0; i < 20; i++) {
    // choose the chamber number 
    int chamberIndex = chooseRandomNumber(chambers.size()) - 1;
    auto randomTile = chambers[chamberIndex]->randomFloorTile();
    // check error
    if (!randomTile) {
      std::cerr << "Error: No valid tile found when spawning enemies" << std::endl;
      continue; 
    }
    std::shared_ptr<Enemy> c;
    int enemyNumber = chooseRandomNumber(18);
    // figure out the valid input !!!!
    if (enemyNumber <= 4) {
      c = std::make_shared<Human>(randomTile->getX(), randomTile->getY());
      randomTile->setEnemy(c, 'H');
    } else if (enemyNumber <= 7) {
      int gold = chooseRandomNumber(2);
      c = std::make_shared<Dwarf>(gold, randomTile->getX(), randomTile->getY());
      randomTile->setEnemy(c, 'W');
    } else if (enemyNumber <= 12) {
      int gold = chooseRandomNumber(2);
      c = std::make_shared<Halfling>(gold, randomTile->getX(), randomTile->getY());
      randomTile->setEnemy(c, 'L');
    } else if (enemyNumber <=14) {
      int gold = chooseRandomNumber(2);
      c = std::make_shared<Elf>(gold, randomTile->getX(), randomTile->getY());
      randomTile->setEnemy(c, 'E');
    } else if (enemyNumber <= 16) {
      int gold = chooseRandomNumber(2);
      c = std::make_shared<Orcs>(gold, randomTile->getX(), randomTile->getY());
      randomTile->setEnemy(c, 'O');
    } else if (enemyNumber <= 18) {
      c = std::make_shared<Merchant>(randomTile->getX(), randomTile->getY());
      randomTile->setEnemy(c, 'M');
    } else {
      std::cerr << "Error: wrong random number when spawning enemies" << std::endl;
    }
  }
}

// move the player or  enemy from "from" to "to"
void Floor:: moveBetweenCell(std::shared_ptr<Cell> from, std::shared_ptr<Cell> to, string & action) {
  // first, the cell "from " has to be occupied , or we are moving nothing
  if (from->itIsOccupied()) {
    // if it is a player (double check)
    if (from->playerHere() && from->getChar() == '@') {
      // check if to is valid, otherwise dont move 
      if (!to->validPlayerPosition()) {
        action += "player fails to move, the cell is already occupied, :( ";
        return;
      } else {
        // player can be here !
        // check if it is picking up a gold 
        if (to->getChar() == 'G') {
          // can pick up the gold 
          if (to->getGold()->canPickUp()) {
            action += "player picked up the gold !";
            player->addGold(to->getGold()->getgold());
            // gold has been picked up, so empty 
            to->resetCell();
          } 
        } 
        int x = to->getX();
        int y = to->getY();
        player->updatePos(x,y);
        from->resetCell();
        to->setPlayer();  
        seesPotion(to->getX(), to->getY(), action);
        // check the eight cell around the player    
      }
    /// not sure if this part is needed 
    // else only enemy will be moved, potion and treasure simply disapper
    } else if (to->validPosition()) {
      char c = from->getChar();
      auto p = from->getEnemy();
      if (!p) {
        std::cerr<< "you are tryting to move nothing, really? sth. is wrong with the occipied check "<< std::endl;
      }
      // double check for debugging 
      if (c == 'P') {
        std::cerr << "you are trying to move a potion, really?"<< std::endl;
      } else if (c == 'G') {
        std::cerr << "you are trying to move a gold, really?" << std::endl;
        // an enemy
      } else {
        from->resetCell();
        to->setEnemy(p, c);
      }
    }
  }
}

void Floor::moveOneEnemy(int x, int y, string & action) {
  if (grid[x][y]->getChar() == 'd') {
    return;
  }

  std::vector<std::pair<int, int>> possible = {
    {x - 1, y - 1}, {x - 1, y}, {x - 1, y + 1},
    {x, y - 1},  {x, y + 1},
    {x + 1,  y - 1}, {x + 1, y}, {x + 1, y + 1}};

  for (auto it = possible.begin() ; it != possible.end(); ) {
    if (grid[it->first][it->second]->getChar() == '@') {
      return;
    } 

    if (!(grid[it->first][it->second]->getChar() == '.')) {
      possible.erase(it);
    } else {
      ++it;
    }
  }

  if (possible.empty()) {
    return;
  } else {
    int randomNumber = prng(0, possible.size() - 1);
    std::pair<int, int> newPos = possible[randomNumber];
    moveBetweenCell(grid[x][y], grid[newPos.first][newPos.second], action);
    grid[newPos.first][newPos.second]->setHasMoved(true);
    grid[newPos.first][newPos.second]->getEnemy()->updatePos(newPos.first, newPos.second);
  }
}

void Floor::moveAllEnemies(string & action ) {
  for (auto& row : grid) {
    for (auto& cell : row) {
      if ((cell->getChar() == 'H' || cell->getChar() == 'W' || 
           cell->getChar() == 'E' || cell->getChar() == 'O' || 
           cell->getChar() == 'M' || cell->getChar() == 'L') 
          && !cell->getHasMoved()) {
        moveOneEnemy(cell->getX(), cell->getY(), action);
      }
    }
  }
  for (auto& row : grid) {
    for (auto& cell : row) {
      cell->setHasMoved(false);
    }
  }
}

void Floor::attackEnemy(int xNew, int yNew, std::string & action) {
  if (!grid[xNew][yNew]->getEnemy() ) {
    action += "you are trying to attack nothing, stupid~ ";
    return;
  } 
    player->combat(grid[xNew][yNew]->getEnemy(), action);

  // check if enemy's hp is lower than 0
  if (grid[xNew][yNew]->getEnemy()->getHP() <= 0) {
    shared_ptr<Cell> curr = grid[xNew][yNew];
    if (curr->getChar() == 'W' || curr->getChar() == 'E' || 
        curr->getChar() == 'O' || curr->getChar() == 'L') {
        player->addGold(curr->getEnemy()->getGold());
        grid[xNew][yNew]->resetCell();
    } else if (curr->getChar() == 'M') { // Merchant
      grid[xNew][yNew]->resetCell();
      std::shared_ptr<Gold> t = std::make_shared<Gold>(xNew, yNew, 0, 0, 4, 0, 0, nullptr);
      grid[xNew][yNew]->setGold(t);
    } else if (curr->getChar() == 'H') { // Human
      grid[xNew][yNew]->resetCell();
      std::shared_ptr<Gold> t = std::make_shared<Gold>(xNew, yNew, 0, 2, 0, 0, 0, nullptr);
      grid[xNew][yNew]->setGold(t);
    } else if (curr->getChar() == 'D') {
      grid[xNew][yNew]->resetCell();
    }
    if (player->getRace() == "Goblin") {
      player->addGold(5);
    }
    action +="you killed the enemy, congrats";
  }
  if (grid[xNew][yNew]->getChar() == 'M' && grid[xNew][yNew]->getEnemy()->getIsHostile()) {
      for (auto& row : grid) {
        for (auto& cell : row) {
          if (cell->getEnemy()) {
            cell->getEnemy()->setIsHostile(true);
          }
        }
      }
  }
}

bool Floor::stairReached(int x, int y) const {
  return grid[x][y]->EnterStair();
}

void Floor::usePotion(int xNew, int yNew, std::string & action) {
  // has potion 
  if (grid[xNew][yNew]->getChar() != 'P') {
    action += "you use nothing, because there is no potion there ! ";
    return;
  } else {
    // player sees potion, update the state of all the postions in the grid 
    // figure out the type of the potion
    std::string type = grid[xNew][yNew]->getPotion()->gettype();
    // make the player use this potion
    (grid[xNew][yNew]->getPotion())->usePotion(this->player, action);
    // update the state of the same potion in the gird 
    grid[xNew][yNew]->resetCell();
  }
}

std::shared_ptr<Cell> Floor::getCell(int x, int y) {
  return grid[x][y];
}

bool Floor::doorwayReached(int x, int y) const {
  return grid[x][y]->isDoorway();
}

// check if the player will see a potion or not 
void Floor::seesPotion(int x, int y, string & action ) {
  // the 8 cell around them 
  std::vector<std::pair<int, int>> potentialPositions = {
        {x - 1, y - 1}, {x - 1, y}, {x- 1, y + 1},
        {x, y- 1},  {x, y + 1},
        {x + 1,  y - 1}, {x + 1, y}, {x + 1, y + 1}
  };
  for (const auto& position : potentialPositions) {
    // it is a position 
    if (grid[position.first][position.second]->getChar() == 'P') {
       // the type of this gold 
        string type = grid[position.first][position.second]->getPotion()->gettype();
        bool inlist = false;
        for (size_t i = 0; i < player->potions.size(); i++) {
          if (player->potions[i]->gettype() == type) {
          action += "you see a " + grid[position.first][position.second]->getPotion()->gettype() + ". wanna pick up? ";
          inlist = true;
          break;
          } 
        }
        if (!inlist){
        action += "you see an unknown potion, wanna bet? ";  
        }
      }
    }
}
