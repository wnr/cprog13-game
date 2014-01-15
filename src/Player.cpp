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

void Player::update(Environment & env) {
    std::cout << std::endl << "Your are in " << env.getDescription() << std::endl;
    
    std::cout << "You can go:" << std::endl;
    
    for(auto dir : env.getDirections()) {
        std::cout << dir << std::endl;
    }
    
    //If only 1 thing in environment then it is the player itself, so skip then.
    if(env.size() > 1) {
        std::cout << "-----------" << std::endl;
        std::cout << "You can see the following:" << std::endl;
        
        env.for_each([this](const Object * entity) {
            if(entity == this) {
                return true; //Skip when entity is the player itself.
            }
            
            std::cout << entity->getDescription() << std::endl;
            return true;
        });
    }
    
    std::cout << INPUT_INDICATOR;
    
    if(!performCommand(env, getEngine().getInput())) {
        std::cout << INPUT_INVALID_COMMAND << std::endl;
    }
}

void Player::initCommands() {
    commands["exit"] = [this](Environment & env, const std::vector<std::string> &) -> bool {
        this->getEngine().kill();
        return true;
    };
    
    commands["go"] = [this](Environment & env, const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            return false;
        }
     
        return this->move(env, commands[1]);
     };
    
    commands["help"] = [](Environment & env, const std::vector<std::string> &) -> bool {
        std::cout << std::endl;
        std::cout << TEXT_DIVIDER << " HELP START " << TEXT_DIVIDER << std::endl;
        std::cout << HELP_TEXT << std::endl;
        std::cout << TEXT_DIVIDER << " HELP END " << TEXT_DIVIDER << std::endl;
        return true;
    };
    
    commands["attack"] = [this](Environment & env, const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            return false;
        }

        auto findTarget = [env](Environment & env, std::string target) -> Entity * {
            std::transform(target.begin(), target.end(), target.begin(), ::tolower);
            Entity * found = NULL;
            env.for_each([&found, target] (Object * obj) {
                if(obj->getSubType() == ENTITY_MONSTER_TYPE) {
                    Entity * entity = static_cast<Entity*>(obj);
                    std::string desc = entity->getDescription();
                    std::transform(desc.begin(), desc.end(), desc.begin(), ::tolower);
                    
                    if(desc == target) {
                        found = entity;
                        return false;
                    }
                }
        
                return true;
            });
            
            return found;
        };
        
        Entity * entity = findTarget(env, commands[1]);
        
        if(entity == NULL) {
            std::cout << "There is no " + commands[1] << " in the area." << std::endl;
            return false;
        }
        entity->kill();
        env.removeObject(entity);
        
        return true;
    };
}

bool Player::performCommand(Environment & env, const std::vector<std::string> & input) {
    if(input.empty()) {
        return false;
    }
    
    std::string key = input[0];
    
    if(commands.count(key) == 0) {
        return false;
    }
    
    auto command = commands[key];
    return command(env, input);
}