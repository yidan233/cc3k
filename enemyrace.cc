#include "enemyrace.h"

// sequence : HP, Atk, Def, gold, row, col, race, isHostile, isMovable, isAlive

Human::Human( int row, int col ) : 
  Enemy{140, 20, 20, 2, row, col, "Human", 'H', true, true, true} { }

Dwarf::Dwarf( int gold, int row, int col ) : 
  Enemy{100, 20, 30, gold, row, col, "Dwarf", 'W', true, true, true} { }

Elf::Elf( int gold, int row, int col ) : 
  Enemy{140, 30, 10, gold, row, col, "Elf", 'E', true, true, true} { }

Orcs::Orcs( int gold, int row, int col ) : 
  Enemy{180, 30, 25, gold, row, col, "Orcs", 'O', true, true, true} { }

Merchant::Merchant( int row, int col ) : 
  Enemy{30, 70, 5, 4, row, col, "Merchant", 'M', false, true, true} { }

Dragon::Dragon( int row, int col ) : 
  Enemy{150, 20, 20, 6, row, col, "Dragon", 'D', true, false, true} { }

Halfling::Halfling( int gold, int row, int col ) : 
  Enemy{100, 15, 20, gold, row, col, "Halfling", 'L', true, true, true} { }
