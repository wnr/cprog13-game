#include "Demon.h"
#include "rand.h"

using namespace game;

Demon::Demon(Environment * env) : Demon(env, "Demon", 5000) {}
Demon::Demon(Environment * env, std::string name, unsigned int maxHealth) : Demon(env, name, maxHealth, 0.0f, 0.0f) {}
Demon::Demon(Environment * env, std::string name, unsigned int maxHealth, float moveProb, float attackProb) : Monster(env, name, maxHealth, moveProb, attackProb) {}

Demon::~Demon() {}

void Demon::interact(Character * other) {
    if(!isAlive()) {
        return;
    }
    
    other->attack(this, Attack(6666, "soul eaten"));
    
    if(other->isAlive()) {
        other->interact(this);
    }
}

Demon::Attack Demon::attack(const Character * attacker, const Attack & attack) {
    static const unsigned int dodgeProb = 25;
    static const float reduction = 0.8f;
    
    Attack actual((1.0f - reduction) * attack.health);
    
    if(happen(dodgeProb)) {
        actual.health = 0;
    }
    
    decHealth(actual.health);
    
    return actual;
}