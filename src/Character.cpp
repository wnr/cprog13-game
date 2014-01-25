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
Character::Attack::Attack(unsigned int health, std::string mainDescription) :Character::Attack::Attack(health, mainDescription, "") {}
Character::Attack::Attack(unsigned int health, std::string mainDescription, std::string extraDescription) : health(health), mainDescription(mainDescription), extraDescription(extraDescription) {}

Character::Character(Environment * env, std::string subType) : Character(env, subType, CHARACTER_HEALTH) {}
Character::Character(Environment * env, std::string subType, unsigned int maxHealth) : Character(env, subType, maxHealth, subType) {}
Character::Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Character(env, subType, maxHealth, name, CHARACTER_INVENTORY_SIZE) {}

Character::Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name, unsigned int inventorySize) : Character(env, subType, maxHealth, name, inventorySize, CHARACTER_BASE_ARMOR, CHARACTER_BASE_DODGE, CHARACTER_BASE_BLOCK, CHARACTER_BASE_MIN_DMG, CHARACTER_BASE_MAX_DMG, CHARACTER_BASE_CRIT_PROB, CHARACTER_BASE_CRIT_MOD) {}

Character::Character(Environment * env, std::string subType, unsigned int maxHealth, std::string name, unsigned int inventorySize, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod) : PhysicalObject(OBJECT_TYPE_CHARACTER, subType, name), alive(true), env(env), inventory(new Backpack(inventorySize)), equipment(new Equipment()), rottenness(0), maxHealth(maxHealth), health(maxHealth), interacting(false), baseArmorRating(baseArmorRating), baseDodgeProb(baseDodgeProb), baseBlockProb(baseBlockProb), baseMinDmg(baseMinDmg), baseMaxDmg(baseMaxDmg), baseCritProb(baseCritProb), baseCritMod(baseCritMod) {
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

void Character::setRottenness(unsigned int rottenness) {
    this->rottenness = rottenness;
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

Character::Attack Character::attack(Character * attacker, unsigned int health) {
    return attack(attacker, Character::Attack(health));
}

Character::Attack Character::attack(Character * attacker, unsigned int health, std::string description) {
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
    return convertPercent(incByPercent(equipment->getDodgeProb(), getBaseDodgeProb()));
}

unsigned int Character::getAttackPower() const {
    return rand(getMinDmg(), getMaxDmg(), true);
}

unsigned int Character::getMinDmg() const {
    return equipment->getMinDmg() + getBaseMinDmg();
}

unsigned int Character::getMaxDmg() const {
    return equipment->getMaxDmg() + getBaseMaxDmg();
}

unsigned int Character::getBlockProb() const {
    return convertPercent(incByPercent(equipment->getBlockProb(), getBaseBlockProb()));
}

unsigned int Character::getCritProb() const {
    return convertPercent(incByPercent(equipment->getCritProb(), getBaseCritProb()));
}

unsigned int Character::getCritMod() const {
    return equipment->getCritMod() + getBaseCritMod();
}

unsigned int Character::getBaseArmorRating() const {
    return baseArmorRating;
}

unsigned int Character::getBaseDodgeProb() const {
    return baseDodgeProb;
}

unsigned int Character::getBaseMinDmg() const {
    return baseMinDmg;
}

unsigned int Character::getBaseMaxDmg() const {
    return baseMaxDmg;
}

unsigned int Character::getBaseBlockProb() const {
    return baseBlockProb;
}

unsigned int Character::getBaseCritProb() const {
    return baseCritProb;
}

unsigned int Character::getBaseCritMod() const {
    return baseCritMod;
}

bool Character::isCriticalHit(unsigned int &attackPower) const {
    unsigned int critProb = getCritProb();
    unsigned int critMod = getCritMod();
    if(happen(critProb)) {
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

Character::Attack Character::generateAttack(std::string attackType) const {
    unsigned int attackPower = getAttackPower();
    if(isCriticalHit(attackPower)) {
        attackType = "critical " + attackType;
    }
    return Character::Attack(attackPower, attackType);
}

Character::Attack Character::performAttack(Character * defender, std::string attackType) {
    return defender->attack(this, generateAttack(attackType));
}

Character::Attack Character::attack(Character * attacker, const Attack & attack) {
    unsigned int dodgeProb = getDodgeProb();
    unsigned int blockProb = getBlockProb();
    
    Attack actual(attack.health);
    
    actual.health = armorMod(actual.health);
    
    equipment->for_each_armor([this, actual, attack](Armor * armor){
        affectDurability(armor, attack.health - actual.health);
        return true;
    });
 
    if(actual.health == 0){
        actual.mainDescription = ATTACK_ABSORBED;
    } else if(happen(dodgeProb)) {
        actual.health = dodgeMod(actual.health);
        actual.mainDescription = ATTACK_DODGED;
    } else if(happen(blockProb)) {
        unsigned int preHP = actual.health;
        actual.health = blockMod(actual.health);
        unsigned int blocked = preHP - actual.health;
        actual.mainDescription = ATTACK_BLOCKED;
        actual.mainDescription = actual.mainDescription + "(" + unsignedValToString(blocked) + ")";
        affectDurability(equipment->findItemWithSubType(ARMOR_TYPE_SHIELD), blocked);
    }
    
    if(actual.mainDescription != ATTACK_DODGED) {
        unsigned int durAffectedAttackPower = attack.health;
        if(getHealth() < attack.health) {
            // Attackpower affected durability of the weapon can never be higher than someones health.
            durAffectedAttackPower = getHealth();
        }
        attacker->affectDurability(attacker->getEquipment()->findItemWithSubType(ITEM_TYPE_WEAPON), durAffectedAttackPower);
    }
    
    return actual;
}

void Character::addMaxHealth(int amount) {
    int newMaxHealth = getMaxHealth() + amount;
    if(newMaxHealth < 1) {
        setMaxHealth(1);
    } else {
        setMaxHealth(newMaxHealth);
    }
}

void Character::setMaxHealth(unsigned int health) {
    if(health == 0) {
        throw std::invalid_argument("Max health can not be set to 0.");
    }
    
    maxHealth = health;
    if(getHealth() > maxHealth) {
        setHealth(maxHealth);
    }
}

Character * Character::getRandomTarget(std::function<bool(Character*)> operation) const {
    return getEnvironment()->random<Character>("Character", {this}, [&operation](Character * c){
        if(c->isAlive() && !c->isInteracting()){
            if(operation(c)){
                return true;
            }
        }
        return false;
    });
}