#include "Troll.h"
#include "rand.h"

using namespace game;

Troll::Troll(Environment * env) : Troll(env, "Troll", 100) {}
Troll::Troll(Environment * env, std::string name, unsigned int maxHealth) : Troll(env, name, maxHealth, 0.0f, 0.0f) {}
Troll::Troll(Environment * env, std::string name, unsigned int maxHealth, float moveProb, float attackProb) : Monster(env, name, maxHealth, moveProb, attackProb) {}

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