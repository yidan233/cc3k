#include "chamber.h"

Chamber::Chamber() : hasPlayer(false) {
    std::random_device rd;
    prng.seed(rd());
}

void Chamber::setPlayer() {
  hasPlayer = true;
}

bool Chamber::playerHere() const {
    return hasPlayer;
}

void Chamber::addCell(const std::shared_ptr<Cell>& cell) {
    floorTiles.push_back(cell);
}

void Chamber::update() {
    int size = floorTiles.size();
    for (int i = 0; i < size;) {
        if (!floorTiles[i]->validPosition()) {
            std::swap(floorTiles[i], floorTiles.back());
            floorTiles.pop_back();
            size--;
        } else {
            i++;
        }
    }
}

std::shared_ptr<Cell> Chamber::randomFloorTile() {
   // error handling (no avalable floor tile in this chamber)
    if (floorTiles.empty()) {
        return nullptr; 
    }
    //randomly choose a number from the floorTiles list 
    while (!floorTiles.empty()) {
        int idx = prng(floorTiles.size() - 1);
        // double check 
        if (floorTiles[idx]->validPosition()) {
            std::shared_ptr<Cell> selectedTile = floorTiles[idx];
            std::swap(floorTiles[idx], floorTiles.back());
            floorTiles.pop_back();
            return selectedTile;
        }
    }
    return nullptr; // This should never happen, for error checking 
}
