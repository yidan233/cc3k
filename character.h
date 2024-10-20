#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <string>

class Character {
protected:
  int HP, Atk, Def;
  int gold;
  int row, col;
  std::string race;

public:
  Character( int, int, int, int, int, int, std::string );

  virtual std::string getRace() const;
  virtual int getRow() const;
  virtual int getCol() const;
  virtual int getHP() const;
  virtual int getAtk() const;
  virtual int getDef() const;
  virtual int getGold() const;

  virtual void updatePos( int, int );

  virtual void addHP( int ) = 0;
};

#endif
