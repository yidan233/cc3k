#include <cmath>
#include "enemy.h"
#include "player.h"

using std::string;
using std::to_string;
using std::shared_ptr;

Enemy::Enemy( int HP, int Atk, int Def, int gold, int row, int col, string race,
              char c, bool isHostile, bool isMovable, bool isAlive) :
  Character{HP, Atk, Def, gold, row, col, race}, c{c}, isHostile{isHostile}, 
  isMovable{isMovable}, isAlive{isAlive} { }

bool Enemy::getIsHostile() const {
  return isHostile;
}

void Enemy::setIsHostile( bool b ) {
  isHostile = b;
}

void Enemy::addHP( int value ) {
  HP += value;
  if (HP < 0) HP = 0;
}

char Enemy::getChar() const {
  return c;
}

void Enemy::combat( shared_ptr<Player> p, string& action ) {
  // not in attack range
  if ((p->getRow() < row - 1 || p->getRow() > row + 1 || 
      p->getCol() < col - 1 || p->getCol() > col + 1) && race != "Dragon") {
    return;
  }
  
  // Determine Atk, Def of Player in current floor
  int curAtk = p->getAtk() + p->getBuffAtk();
  int curDef = p->getDef() + p->getBuffDef();
  if ( curAtk < 0) {
    curAtk = 0;
  }
  if ( curDef < 0) {
    curDef = 0;
  }

  // Enemy attacks Player
  int damage = ceil((100 * Atk) / (100 + curDef));
  if (prng(0, 1) == 0) { // 50% chance Enemy misses
    damage = 0;
    action += string(1, c) + "'s attack misses. ";
  }
  if (race == "Orcs" && p->getRace() == "Goblin") {
    damage *= 1.5;
  } else if (race == "Merchant" && !isHostile) {
    damage = 0;
  } else if (race == "Dragon" && !isHostile) {
    damage = 0;
  } 
  p->addHP(-damage);
  action += string(1, c) + " deals " + to_string(damage) + " damage to PC. ";
  if (p->getHP() <= 0) return;

  // May have another Attack
  if (race == "Elf" && p->getRace() != "Drow") {
    if (prng(0, 1) == 0) {
      p->addHP(-damage);
      action += string(1, c) + " gets second attack and deals " + 
                to_string(damage) + " to PC. ";
    } else {
      action += string(1, c) + "'s second attack misses. ";
    }
  }
}
