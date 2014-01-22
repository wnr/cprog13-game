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

void Troll::interact(Character * other) {
    if(!isAlive()) {
        return;
    }
    
    other->attack(this, Attack(5, "scratched"));
    
    if(other->isAlive()) {
        other->interact(this);
    }
}

Troll::Attack Troll::attack(const Character * attacker, const Attack & attack) {
    static const unsigned int dodgeProb = 25;
    
    Attack actual(attack.health);
    
    if(happen(dodgeProb)) {
        actual.health = 0;
    }
    
    decHealth(actual.health);
    
    return actual;
}

std::string Troll::getPersonalDescription() const {
    return "A ugly " + getName() + " who does not fancy your good looks. Watch out!";
}