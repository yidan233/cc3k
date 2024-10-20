#include <iostream>
#include "cell.h"

#define ESC "\033["
#define RESET "\033[0m"
#define PC_STAIR_COLOUR "46"// blue for PC and stair
#define ENEMY_COLOUR "101" // red for enemie
#define GOLD_COLOUR "103" // yellow for gold
#define POTION_COLOUR "102" // green for potion

Cell::Cell(int x, int y, char type)
    : x(x), y(y), type(type), displayChar(type), isOccupied(false), isPlayer(false), isStair(false), hasMoved(false) {}

bool Cell::validPlayerPosition() const {
    return displayChar == '.' || displayChar == '+' || displayChar == '#' || displayChar == 'G';
}

bool Cell::itIsOccupied() const {
    return isOccupied;
}

bool Cell::validPosition() const {
    return type == '.' && !isOccupied && displayChar == '.';
}

void Cell::setPlayer() {
    displayChar = '@';
    isPlayer = true;
    isOccupied = true;
}

void Cell::setEnemy(std::shared_ptr<Enemy> e, char c) {
    enemy = e;
    displayChar = c;
    isOccupied = true;
}

void Cell::setGold(const std::shared_ptr<Gold>& t) {
    gold = t;
    displayChar = 'G';
    isOccupied = true;
}

void Cell::setPotion(const std::shared_ptr<Potion>& p) {
    potion = p;
    displayChar = 'P';
    isOccupied = true;
}

void Cell::setStair() {
    isStair = true;
    displayChar = '/';
    isOccupied = true;
}

bool Cell::EnterStair() const {
    return isStair;
}

bool Cell::playerHere() const {
    return isPlayer;
}

void Cell::resetCell() {
    // if player if on the dragon hoard and leaves it 
    // gold does not disapplyer 
    if (isPlayer && gold) {
        isPlayer = false;
        displayChar = 'G';
    } else {
        enemy = nullptr;
        potion = nullptr;
        isPlayer = false;
        isStair = false;
        isOccupied = false;
        displayChar = type;
        gold = nullptr;
    }
}

void Cell::print() const {
    if (isPlayer || isStair) {
        std::cout << ESC << PC_STAIR_COLOUR << "m" << displayChar << RESET;
    } else if (enemy) {
        std::cout << ESC << ENEMY_COLOUR << "m" << displayChar << RESET;
    } else if (potion) {
        std::cout << ESC << POTION_COLOUR << "m" << displayChar << RESET;
    } else if (gold) {
        std::cout << ESC << GOLD_COLOUR << "m" << displayChar << RESET;
    } else {
        std::cout << displayChar;
    }
}

int Cell::getX() const {
    return x;
}

int Cell::getY() const {
    return y;
}

char Cell::getChar() const {
    return displayChar;
}

// get the pointer of the thing that is on the grid
std::shared_ptr<Enemy> Cell::getEnemy() const {
    return enemy;
}

std::shared_ptr<Potion> Cell::getPotion() const {
    return potion;
}

std::shared_ptr<Gold> Cell::getGold() const {
    return gold;
}

bool Cell::getHasMoved() const {
    return hasMoved;
}

void Cell::setHasMoved( bool b ) {
    hasMoved = b;
}

bool Cell::isDoorway() const {
    return displayChar == type && type == '+';
}
