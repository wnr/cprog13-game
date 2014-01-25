#include "Monster.h"
#include "Constants.h"
#include "Environment.h"

using namespace game;

Monster::Monster(Environment * env, std::string subType, unsigned int maxHealth) : Monster(env, subType, maxHealth, subType) {}
Monster::Monster(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Monster(env, subType, maxHealth, name, 0.0f, 0.0f) {}
Monster::Monster(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb) : Monster(env, subType, maxHealth, name, moveProb, attackProb, MONSTER_BASE_ARMOR, MONSTER_BASE_DODGE, MONSTER_BASE_BLOCK, MONSTER_BASE_MIN_DMG, MONSTER_BASE_MAX_DMG, MONSTER_BASE_CRIT_PROB, MONSTER_BASE_CRIT_MOD) {}

Monster::Monster(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod) : Character(env, subType, maxHealth, name, CHARACTER_INVENTORY_SIZE, baseArmorRating, baseDodgeProb, baseBlockProb, baseMinDmg, baseMaxDmg, baseCritProb, baseCritMod), moveProb(moveProb), attackProb(attackProb) {}

Monster::Monster(const Monster & monster)   : Character(monster), moveProb(monster.moveProb), attackProb(monster.attackProb) {}
Monster::Monster(Monster && monster)        : Character(monster), moveProb(monster.moveProb), attackProb(monster.attackProb) {}

Monster::~Monster() {}

void Monster::update() {
    Character::update();
    
    if(!isAlive()) {
        return;
    }
    
    bool tickConsumed = false;
    
    if(happen(getAttackProb())) {
        //Pick random from env.
        
        Character * target = getRandomTarget();
        
        if(target != NULL && target->startInteraction(this)) {
            startInteraction(target);
            interact(target);
            target->endInteraction(this);
            endInteraction(target);
            tickConsumed = true;
        }
    }
    
    if(!tickConsumed && happen(getMoveProb())) {
        Environment * env = getEnvironment()->randomNeighbor();
        
        if(env != NULL) {
            move(getEnvironment(), env);
            tickConsumed = true;
        }
    }
}

float Monster::getMoveProb() const {
    return moveProb;
}

void Monster::setMoveProb(float prob) {
    if(prob > 1) {
        throw std::invalid_argument("move prob is set greater than 1.");
    } else if(prob < 0) {
        throw std::invalid_argument("move prob is set less than 0.");
    }
    
    moveProb = prob;
}

void Monster::addMoveProb(float prob) {
    float res = moveProb + prob;
    
    if(res < 0) {
        res = 0;
    } else if(res > 1) {
        res = 1;
    }
    
    setMoveProb(res);
}

void Monster::incMoveProb(float prob) {
    addMoveProb(prob);
}

void Monster::decMoveProb(float prob) {
    addMoveProb(-prob);
}

float Monster::getAttackProb() const {
    return attackProb;
}

void Monster::setAttackProb(float prob) {
    if(prob > 1) {
        throw std::invalid_argument("attack prob is set greater than 1.");
    } else if(prob < 0) {
        throw std::invalid_argument("attack prob is set less than 0.");
    }
    
    attackProb = prob;
}

void Monster::addAttackProb(float prob) {
    float res = attackProb + prob;
    
    if(res < 0) {
        res = 0;
    } else if(res > 1) {
        res = 1;
    }
    
    setAttackProb(res);
}

void Monster::incAttackProb(float prob) {
    addAttackProb(prob);
}

void Monster::decAttackProb(float prob) {
    addAttackProb(-prob);
}

Monster::Attack Monster::attack(Character * attacker, const Attack & attack) {
    Attack actual = Character::attack(attacker, attack);
    decHealth(actual.health);
    return actual;
}

void Monster::affectDurability(BreakableItem * bi, unsigned int power) const {}

Character * Monster::getRandomTarget() const {
    return getEnvironment()->random<Character>(OBJECT_TYPE_CHARACTER, {this}, [this](Character *c){
        if(c->isAlive() && !c->isInteracting() && c->getSubType() != getSubType()) {
            return true;
        }
        return false;
    });
}


void Monster::interact(Character * other) {
    if(!isAlive()) {
        return;
    }
    
    performAttack(other, getAttackType());
    
    if(other->isAlive()) {
        other->interact(this);
    }
}

std::string Monster::getAttackType() const {
    return "hit";
}


