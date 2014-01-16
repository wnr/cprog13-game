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

void Player::update() {
    Environment & env = *getEnvironment();
    std::cout << std::endl << "Location: " << env.getFullInfo() << std::endl;
    
    std::cout << "You can goto:" << std::endl;
    
    for(auto dir : env.getDirections()) {
        std::cout << dir << std::endl;
    }
    
    //If only 1 thing in environment then it is the player itself, so skip then.
    if(env.size() > 1) {
        std::cout << "-----------" << std::endl;
        std::cout << "You can see the following:" << std::endl;
        
        env.for_each([this](const PhysicalObject * entity) {
            if(entity == this) {
                return true; //Skip when entity is the player itself.
            }
            
            std::cout << entity->getDescription() << std::endl;
            return true;
        });
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
    
    commands["move"] = commands["goto"] = commands["go"] = [this](const std::vector<std::string> & commands) -> bool {
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
        
        Environment * env = getEnvironment();

        auto findTarget = [env](std::string target) -> Character * {
            std::transform(target.begin(), target.end(), target.begin(), ::tolower);
            Character * found = NULL;
            env->for_each([&found, target] (PhysicalObject * obj) {
                if(obj->getSubType() == ENTITY_MONSTER_TYPE) {
                    Character * entity = static_cast<Character*>(obj);
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
        
        auto entity = findTarget(commands[1]);
        
        if(entity == NULL) {
            std::cout << "There is no " + commands[1] << " in the area." << std::endl;
            return false;
        }
        
        interact(entity);
        
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

void Player::interact(game::Character * other) {
    if(!isAlive()) {
        return;
    }
    
    std::cout << "You can do the following:" << std::endl;
    
    std::cout << "kick" << std::endl;
    std::cout << "hit" << std::endl;
    
    std::map<std::string, std::function<bool()>> actions;
    
    actions["kick"] = [&other]() {
        other->decHealth(3);
        std::cout << "You kicked " + other->getDescription() << " for 3 hp!" << std::endl;
        return true;
    };
    actions["hit"] = [&other]() {
        other->kill();
        std::cout << "You hit " + other->getDescription() << " for all the hp!" << std::endl;
        return true;
    };
    actions["flee"] = []() {
        return true;
    };
    
    auto performAttackCommand = [&actions](const std::vector<std::string> & input) -> bool {
        if(input.empty()) {
            return false;
        }
        
        std::string key = input[0];
        
        if(actions.count(key) == 0) {
            return false;
        }
        
        auto action = actions[key];
        return action();
    };
    
    while(!performAttackCommand(getEngine().getInput())) {
        std::cout << INPUT_INVALID_COMMAND << std::endl;
    }
    
    if(!other->isAlive()) {
        std::cout << "You killed " << other->getDescription() << "!" << std::endl;
        return;
    }
    
    other->interact(this);
}