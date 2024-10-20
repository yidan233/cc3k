#ifndef __POTION_H__
#define __POTION_H__

#include "item.h"
#include "player.h"

class Potion : public Item {
    public:
        string type;
        std::shared_ptr<Player> p;
        bool isUsed = false;
        Potion(int x, int y, string type, std::shared_ptr<Player> p, bool isUsed);
        char getchar();
        string gettype();
        virtual void usePotion(std::shared_ptr<Player> p, string& action) = 0;
        virtual ~Potion();
};

class RestoreHealth : public Potion {
    public:
        RestoreHealth(int x, int y, std::shared_ptr<Player> p, bool isUsed = false, string type = "RH");
        void usePotion(std::shared_ptr<Player> p, string& action);
};

class BoostAttack : public Potion {
    public:
        BoostAttack(int x, int y, std::shared_ptr<Player> p, bool isUsed = false, string type = "BA");
        void usePotion(std::shared_ptr<Player> p, string& action);
};

class BoostDef : public Potion {
    public:
        BoostDef(int x, int y, std::shared_ptr<Player> p, bool isUsed = false, string type = "BD");
        void usePotion(std::shared_ptr<Player> p, string& action);
};

class PoisonHealth : public Potion {
    public:
        PoisonHealth(int x, int y, std::shared_ptr<Player> p, bool isUsed = false, string type = "PH");
        void usePotion(std::shared_ptr<Player> p, string& action);
};

class WoundAttack : public Potion {
    public:
        WoundAttack(int x, int y, std::shared_ptr<Player> p, bool isUsed = false, string type = "WA");
        void usePotion(std::shared_ptr<Player> p, string& action);
};

class WoundDef : public Potion {
    public:
        WoundDef(int x, int y, std::shared_ptr<Player> p, bool isUsed = false, string type = "WD");
        void usePotion(std::shared_ptr<Player> p, string& action);
};

#endif
