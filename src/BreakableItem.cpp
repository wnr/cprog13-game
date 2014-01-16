#include "BreakableItem.h"

using namespace game;

BreakableItem::BreakableItem(std::string type) : BreakableItem(type, true) {}

BreakableItem::BreakableItem(std::string type, bool visible) : Item(type, visible) {}

BreakableItem::BreakableItem(const BreakableItem & bi) : Item(bi), durability(bi.durability), maxDurability(bi.maxDurability) {}

BreakableItem::BreakableItem(BreakableItem && bi) : Item(bi), durability(bi.durability), maxDurability(bi.maxDurability) {}

BreakableItem::~BreakableItem() {}

bool BreakableItem::breakItem() {
    if(!isWorking()){
        return false;
    }
    
    log(this, "broke!");
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
    return durability <= 0;
}

int BreakableItem::getDurability() const {
    return durability;
}

int BreakableItem::getMaxDurability() const {
    return maxDurability;
}