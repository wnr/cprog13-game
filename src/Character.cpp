#include "Character.h"
#include "Constants.h"
#include "Backpack.h"
#include "Container.h"
#include "Environment.h"
#include "Food.h"
#include "Equipment.h"
#include "BreakableItem.h"
#include "Armor.h"
#include "Weapon.h"

using namespace game;

Character::Attack::Attack(unsigned int health) : Character::Attack::Attack(health, "") {}
Character::Attack::Attack(unsigned int health, std::string description) : health(health), description(description) {}

Character::Character(Environment * env, std::string subType, unsigned int maxHealth) : Character(env, subType, maxHealth, subType) {}
Character::Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Character(env, subType, maxHealth, name, CHARACTER_INVENTORY_SIZE) {}

Character::Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name, unsigned int inventorySize) : PhysicalObject(OBJECT_TYPE_CHARACTER, subType, name), alive(true), env(env), inventory(new Backpack(inventorySize)), equipment(new Equipment()), rottenness(0), maxHealth(maxHealth), health(maxHealth), interacting(false) {
    setTickSync(env->getTickSync());
    env->push_back(std::unique_ptr<PhysicalObject>(this));
}

//TODO: When characters are copied, shouldn't they add themselves to the env again since we now have 2 characters?
Character::Character(const Character & character)   : PhysicalObject(character), alive(character.alive), env(character.env), inventory(character.inventory), rottenness(character.rottenness), maxHealth(character.maxHealth), health(character.health), interacting(character.interacting) {}
Character::Character(Character && character)        : PhysicalObject(character), alive(character.alive), env(character.env), inventory(character.inventory), rottenness(character.rottenness), maxHealth(character.maxHealth), health(character.health), interacting(character.interacting) {}

Character::~Character() {}

Environment * Character::getEnvironment() const {
    return env;
}

Backpack * Character::getInventory() const {
    return inventory;
}

std::string Character::getName() const {
    if(!isAlive()) {
        return PhysicalObject::getName() + " corpse";
    }
    
    return PhysicalObject::getName();
}

bool Character::move(Environment * from, Environment * to) {
    env = to;
    to->push_back(from->remove(this));
    return true;
}

bool Character::move(const std::string &direction) {
    
    Environment * neighbor = env->getNeighbor(direction);
    
    if(neighbor == NULL) {
        //No neighbor in that direction.
        return false;
    }
    
    move(env, neighbor);
    
    return true;
}

void Character::dropInventory() {
    inventory->for_each([this](Item * item){
        dropItem(item);
        return true;
    });
}

bool Character::pickItem(const Item * item) {
    return item->move(env, inventory);
}

bool Character::pickItem(const Item * item, Container * con) {
    return item->move(con, inventory);
}

bool Character::dropItem(const Item * item) {
    return item->move(inventory, env);
}

bool Character::putItem(const Item * item, Container * con) {
    return item->move(inventory, con);
}

bool Character::isInteracting() const {
    return interacting;
}

bool Character::isAlive() const {
    return alive;
}

void Character::kill() {
    alive = false;
    setHealth(0);
}

unsigned int Character::getRottenness() const {
    return rottenness;
}

void Character::update() {
    PhysicalObject::update();
    
    if(!isAlive()) {
        if(++rottenness >= MAXIMUM_ROTTENNESS) {
            env->remove(this);
            return;
        }
    }
    
    inventory->update();
}

unsigned int Character::getMaxHealth() const {
    return maxHealth;
}

unsigned int Character::getHealth() const {
    return health;
}

void Character::setHealth(unsigned int health) {
    if(health > maxHealth) {
        throw std::invalid_argument("health must be set less than max health.");
    }
    
    this->health = health;
}

void Character::addHealth(int health) {
    int res = (int)this->health;
    res += health;
    
    if(res <= 0) {
        kill();
    } else if(res > maxHealth) {
        this->health = maxHealth;
    } else {
        setHealth(res);
    }
}

void Character::incHealth(unsigned int health) {
    addHealth(health);
}

void Character::decHealth(unsigned int health) {
    addHealth(-health);
}

bool Character::startInteraction(Character * other) {
    if(interacting) {
        return false;
    }

    if(!isAlive()) {
        return false;
    }
    
    interacting = true;
    
    return true;
}

void Character::endInteraction(Character * other) {
    interacting = false;
}
    
bool Character::eatFood(Food * food) {
    addHealth(food->getStrength());
    if(inventory->remove(food) != nullptr) {
        return true;
    } else {
        return true;
    }
}

Character::Attack Character::attack(const Character * attacker, unsigned int health) {
    return attack(attacker, Character::Attack(health));
}

Character::Attack Character::attack(const Character * attacker, unsigned int health, std::string description) {
    return attack(attacker, Character::Attack(health, description));
}

std::string Character::getPersonalDescription() const {
    return PhysicalObject::getPersonalDescription() + "A character of type " + getSubType();
}

std::string Character::getStatisticalDescription() const {
    std::string desc = "Health: " + unsignedValToString(getHealth()) + "/" + unsignedValToString(getMaxHealth());
    return desc;
}

bool Character::equip(const BreakableItem * bItem) {
    return bItem->move(inventory, equipment);
}

bool Character::unEquip(const BreakableItem * bItem) {
    return bItem->move(equipment, inventory);
}

Equipment * Character::getEquipment() const {
    return equipment;
}

unsigned int Character::getArmorRating() const {
    return equipment->getArmorRating() + getBaseArmorRating();
}

unsigned int Character::getDodgeProb() const {
    return (100.0 * incByPercent(equipment->getDodgeProb(), getBaseDodgeProb())) + 0.5;
}

unsigned int Character::getAttackPower() const {
    return equipment->getAttackPower() + getBaseAttackPower();
}

unsigned int Character::getBlockProb() const {
    return (100.0 * incByPercent(equipment->getBlockProb(), getBaseBlockProb())) + 0.5;
}

unsigned int Character::getBaseArmorRating() const {
    return 0;
}

unsigned int Character::getBaseDodgeProb() const {
    return 5;
}

unsigned int Character::getBaseAttackPower() const {
    return rand(1, 5, true);
}

unsigned int Character::getBaseBlockProb() const {
    return 0;
}

unsigned int Character::getBaseCritProb() const {
    return 5;
}

unsigned int Character::getBaseCritMod() const {
    return 50;
}

bool Character::isCriticalHit(unsigned int &attackPower) const {
    float critProb = incByPercent(0, getBaseCritProb());
    float critMod = getBaseCritMod();
    Weapon * weapon = equipment->findItemWithSubType<Weapon>(ITEM_TYPE_WEAPON);
    if(weapon != NULL) {
        critProb = incByPercent(critProb, weapon->getCritProb());
        critMod += weapon->getCritModifier();
    }
    if(happen(convertPercent(critProb))) {
        attackPower = (((critMod / 100.0) + 1.0) * (float)(attackPower));
        return true;
    } else {
        return false;
    }
}

unsigned int Character::blockMod(const unsigned int originalDmg) const {
    int blockPercent = rand(0, 3, true) * 25;
    return (originalDmg * blockPercent) / 100;
}

unsigned int Character::dodgeMod(const unsigned int originalDmg) const {
    return 0;
}

unsigned int Character::armorMod(const unsigned int originalDmg) const {
    if(originalDmg <= getArmorRating()) {
        return 0;
    } else {
        return originalDmg - getArmorRating();
    }
}

Character::Attack Character::attack(const Character * attacker, const Attack & attack) {
    unsigned int dodgeProb = getDodgeProb();
    unsigned int blockProb = getBlockProb();
    
    Attack actual(attack.health);
    
    actual.health = armorMod(actual.health);
    
    equipment->for_each_armor([this, actual, attack](Armor * armor){
        affectDurability(armor, attack.health - actual.health);
        return true;
    });
 
    if(actual.health == 0){
        actual.description = ATTACK_ABSORBED;
    } else if(happen(dodgeProb)) {
        actual.health = dodgeMod(actual.health);
        actual.description = ATTACK_DODGED;
    } else if(happen(blockProb)) {
        unsigned int preHP = actual.health;
        actual.health = blockMod(actual.health);
        unsigned int blocked = preHP - actual.health;
        actual.description = ATTACK_BLOCKED;
        actual.description = actual.description + "(" + unsignedValToString(blocked) + ")";
        affectDurability(equipment->findItemWithSubType(ARMOR_TYPE_SHIELD), blocked);
    }
    
    if(actual.description != ATTACK_DODGED) {
        attacker->affectDurability(attacker->getEquipment()->findItemWithSubType(ITEM_TYPE_WEAPON), attack.health);
    }
    
    return actual;
}
