#ifndef __ENEMYRACE_H__
#define __ENEMYRACE_H__

#include "enemy.h"

class Human : public Enemy {
public:
  Human( int, int );
};

class Dwarf : public Enemy {
public:
  Dwarf( int, int, int );
};

class Elf : public Enemy {
public:
  Elf( int, int, int );
};

class Orcs : public Enemy {
public:
  Orcs( int, int, int );
};

class Merchant : public Enemy {
public:
  Merchant( int, int );
};

class Dragon : public Enemy {
public:
  Dragon( int, int );
};

class Halfling : public Enemy {
public:
  Halfling( int, int, int );
};

#endif
