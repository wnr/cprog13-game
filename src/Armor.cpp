#include "Armor.h"

#include "Constants.h"

using namespace game;

Armor::Armor(std::string subType) : Armor(subType, ARMOR_RATING){}

Armor::Armor(std::string subType, unsigned int armorRating) : Armor(subType, armorRating, ARMOR_WEIGHT) {}

Armor::Armor(std::string subType, unsigned int armorRating, unsigned int weight) : Armor(subType, armorRating, weight, subType) {}

Armor::Armor(std::string subType, unsigned int armorRating, unsigned int weight, std::string name) : BreakableItem(subType, weight, name), armorRating(armorRating) {
    if(!isSubTypeAllowed(subType)) {
        throw new std::invalid_argument("The subType: " +  subType + " is not allowed.");
    }
}

Armor::Armor(Armor && armor) : BreakableItem(armor), armorRating(armor.armorRating) {}

Armor::~Armor() {}

std::string Armor::getStatisticalDescription() const {
    std::string desc = Item::getStatisticalDescription();
    desc += "\nArmor rating: " + unsignedValToString(getArmorRating());
    return desc;
}

bool Armor::isSubTypeAllowed(const std::string & subType) const {
    if(subType != ARMOR_TYPE_CHEST  &&
       subType != ARMOR_TYPE_HELMET &&
       subType != ARMOR_TYPE_PANTS  &&
       subType != ARMOR_TYPE_SHIELD &&
       subType != ARMOR_TYPE_SHOE) {
        return false;
    } else {
        return true;
    }
}

unsigned int Armor::getArmorRating() const {
    return armorRating;
}