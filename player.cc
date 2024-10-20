#include <vector>
#include <cmath>
#include <iostream>
#include "player.h"
#include "enemy.h"

using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::string;
using std::to_string;

Player::Player( int HP, int Atk, int Def, int gold, int row, int col, 
                string race, int maxHP, int buffAtk, int buffDef, 
                vector<shared_ptr<Potion>> potions ) :
  Character{HP, Atk, Def, gold, row, col, race}, maxHP{maxHP}, 
  buffAtk{buffAtk}, buffDef{buffDef}, potions{potions} { }

void Player::addHP( int value ) {
  HP += value;
  if (HP > maxHP) {
    HP = maxHP;
  } else if (HP < 0) {
    HP = 0;
  }
}

void Player::addGold( int value ) {
  gold += value;
}

void Player::addBuffAtk( int value ) {
  buffAtk += value;
}

void Player::addBuffDef( int value ) {
  buffDef += value;
}

int Player::getBuffAtk() const {
  return buffAtk;
}

int Player::getBuffDef() const {
  return buffDef;
}

int Player::getMaxHP() const {
  return maxHP;
}

void Player::print() const {
  cout << "Race: " << race << ' ' << "Gold: " << gold << endl;
  cout << "HP: " << HP << endl;
  cout << "Atk: " << realAtk(buffAtk) << endl;
  cout << "Def: " << realDef(buffDef) << endl;
}
  
int Player::realAtk( int value ) const {
  if (Atk + value > 0) {
    return Atk + value;
  } else {
    return 0;
  }
}

int Player::realDef( int value ) const {
  if (Def + value > 0) {
    return Def + value;
  } else {
    return 0;
  }
}

void Player::resetBuff() {
  buffAtk = 0;
  buffDef = 0;
}

void Player::combat( shared_ptr<Enemy> e, string& action) {
  // not in attack range
  if (e->getRow() < row - 1 || e->getRow() > row + 1 || 
      e->getCol() < col - 1 || e->getCol() > col + 1) {
    return;
  }

  // Determine Atk, Def in current floor
  int curAtk = realAtk(buffAtk);

  // Player attacks Enemy
  int damage = ceil((100 * curAtk) / (100 + e->getDef()));

  if (e->getRace() == "Halfling") { // halfling causes 50% chance Player misses
    if ( prng(0, 1) == 0 ) {
      damage = 0; 
      action += "PC's attack misses. ";
    }
  }
  e->addHP(-damage);
  action += "PC deals " + to_string(damage) + " damage to " + 
            e->getChar() + " (" + to_string(e->getHP()) + " HP). ";
  if (race == "Vampire" && e->getRace() == "Dwarf") {
    addHP(-5);
    action += "V loses 5 HP when attacking W. ";
  } else if (race == "Vampire") {
    addHP(5);
    action += "V gains extra 5 HP when attack succeeds. ";
  } else if (e->getRace() == "Merchant") {
    e->setIsHostile(true); 
  }
}
