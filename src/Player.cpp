#include "Player.h"
#include "Environment.h"
#include "Engine.h"

#include "Constants.h"
#include "Log.h"

#include <iostream>

using namespace game;

Player::Player(unsigned int maxHealth, std::string name) : Character(name, maxHealth, ENTITY_PLAYER_TYPE) {
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
    
    auto envEntities = env.getEntities();
    
    if(envEntities.size() > 0) {
        std::cout << "-----------" << std::endl;
        std::cout << "You can see the following:" << std::endl;
        
        for(auto entity : envEntities) {
            std::cout << entity->getDescription() << std::endl;
        }
    }
    
    std::cout << INPUT_INDICATOR;
    
    if(!performCommand(getEngine().getInput())) {
        std::cout << INPUT_INVALID_COMMAND << std::endl;
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
    
    commands["help"] = [](const std::vector<std::string> &) -> bool {
        std::cout << std::endl;
        std::cout << TEXT_DIVIDER << " HELP START " << TEXT_DIVIDER << std::endl;
        std::cout << HELP_TEXT << std::endl;
        std::cout << TEXT_DIVIDER << " HELP END " << TEXT_DIVIDER << std::endl;
        return true;
    };
    
    commands["attack"] = [this](const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            return false;
        }

        auto findTarget = [this](std::string target) -> Entity * {
            std::transform(target.begin(), target.end(), target.begin(), ::tolower);
            
            std::string desc;
            for(auto entity : this->env->getEntities()) {
                if(entity->getType() == ENTITY_MONSTER_TYPE) {
                    desc = entity->getDescription();
                    std::transform(desc.begin(), desc.end(), desc.begin(), ::tolower);
                    
                    if(desc == target) {
                        return entity;
                    }
                }
            }
            
            return NULL;
        };
        
        Entity * entity = findTarget(commands[1]);
        
        if(entity == NULL) {
            std::cout << "There is no " + commands[1] << " in the area." << std::endl;
            return false;
        }
        
        entity->kill();
        env->removeEntity(entity);
        
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