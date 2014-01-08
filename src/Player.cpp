#include "Player.h"

using namespace game;

Player::Player(Engine * engine, std::string name) : Entity(engine, ENTITY_PLAYER_TYPE), name(name) {}

Player::Player(const Player & player) : Entity(player), name(player.name) {}

Player::Player(Player && player) : Entity(player), name(player.name) {}

void Player::update() {
    
}