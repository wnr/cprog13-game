#include "Player.h"
#include "Environment.h"
#include "Engine.h"

#include "Constants.h"

#include <iostream>

using namespace game;

Player::Player(Engine * engine, std::string name) : Entity(engine, ENTITY_PLAYER_TYPE), name(name) {
    initCommands();
}

Player::Player(const Player & player) : Entity(player), name(player.name), commands(player.commands) {}

Player::Player(Player && player) : Entity(player), name(player.name), commands(player.commands) {}

void Player::update(const Environment & env) {
    std::cout << "Your are in " << env.getDescription() << std::endl;
    
    std::cout << "You can move:" << std::endl;
    
    for(auto dir : env.getDirections()) {
        std::cout << dir << std::endl;
    }
    
    std::cout << INPUT_INDICATOR;
    
    if(!performCommand(engine->getInput())) {
        std::cout << INPUT_INVALID_COMMAND;
        std::cout << std::endl;
    }
}

void Player::initCommands() {
    commands["exit"] = [this](const std::vector<std::string> &) -> bool {
        this->engine->kill();
        return true;
    };
    
    commands["go"] = [this](const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            return false;
        }
     
        return this->move(commands[1]);
     };
}

bool Player::performCommand(const std::vector<std::string> & input) {
    if(input.empty()) {
        return false;
    }
    
    std::string key = input[0];
    
    if(commands.count(key) == 0) {
        return false;
    }
    
    auto command = commands[key];
    return command(input);
}