#include "BreakableItem.h"

using namespace game;

BreakableItem::BreakableItem(std::string subType, unsigned int weight) : BreakableItem(subType, weight, subType) {}

BreakableItem::BreakableItem(std::string subType, unsigned int weight, std::string name) : BreakableItem(subType, weight, name, ITEM_DURABILITY) {}

BreakableItem::BreakableItem(std::string subType, unsigned int weight, std::string name, unsigned int durability) : Item(subType, weight, name), durability(durability), maxDurability(durability) {}

BreakableItem::BreakableItem(const BreakableItem & bi) : Item(bi), durability(bi.durability), maxDurability(bi.maxDurability) {}

BreakableItem::BreakableItem(BreakableItem && bi) : Item(bi), durability(bi.durability), maxDurability(bi.maxDurability) {}

BreakableItem::~BreakableItem() {}

bool BreakableItem::breakItem() {
    if(!isWorking()){
        return false;
    }
    
    durability = 0;
    return true;
}

bool BreakableItem::decDurability(int amount) {
    if(!isWorking()){
        return false;
    } else {
        changeDurability(-amount);
        return true;
    }
}

bool BreakableItem::incDurability(int amount) {
    if(durability == maxDurability) {
        return false;
    } else {
        changeDurability(amount);
        return true;
    }
}

void BreakableItem::changeDurability(int amount){
    durability += amount;
    if(durability > maxDurability){
        durability = maxDurability;
    }
    if(durability < 0) {
        durability = 0;
    }
}

bool BreakableItem::isWorking() const {
    return durability > 0;
}

int BreakableItem::getDurability() const {
    return durability;
}

int BreakableItem::getMaxDurability() const {
    return maxDurability;
}

bool BreakableItem::isWeapon() const {
    return (getSubType() == ITEM_TYPE_WEAPON);
}

bool BreakableItem::isArmor() const {
    std::string subType = getSubType();
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

std::string BreakableItem::getStatisticalDescription() const {
    std::string desc = Item::getStatisticalDescription();
    desc += "\nDurability: (" + unsignedValToString(getDurability()) + "/" + unsignedValToString(getMaxDurability()) + ")";
    return desc;
}