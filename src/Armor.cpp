#include "Armor.h"

#include "Constants.h"

using namespace game;

Armor::Armor(std::string subType) : Armor(subType, ARMOR_RATING){}

Armor::Armor(std::string subType, unsigned int armorRating) : Armor(subType, armorRating, ARMOR_DODGE_RATING){}

Armor::Armor(std::string subType, unsigned int armorRating, unsigned int dodgeRating) : Armor(subType, armorRating, dodgeRating, ARMOR_WEIGHT) {}

Armor::Armor(std::string subType, unsigned int armorRating, unsigned int dodgeRating, unsigned int weight) : Armor(subType, armorRating, dodgeRating, weight, subType) {}

Armor::Armor(std::string subType, unsigned int armorRating, unsigned int dodgeRating, unsigned int weight, std::string name) : BreakableItem(subType, weight, name), armorRating(armorRating), dodgeRating(dodgeRating) {
    if(!isArmor()) {
        throw new std::invalid_argument("The subType: " +  subType + " is not allowed.");
    }
}

Armor::Armor(const Armor & armor) :  BreakableItem(armor), armorRating(armor.armorRating) {}

Armor::Armor(Armor && armor) : BreakableItem(armor), armorRating(armor.armorRating) {}

Armor::~Armor() {}

std::string Armor::getStatisticalDescription() const {
    std::string desc = BreakableItem::getStatisticalDescription();
    desc += "\nArmor rating: " + unsignedValToString(armorRating);
    desc += "\nDodge rating: " + unsignedValToString(dodgeRating);
    return desc;
}

unsigned int Armor::getArmorRating() const {
    return armorRating;
}

unsigned int Armor::getDodgeRating() const {
    return dodgeRating;
}

bool Armor::affectDurability(unsigned int power) {
    if(!isWorking() || power < getArmorRating()) {
        return false;
    } else {
        if(happen(5)){
            decDurability(1);
        }
        return !isWorking();
    }
}

Armor * Armor::clone() const {
    Armor * c = new Armor(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}