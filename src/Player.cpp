#include "Player.h"
#include "Environment.h"
#include "Engine.h"

#include "Constants.h"

#include <iostream>

using namespace game;

Player::Player(Engine * engine, std::string name) : Entity(engine, ENTITY_PLAYER_TYPE), name(name) {}

Player::Player(const Player & player) : Entity(player), name(player.name) {}

Player::Player(Player && player) : Entity(player), name(player.name) {}

void Player::update(const Environment & env) {
    std::cout << "Your are in " << env.getDescription() << std::endl;
    
    std::cout << "You can move:" << std::endl;
    
    for(auto dir : env.getDirections()) {
        std::cout << dir << std::endl;
    }
    
    std::cout << INPUT_INDICATOR;
    
    if(!engine->performCommand(engine->getInput())) {
        std::cout << INPUT_INVALID_COMMAND;
        std::cout << std::endl;
    }

}