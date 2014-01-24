
#include "Armor.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Shield.h"
#include "BreakableItem.h"
#include "Constants.h"

using namespace game;

Equipment::Equipment() : PhysicalObject(OBJECT_TYPE_OTHER, OTHER_TYPE_EQUIPMENT){}

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

unsigned int Equipment::getMinDmg() const {
    unsigned int attackPower = 0;
    Weapon * weapon = findItemWithSubType<Weapon>(ITEM_TYPE_WEAPON);
    if(weapon != NULL && weapon->isWeapon()) {
        attackPower += weapon->getMinDmg();
    }
    return attackPower;
}

unsigned int Equipment::getMaxDmg() const {
    unsigned int attackPower = 0;
    Weapon * weapon = findItemWithSubType<Weapon>(ITEM_TYPE_WEAPON);
    if(weapon != NULL && weapon->isWorking()) {
        attackPower += weapon->getMaxDmg();
    }
    return attackPower;
}

unsigned int Equipment::getCritMod() const {
    unsigned int critMod = 0;
    Weapon * weapon = findItemWithSubType<Weapon>(ITEM_TYPE_WEAPON);
    if(weapon != NULL) {
        critMod += weapon->getCritModifier();
    }
    return critMod;
}

float Equipment::getCritProb() const {
    float critProb = 0;
    Weapon * weapon = findItemWithSubType<Weapon>(ITEM_TYPE_WEAPON);
    if(weapon != NULL && weapon->isWorking()) {
        critProb = incByPercent(critProb, weapon->getCritProb());
    }
    return critProb;
}

float Equipment::getDodgeProb() const {
    float dodgeProb = 0;
    
    for_each_armor([&dodgeProb](const Armor * armor){
        if(armor->isWorking()){
            dodgeProb = incByPercent(dodgeProb, armor->getDodgeRating());
        }
        return true;
    });
    return dodgeProb;
}

unsigned int Equipment::getArmorRating() const {
    unsigned int armorRating = 0;
    
    for_each_armor([&armorRating](const Armor * armor){
        if(armor->isWorking()) {
            armorRating += armor->getArmorRating();
        }
        return true;
    });
    return armorRating;
}

float Equipment::getBlockProb() const {
    float blockProb = 0;
    Shield * shield = findItemWithSubType<Shield>(ARMOR_TYPE_SHIELD);
    if(shield != NULL && shield->isWorking()) {
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

std::string Equipment::getDescription() const {
    return getPersonalDescription() + "\n" + getStatisticalDescription() + "\n" + TEXT_DIVIDER + "\n" + getStorageListAsString();
}

std::string Equipment::getPersonalDescription() const {
    return PhysicalObject::getPersonalDescription() + "These are your equipped items their stats.";
}

std::string Equipment::getStatisticalDescription() const {
    std::string desc = "Armor rating: " + std::to_string(getArmorRating());
    desc += "\nDodge prob: " + std::to_string(convertPercent(getDodgeProb()));
    desc += "\nBlock prob: " + std::to_string(convertPercent(getBlockProb()));
    desc += "\nDmg: " + std::to_string(getMinDmg()) + "-" + std::to_string(getMaxDmg());
    desc += "\nCrit prob: " + std::to_string(convertPercent(getCritProb()));
    desc += "\nCrit mod: " + std::to_string(getCritMod());
    return desc;
}

Equipment * Equipment::clone() const {
    throw std::runtime_error("Equipment is not cloneable.");
}
