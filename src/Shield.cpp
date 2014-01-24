#include "Shield.h"

#include "Constants.h"

using namespace game;

Shield::Shield() : Shield(SHIELD_BLOCK_RATING){}

Shield::Shield(unsigned int blockProb) : Shield(blockProb, SHIELD_ARMOR_RATING) {}

Shield::Shield(unsigned int blockProb, unsigned int armorRating) : Shield(blockProb, armorRating, SHIELD_BLOCK_RATING) {}

Shield::Shield(unsigned int blockProb, unsigned int armorRating, unsigned int dodgeRating) : Shield(blockProb, armorRating, dodgeRating, SHIELD_WEIGHT) {}

Shield::Shield(unsigned int blockProb, unsigned int armorRating, unsigned int dodgeRating, unsigned int weight) : Shield(blockProb, armorRating, dodgeRating, weight, ARMOR_TYPE_SHIELD) {}

Shield::Shield(unsigned int blockProb, unsigned int armorRating, unsigned int dodgeRating, unsigned int weight, std::string name) : Armor(ARMOR_TYPE_SHIELD, armorRating, dodgeRating, weight, name), blockProb(blockProb) {}

Shield::Shield(const Shield & shield) : Armor(shield), blockProb(shield.blockProb) {}

Shield::Shield(Shield && shield) : Armor(shield), blockProb(shield.blockProb ) {}

Shield::~Shield() {}

int Shield::getBlockProb() const {
    return blockProb;
}

std::string Shield::getStatisticalDescription() const {
    std::string desc = Armor::getStatisticalDescription();
    desc += "\nBlock prob: " + unsignedValToString(blockProb);
    return desc;
}

Shield * Shield::clone() const {
    Shield * c = new Shield(*this);
    if(typeid(*c) != typeid(*this)) {
        throw std::invalid_argument(INVALID_CLONE);
    }
    return c;
}

