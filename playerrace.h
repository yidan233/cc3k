#ifndef __PLAYERRACE_H__
#define __PLAYERRACE_H__

#include <vector>
#include <memory>
#include "player.h"

class Potion;

class Shade : public Player {
public:
  Shade( int, int, std::vector<std::shared_ptr<Potion>> );
};

class Drow : public Player {
public:
  Drow( int, int, std::vector<std::shared_ptr<Potion>> );
};

class Vampire : public Player {
public:
  Vampire( int, int, std::vector<std::shared_ptr<Potion>> );
};

class Troll : public Player {
public:
  Troll( int, int, std::vector<std::shared_ptr<Potion>> );
};

class Goblin : public Player {
public:
  Goblin( int, int, std::vector<std::shared_ptr<Potion>> );
};

#endif
