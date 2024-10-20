#include "gameflow.h"
#include "playerrace.h"

GameFlow::GameFlow() : level(1), player(nullptr), floor(nullptr), enemyMoving(true){}

// smart pointer destroy itself automatically 
GameFlow::~GameFlow() {
}

// initialize a new floor, with everything spawned
//(default map)
void GameFlow::newFloor(int level, std::shared_ptr<Player> player, 
                        const std::string &filename, bool empty) {
    floor = std::make_unique<Floor>(level, player, filename);
    if (empty) floor->initializeFloor();
} 


// Handle enemy movement 
// if enemyMovingg == true, the enemies need to move randomly
void GameFlow::enemyMovement() {
    if (enemyMoving) {
        enemyMoving = false;
    } else {
        enemyMoving = true;
    }
}

void GameFlow::updatePosition(std::string command, int &xNew, int &yNew, std::string &action, const std::string str) {
    if (command == "no") {
            xNew--;
            action = "player " + str + "north. ";
    } else if (command == "so") {
            xNew++;
            action = "player " + str + "south. ";
    } else if (command == "ea") {
            yNew++;
            action = "player " + str + "east. ";
    } else if (command == "we") {
            yNew--;
            action = "player " + str + "west. ";
    } else if (command == "ne") {
            yNew++;
            xNew--;
            action = "player " + str + "northeast. ";
    } else if (command == "nw") {
            yNew--;
            xNew--;
            action = "player " + str + "northwest. ";
    } else if (command == "se") {
            yNew++;
            xNew++;
            action = "player " + str + "southeast. ";
    } else if (command == "sw") {
            yNew--;
            xNew++;
            action = "player " + str + "southwest. ";
    }
}

void GameFlow::attackPlayer(int x, int y, std::string & action, bool& b) {
  std::vector<std::pair<int, int>> possible = {
    {x - 1, y - 1}, {x - 1, y}, {x - 1, y + 1},
    {x, y - 1},  {x, y + 1},
    {x + 1,  y - 1}, {x + 1, y}, {x + 1, y + 1}};

    bool already = false; // used to check whether 8 nearby cells have both dragon and gold, if there's dragon, set it to true and no need to check again for gold

    for (auto it = possible.begin() ; it != possible.end(); ++it) {
        std::shared_ptr<Cell> cell = floor->getCell(it->first, it->second);
        if (cell->getChar() == 'D') {
            already = true;
        }
    }
  for (auto it = possible.begin() ; it != possible.end(); ++it) {
    std::shared_ptr<Cell> cell = floor->getCell(it->first, it->second);
    if (cell->getChar() == 'H' || cell->getChar() == 'W' || 
        cell->getChar() == 'E' || cell->getChar() == 'O' || 
        (cell->getChar() == 'M' && cell->getEnemy()->getIsHostile()) || cell->getChar() == 'L' || 
        cell->getChar() == 'D' ) {
      cell->getEnemy()->combat(player, action);
    } else if (cell->getChar() == 'G' && !already && cell->getGold()->dragon_hoard != 0) {
        int goldx = cell->getX();
        int goldy = cell->getY();
      std::vector<std::pair<int, int>> dragon = {
        {goldx - 1, goldy - 1}, {goldx - 1, goldy}, {goldx - 1, goldy + 1},
        {goldx, goldy - 1},  {goldx, goldy + 1},
        {goldx + 1, goldy - 1}, {goldx + 1, goldy}, {goldx + 1, goldy + 1}};
      for (auto ite = dragon.begin() ; ite != dragon.end(); ++ite) {
        std::shared_ptr<Cell> cell2 = floor->getCell(ite->first, ite->second);
        if (cell2->getChar() == 'D' ) {
          cell2->getEnemy()->combat(player, action);
          break;
        }
      }
    }
    checkPlayerDeath(b);
    if (player == nullptr) return;
  }
}

void GameFlow::checkPlayerDeath(bool & start){
    if (player->getHP() <= 0) {
        std::cout << "-------------------------------------" << std::endl;
        std::cout << " womp womp ! you are dead" << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        player = nullptr;
        floor = nullptr;
        start = false;
        if (player && !player->potions.empty()) {
                player->potions.clear();
        }


    }       
}


bool GameFlow::validDirection(std::string command) {
    return command == "no" || command== "so" || command == "ea" 
    || command == "we" || command == "ne" || command == "nw" || command == "se"
    || command == "sw";
}

// Start the game and handle the main game loop
void GameFlow::startGame(std::string filename) {
    string race;
    string command;
    string action;
    while (true) {
        bool start = true;
        while (start) {
    // -------------------------------------------------------------------------------------
    /* int HP, int Atk, int Def, int gold, int row, int col, 
                int maxHP, int chamber, int buffAtk, int buffDef, 
                std::vector<Potion*> potions */
        // first, ask the player to choose a race 
            while (true) {
                std::cout << "s (shade) : 125 HP, 25 Atk, 25 Def" << std::endl;
                std::cout << "d (drow)    : 150 HP, 25 Atk, 15 Def, all potions have their effect magnified by 1.5" << std::endl;
                std::cout << "v (vampire) : 50 HP, 25 Atk, 25 Def, gains 5 HP every successful attack and has no maximum HP" << std::endl;
                std::cout << "t (troll)   : 120 HP, 25 Atk, 15 Def, regains 5 HP every turn; HP is capped at 120 HP" << std::endl;
                std::cout << "g (goblin)  : 110 HP, 15 Atk, 20 Def, steals 5 gold from every slain enemy" << std::endl;
                std::cout << "Choose a race: (s (default) / d (drow) / v (vampire) / g (goblin) / t (troll) ) ?" << std::endl;
                // BONUS -> add command to show description for each race ?  
                std::cin >> race;
                // !!! call player's constructor !!! more Info Here !!!!
                std::vector<shared_ptr<Potion>> potions;
                if (race == "s") {
                    this->player = std::make_shared<Shade>(0,0, potions);
                    std::cout << "shade chosen !" << std::endl;
                    break;
                // Drow
                } else if (race == "d") {
                    this->player = std::make_shared<Drow>(0,0, potions);
                    std::cout << "Drow chosen !" << std::endl;
                    break;
                // Vampire
                } else if (race == "v") {
                    this->player = std::make_shared<Vampire>(0,0, potions);
                    std::cout << "Vampire chosen !" << std::endl;
                    break;
                // Goblin
                } else if (race == "g") {
                    this->player = std::make_shared<Goblin>(0,0, potions);
                    std::cout << "Goblin chosen !" << std::endl;
                    break;
                // Troll
                } else if (race == "t") {
                    this->player = std::make_shared<Troll>(0,0, potions);
                    std::cout << "troll chosen !" << std::endl;
                    break;
                } else {
                    std::cout << "invalid input, please enter again !" << std::endl;
                }
            }
    // ------------------------------------------------------------------------------------
            // generate each floor 
            // asking for the filename of the map 
            std::string filename;
            std::cout << "please input the file name of the map" << std::endl;
            std::cin >> filename;
            bool empty;
            string e;
            while (true) {
                std::cout << "is this an empty floor ? y or n " << std::endl;
                std::cin >> e;
                if ( e == "y") {
                    empty = true;
                    break;
                } else if (e == "n") {
                    empty = false;
                    break; 
                }
            }
            while (this->level <= 5 && start) {
                // initialize a floor (with everything generated and spawn)
                newFloor(this->level, this->player, filename, empty);
                if (level == 1) {
                    action = "player is born in level 1" ;
                } else {
                    action = "player enter level " + std::to_string(level);
                }
            
                // interaction within each floor 
                bool onfloor = true;
                while (start && onfloor) {
                    // display information 
                    floor->showFloor();
                    // !!!! need this function implemented 
                    // print Race, Gold, HP, ATK, DEF
                    std::cout << "you are on level " << std::to_string(level) << std::endl;
                    player->print(); 
                    std::cout << "Action: " << action << std::endl;
                    //  command
                    string command;
                    /*
                    std::cout << "-------------------please enter your command--------------" << std::endl;
                    std::cout << "directions: no/so/ea/we/ne/nw/se/sw" << std::endl;
                    std::cout << "move? innput a direction! " << std::endl;
                    std::cout << "potion? input u! " << std::endl;
                    std::cout << "fight? input a!" << std::endl;
                    std::cout << "q for quite/ r for restart / f to stop enemy" << std::endl;
                    */
                    std::cout << "now please enter your command" << std::endl;
                    std::cout << "--------------------------------------------------------------" <<std::endl;
                    bool invalidCommand = true;
                    while (invalidCommand) {
                        std::cin >> command;
                        // enemy stop // Description? 
                        if (command == "f") {
                            enemyMovement();
                            invalidCommand = false;
                        // restart 
                        } else if (command == "r") {
                            
                            this->floor = nullptr;
                            this->level = 1;
                            start = false;
                            if (player && !player->potions.empty()) {
                                player->potions.clear();
                            }    
                            this->player = nullptr;       
 
                            invalidCommand = false;
                            break;
                        // quit
                        } else if (command == "q")  {
                            if (player && !player->potions.empty()) {
                                player->potions.clear();
                            }
 

                            return; 
                        // attack
                        } else if (command == "a") {
                            string direction;
                            std::cin >> direction;
                            if (this->validDirection(direction)) {
                                // player's position
                                int x = player->getRow();
                                int y = player->getCol();
                                int xNew = x;
                                int yNew = y;
                                // enemy's position 
                                updatePosition(direction, xNew, yNew, action, "tries to attack the enemy at the ");
                                floor->attackEnemy(xNew,yNew, action); 
                                checkPlayerDeath(start);
                                if (player == nullptr) break;
                                attackPlayer(x, y, action, start);
                                if (player == nullptr) break; 
                                invalidCommand = false;
                            } else {
                                std::cout << " invalid command " << std::endl;
                            }
                            if (this->enemyMoving) {
                                floor->moveAllEnemies(action);
                            }
                        // use posion
                        } else if (command == "u") {
                            string direction;
                            std::cin >> direction;
                            if (this->validDirection(direction)) {
                                // use potion
                                int x = player->getRow();
                                int y = player->getCol();
                                int xNew = x;
                                int yNew = y;
                                // enemy's position
                                updatePosition(direction, xNew, yNew, action, " tries to pick up the potion at the ");
                                floor->usePotion(xNew,yNew,action);
                                invalidCommand = false;
                            } else {
                                std::cout << "invalid command" << std::endl;
                            }    
                            attackPlayer(player->getRow(), player->getCol(), action, start);
                            if (player == nullptr) break;      
                            if (this->enemyMoving) {
                                floor->moveAllEnemies(action);
                            }
                        // move character 
                        } else if (this->validDirection(command)) {
                            // get character's position 
                            int x = player->getRow();
                            int y = player->getCol();
                            int xNew = x;
                            int yNew = y;
                            updatePosition(command, xNew, yNew, action, "tries to move ");
                            // if reach the stair
                            if (floor->doorwayReached(xNew, yNew)) {
                                player->resetBuff();
                            }

                            if (floor->stairReached(xNew, yNew)) {
                                level += 1;
                                if (level == 6) {
                                    std::cout << "Congratulations! You win!" << std::endl;
                                    if (player->getRace() == "Shade") {
                                        int score = player->getGold() * 1.5;
                                        std::cout << "Your score is: "<< score << std::endl;
                                        
                                    }else {
                                    std::cout << "Your score is: "<< player->getGold() << std::endl;  
                                    }
                                    start = false;
                                    if (player && !player->potions.empty()) {
                                        player->potions.clear();
                                    }

                                    invalidCommand = false;
                                } else {
                                    onfloor = false;
                                    invalidCommand = false;
                                }
                            }
                            
                           std::shared_ptr<Cell> c1 = floor->getCell(x, y);
                           std::shared_ptr<Cell> c2 = floor->getCell(xNew, yNew);
                            floor->moveBetweenCell(c1, c2, action);
                            invalidCommand = false; 
                            attackPlayer(xNew, yNew, action, start);
                            if (player == nullptr) break;
                            if (this->enemyMoving) {
                                floor->moveAllEnemies(action);
                            }
                        } else {
                            std::cout << "invalid command !" << std::endl;  
                        }
                    }
                    if (start == false) {

                        break;
                    } 
                    // update enemy's random move
                    /*
                    if (this->enemyMoving) {
                        floor->moveAllEnemies(action);
                    }
                    */
                    if (player->getRace() == "Troll") {
                        player->addHP(5);
                    }
                    // player dead
                    checkPlayerDeath(start);
                    if (player == nullptr) break;
                }
            }
        }
        // start false, break the game
        if (start == false) {
            std::cout << "do you want to restart? y (restart) or n (quit)" << std::endl;
            std::string answer;
            std::cin >> answer;
            if (answer == "y") {;
                player = nullptr;
                floor = nullptr;
                level = 1;
                start = true;
                
            } else {
                
                return; // quit
            }
        }
    }
}   
