#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <memory>
#include "character.h"
#include "PRNG.h"

using std::string;
using std::shared_ptr;

class Player;

class Enemy : public Character {
  PRNG prng;
protected:
  char c;
  bool isHostile, isMovable, isAlive;

public:
  Enemy( int, int, int, int, int, int, string, char, bool, bool, bool );
  
  virtual bool getIsHostile() const;
  virtual void setIsHostile( bool );
  virtual char getChar() const;
  void addHP( int ) override;

  virtual void combat( shared_ptr<Player>, string& action );
};

#endif
