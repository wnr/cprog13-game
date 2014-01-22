#include "Troll.h"
#include "rand.h"
#include "Environment.h"

using namespace game;

Troll::Troll(Environment * env) : Troll(env, CHARACTER_TYPE_TROLL, TROLL_HEALTH) {}
Troll::Troll(Environment * env, std::string subType, unsigned int maxHealth) : Troll(env, subType, maxHealth, subType) {}
Troll::Troll(Environment * env, std::string subType, unsigned int maxHealth, std::string name) : Troll(env, subType, maxHealth, name, TROLL_MOVE_PROB, TROLL_ATTACK_PROB) {}
Troll::Troll(Environment * env, std::string subType, unsigned int maxHealth, std::string name, float moveProb, float attackProb) : Monster(env, subType, maxHealth, name, moveProb, attackProb) {}

Troll::Troll(const Troll & troll)   : Monster(troll) {}
Troll::Troll(Troll && troll)        : Monster(troll) {}

Troll::~Troll() {}

void Troll::update() {
    Monster::update();
    
    if(!isAlive()) {
        return;
    }
    
    bool tickConsumed = false;
    
    if(happen(getAttackProb())) {
        //Pick random from env.
        
        Character * target = getEnvironment()->random<Character>("Character", {this});
        
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

void Troll::interact(Character * other) {
    if(!isAlive()) {
        return;
    }
    
    other->attack(this, Attack(getAttackPower(), "scratched"));
    
    if(other->isAlive()) {
        other->interact(this);
    }
}

std::string Troll::getPersonalDescription() const {
    return "A ugly " + getName() + " who does not fancy your good looks. Watch out!";
}

unsigned int Troll::getBaseAttackPower() const {
    return rand(300, 500);
}