#ifndef __ITEM_H__
#define __ITEM_H__

#include <iostream>

class Item {
    int x, y;
    public:
        Item(int x, int y);
        virtual char getchar() = 0;
};

#endif
