#include "potion.h"
#include "player.h"

Potion::Potion(int x, int y, string type, std::shared_ptr<Player> p, bool isUsed) : Item{x, y}, type{type}, p{p}, isUsed{isUsed} {}

char Potion::getchar() {
    return 'P';
}

void Potion::usePotion(std::shared_ptr<Player> p, string& action) {}

string Potion::gettype() { return this->type; }

Potion::~Potion() {}

RestoreHealth::RestoreHealth(int x, int y, std::shared_ptr<Player> p, bool isUsed, string type) : Potion{x, y, type, p, isUsed} {}

void RestoreHealth::usePotion(std::shared_ptr<Player> p, string& action) {
    if (p->getRace() == "Drow") {
        p->addHP(15);
    } else {
       p->addHP(10);
    }
    p->potions.push_back(std::make_shared<RestoreHealth>(*this));
    action += " Player uses RH. ";
}

BoostAttack::BoostAttack(int x, int y, std::shared_ptr<Player> p, bool isUsed, string type) : Potion{x, y, type, p, isUsed} {}

void BoostAttack::usePotion(std::shared_ptr<Player> p, string& action) {
    if (p->getRace() == "Drow") {
        p->addBuffAtk(7.5);
    } else {
        p->addBuffAtk(5);
    }
    p->potions.push_back(std::make_shared<BoostAttack>(*this));
    action += " Player uses BA. ";
}

BoostDef::BoostDef(int x, int y, std::shared_ptr<Player> p, bool isUsed, string type) : Potion{x, y, type, p, isUsed} {}

void BoostDef::usePotion(std::shared_ptr<Player> p, string& action) {
    if (p->getRace() == "Drow") {
       p->addBuffDef(7.5);
    } else {
        p->addBuffDef(5);
    }
    p->potions.push_back(std::make_shared<BoostDef>(*this));
    action += " Player uses BD. ";
}

PoisonHealth::PoisonHealth(int x, int y, std::shared_ptr<Player> p, bool isUsed, string type) : Potion{x, y, type, p, isUsed} {}

void PoisonHealth::usePotion(std::shared_ptr<Player> p, string& action) {
    if (p->getRace() == "Drow") {
        p->addHP(-15);
    } else {
        p->addHP(-10);
    }
    p->potions.push_back(std::make_shared<PoisonHealth>(*this));
    action += " Player uses PH. ";
}

WoundAttack::WoundAttack(int x, int y, std::shared_ptr<Player> p, bool isUsed, string type) : Potion{x, y, type, p, isUsed} {}

void WoundAttack::usePotion(std::shared_ptr<Player> p, string& action) {
    if (p->getRace() == "Drow") {
        p->addBuffAtk(-7.5);
    } else {
        p->addBuffAtk(-5);
    }
    p->potions.push_back(std::make_shared<WoundAttack>(*this));
    action += " Player uses WA. ";
}

WoundDef::WoundDef(int x, int y, std::shared_ptr<Player> p, bool isUsed, string type) : Potion{x, y, type, p, isUsed} {}

void WoundDef::usePotion(std::shared_ptr<Player> p, string& action) {
    if (p->getRace() == "Drow") {
        p->addBuffAtk(-7.5);
    } else {
        p->addBuffAtk(-5);
    }
    p->potions.push_back(std::make_shared<WoundDef>(*this));
    action += " Player uses WD. ";
}
