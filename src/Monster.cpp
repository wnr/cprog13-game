#include "Monster.h"
#include "Constants.h"
#include "rand.h"
#include "Environment.h"

using namespace game;

Monster::Monster(Environment * env, std::string name, unsigned int maxHealth) : Monster(env, name, maxHealth, 0.0f, 0.0f) {}

Monster::Monster(Environment * env, std::string name, unsigned int maxHealth, float moveProb, float attackProb) : Character(env, name, maxHealth, ENTITY_TYPE_MONSTER), moveProb(moveProb), attackProb(attackProb) {}

Monster::Monster(const Monster & monster) : Character(monster), moveProb(monster.moveProb), attackProb(monster.attackProb) {}

Monster::Monster(Monster && monster) : Character(monster), moveProb(monster.moveProb), attackProb(monster.attackProb) {}

Monster::~Monster() {}

void Monster::update() {
    Character::update();
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

void Monster::interact(Character * other) {
    if(!isAlive()) {
        return;
    }
    
    other->attack(this, Attack(5, "scratched"));
    
    if(other->isAlive()) {
        other->interact(this);
    }
}

Monster::Attack Monster::attack(const Character * attacker, const Attack & attack) {
    static const unsigned int dodgeProb = 25;
    
    Attack actual(attack.health);
    
    if(happen(dodgeProb)) {
        actual.health = 0;
    }
    
    decHealth(actual.health);
    
    return actual;
}