#include "gold.h"

Gold::Gold(int x, int y, int small, int normal, int hoard, int dragon_hoard, int goblin, std::shared_ptr<Dragon>dragon) : 
    Item{x, y}, small{small}, normal{normal}, hoard{hoard}, dragon_hoard{dragon_hoard}, goblin{goblin}, dragon{dragon} {}

char Gold::getchar() {
    return 'G';
}

bool Gold::canPickUp() {
    if (!dragon) {
        return true;
    } else if (dragon && dragon->getHP() == 0) {
        return true;
    } else {
        return false;
    }
}

int Gold::getgold() {
    if (small != 0) {
        return small;
    } else if (normal != 0) {
        return normal;
    } else if (hoard != 0) {
        return hoard;
    } else if (dragon_hoard != 0) {
        return dragon_hoard;
    } else if (goblin != 0) {
        return goblin;
    } else {
        return -1;
    }
}

