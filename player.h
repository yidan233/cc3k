#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <memory>
#include <vector>
#include "PRNG.h"
#include "character.h"

using std::vector;
using std::shared_ptr;
using std::string;

class Potion;
class Enemy;

class Player : public Character {
  PRNG prng;
  
protected:
  int maxHP;
  int buffAtk, buffDef;
  
  int realAtk( int ) const;
  int realDef( int ) const;

public:
  vector<shared_ptr<Potion>> potions;
  
  Player( int, int, int, int, int, int, string,
          int, int, int, vector<shared_ptr<Potion>> );

  virtual int getBuffAtk() const;
  virtual int getBuffDef() const;
  virtual int getMaxHP() const;
  
  virtual void addGold( int );
  virtual void addHP( int );
  virtual void addBuffAtk( int );
  virtual void addBuffDef( int );
  virtual void resetBuff();
  
  virtual void print() const;
  virtual void combat( shared_ptr<Enemy>, string& );
};

#endif
