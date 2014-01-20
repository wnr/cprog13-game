#include "Ghost.h"
#include "Constants.h"
#include "Environment.h"

using namespace game;

Ghost::Ghost(Environment * env) : Ghost(env, GHOST_NAME, GHOST_HEALTH, GHOST_MOVE_PROB, GHOST_ATTACK_PROB) {}

Ghost::Ghost(Environment * env, std::string name, unsigned int maxHealth) : Ghost(env, name, maxHealth, GHOST_MOVE_PROB, GHOST_ATTACK_PROB) {}

Ghost::Ghost(Environment * env, std::string name, unsigned int maxHealth, float moveProb, float attackProb) : Monster(env, name, maxHealth, moveProb, attackProb) {}

Ghost::Ghost(const Ghost & ghost) : Monster(ghost) {}

Ghost::Ghost(Ghost && ghost) : Monster(ghost) {}

Ghost::~Ghost() {}

void Ghost::kill() {
    Monster::kill();
    getEnvironment()->remove(this);
}

Ghost::Attack Ghost::attack(const Character * attacker, const Attack & attack) {
    return Attack(0, "absorbed");
}