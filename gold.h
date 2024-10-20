#ifndef __GOLD_H__
#define __GOLD_H__
#include "item.h"
#include "enemyrace.h"

class Dragon;

class Gold : public Item {
     public:
        int small;
        int normal;
        int hoard;
        int dragon_hoard;
        int goblin;
        std::shared_ptr<Dragon> dragon;
        Gold(int x, int y, int small = 1, int normal = 2, int hoard = 4, int dragon_hoard = 6, int goblin = 5, std::shared_ptr<Dragon> dragon = nullptr);
        char getchar() override;
        bool canPickUp();
        int getgold();
};

#endif
