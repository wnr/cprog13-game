
#include "Armor.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Shield.h"
#include "BreakableItem.h"

using namespace game;

Equipment::Equipment() {}

Equipment::~Equipment() {}

std::unique_ptr<BreakableItem> Equipment::push_back(std::unique_ptr<BreakableItem> element) {
    if(findItemWithSubType(element->getSubType()) != NULL) {
        return element;
    } else {
        return GameStorage::push_back(std::move(element));
    }
}

BreakableItem * Equipment::findItemWithSubType(const std::string subType) const {
    BreakableItem * bi = Equipment::findItemWithSubType<BreakableItem>(subType);
    return bi;
}

unsigned int Equipment::getAttackPower() const {
    unsigned int attackPower = 0;
    Weapon * weapon = findItemWithSubType<Weapon>(ITEM_TYPE_WEAPON);
    if(weapon != NULL) {
        attackPower += weapon->getAttackPower();
    }
    return attackPower;
}


float Equipment::getDodgeProb() const {
    float dodgeProb = 0;
    
    for_each_armor([&dodgeProb](const Armor * armor){
        dodgeProb = incByPercent(dodgeProb, armor->getDodgeRating());
        return true;
    });
    return dodgeProb;
}

unsigned int Equipment::getArmorRating() const {
    unsigned int armorRating = 0;
    
    for_each_armor([&armorRating](const Armor * armor){
        armorRating += armor->getArmorRating();
        return true;
    });
    return armorRating;
}

float Equipment::getBlockProb() const {
    float blockProb = 0;
    Shield * shield = findItemWithSubType<Shield>(ARMOR_TYPE_SHIELD);
    if(shield != NULL) {
        blockProb = incByPercent(blockProb, shield->getBlockProb());
    }
    return blockProb;
}

void Equipment::for_each_armor(const std::function<bool (Armor*)> operation) const{
    for_each([operation](BreakableItem * bItem){
        if(bItem->isArmor()) {
            operation((Armor*) bItem);
        }
        return true;
    });
}

bool Equipment::affectArmorDurability(unsigned int power) const {
    bool itemBroke = false;
    for_each_armor([&itemBroke, power](Armor * armor){
        if(armor->decDurability(power)) {
            itemBroke = true;
        }
        return true;
    });
    return itemBroke;
}

bool Equipment::affectDurability(const std::string &subType, unsigned int power) const {
    BreakableItem * bi = findItemWithSubType(subType);
    if(bi != NULL) {
        return(bi->decDurability(power));
    }
    return false;
}
