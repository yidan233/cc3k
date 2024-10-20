#include <memory>     
#include "gameflow.h" 

int main() {
  std::shared_ptr<GameFlow> g = std::make_shared<GameFlow>();
  g->startGame();
  return 0;
}
