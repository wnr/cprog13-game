
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


unsigned int Equipment::getDodgeProb() const {
    unsigned int dodgeProb = 0;
    
    for_each_armor([&dodgeProb](const Armor * armor){
        dodgeProb += armor->getDodgeRating();
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

unsigned int Equipment::getBlockProb() const {
    unsigned int blockProb = 0;
    Shield * shield = findItemWithSubType<Shield>(ARMOR_TYPE_SHIELD);
    if(shield != NULL) {
        blockProb += shield->getBlockProb();
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
