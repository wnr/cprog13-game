#include "Player.h"
#include "Environment.h"
#include "Engine.h"

#include "Constants.h"
#include "Log.h"

#include <iostream>

using namespace game;

Player::Player(int maxHealth, std::string name) : Character(name, maxHealth, ENTITY_PLAYER_TYPE) {
    initCommands();
}

Player::Player(const Player & player) : Character(player), commands(player.commands) {}

Player::Player(Player && player) : Character(player), commands(player.commands) {}

Player::~Player() {}

void Player::update(const Environment & env) {
    std::cout << std::endl << "Your are in " << env.getDescription() << std::endl;
    
    std::cout << "You can go:" << std::endl;
    
    for(auto dir : env.getDirections()) {
        std::cout << dir << std::endl;
    }
    
    if(env.getEntities().size() > 0) {
        std::cout << "-----------" << std::endl;
        std::cout << "You can see the following:" << std::endl;
        
        for(auto entity : env.getEntities()) {
            std::cout << entity->getDescription() << std::endl;
        }
    }
    
    
    std::cout << INPUT_INDICATOR;
    
    if(!performCommand(getEngine().getInput())) {
        std::cout << INPUT_INVALID_COMMAND;
        std::cout << std::endl;
    }
}

void Player::initCommands() {
    commands["exit"] = [this](const std::vector<std::string> &) -> bool {
        this->getEngine().kill();
        return true;
    };
    
    commands["go"] = [this](const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            return false;
        }
     
        return this->move(commands[1]);
     };
    
    commands["help"] = [this](const std::vector<std::string> &) -> bool {
        std::cout << std::endl;
        std::cout << TEXT_DIVIDER << " HELP START " << TEXT_DIVIDER << std::endl;
        std::cout << HELP_TEXT << std::endl;
        std::cout << TEXT_DIVIDER << " HELP END " << TEXT_DIVIDER << std::endl;
        return true;
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

std::string Player::toString() const {
    return Character::toString() + ":Player";
}