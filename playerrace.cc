#include <limits>
#include "playerrace.h"

Shade::Shade( int row, int col, std::vector<std::shared_ptr<Potion>> p ) :
  Player{125, 25, 25, 0, row, col, "Shade", 125, 0, 0, p} { }

Drow::Drow( int row, int col, std::vector<std::shared_ptr<Potion>> p ) : 
  Player{150, 25, 15, 0, row, col, "Drow", 150, 0, 0, p} { }

Vampire::Vampire( int row, int col, std::vector<std::shared_ptr<Potion>> p ) : 
  Player{50, 25, 25, 0, row, col, "Vampire",
         std::numeric_limits<int>::max(), 0, 0, p} { }

Troll::Troll( int row, int col, std::vector<std::shared_ptr<Potion>> p ) : 
  Player{120, 25, 15, 0, row, col, "Troll", 120, 0, 0, p} { }

Goblin::Goblin( int row, int col, std::vector<std::shared_ptr<Potion>> p ) : 
  Player{110, 15, 20, 0, row, col, "Goblin", 110, 0, 0, p} { }
