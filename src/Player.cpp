#include "Player.h"
#include "Environment.h"
#include "Engine.h"
#include "Backpack.h"

#include "Constants.h"
#include "rand.h"

#include <iostream>

using namespace game;

Player::Player(Environment * env, unsigned int maxHealth, std::string name) : Character(env, name, maxHealth, ENTITY_TYPE_PLAYER) {
    initCommands();
}

Player::Player(const Player & player) : Character(player), commands(player.commands) {}

Player::Player(Player && player) : Character(player), commands(player.commands) {}

Player::~Player() {}

void Player::update() {
    Character::update();
    
    printUpdateInfo();
    
    do { std::cout << INPUT_INDICATOR; } while(!performCommand(getEngine().getInput()));
}

void Player::printUpdateInfo() const {
    Environment & env = *getEnvironment();
    
    std::cout << std::endl << "Location: " << env.getFullInfo() << std::endl;
    
    std::cout << "You can go to:" << std::endl;
    
    for(auto dir : env.getDirections()) {
        std::cout << LIST_ITEM_PREFIX << dir << std::endl;
    }

    //If only 1 thing in environment then it is the player itself, so skip then.
    if(env.size() > 1) {
        std::cout << "-----------" << std::endl;
        std::cout << "You can see the following:" << std::endl;
        
        env.for_each([this](const PhysicalObject * entity) {
            if(entity == this) {
                return true; //Skip when entity is the player itself.
            }
            
            std::cout << LIST_ITEM_PREFIX << entity->getDescription() << std::endl;
            return true;
        });
    }
}

void Player::initCommands() {
    commands["look"] = [this](const std::vector<std::string> & commands) -> bool {
        printUpdateInfo();
        return true;
    };
    
    commands["exit"] = [this](const std::vector<std::string> &) -> bool {
        this->getEngine().kill();
        return true;
    };
    
    commands["go"] = [this](const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            std::cout << "You forgot to write where you wanna go." << std::endl;
            return false;
        }
        
        return this->move(commands[1]);
    };
    commands["move"] = commands["go"];
    commands["goto"] = commands["go"];
    
    commands["pass"] = [](const std::vector<std::string> &) -> bool {
        return true;
    };
    commands["skip"] = commands["pass"];
    
    commands["help"] = [](const std::vector<std::string> &) -> bool {
        std::cout << std::endl;
        std::cout << TEXT_DIVIDER << " HELP START " << TEXT_DIVIDER << std::endl;
        std::cout << HELP_TEXT << std::endl;
        std::cout << TEXT_DIVIDER << " HELP END " << TEXT_DIVIDER << std::endl;
        return true;
    };
    
    commands["inventory"] = [this](const std::vector<std::string> &) -> bool {
        Backpack * inv = getInventory();
        std::cout << "Inventory (" << inv->getTakenSpace() << "/" << inv->getMaxSize() << ")" << std::endl << TEXT_DIVIDER << std::endl;
        std::cout << inv->storageListToString();
        return true;
    };
    commands["backpack"] = commands["inventory"];
    commands["inv"] = commands["inventory"];
    
    commands["pick"] = [this](const std::vector<std::string> & commands) -> bool {
        if(commands.size() < 2) {
            std::cout << "You forgot to write what you wanted to pick up." << std::endl;
            return false;
        }
        
        Environment * env = getEnvironment();
        if(commands.size() == 2) {
            Item * item = env->find<Item>(OBJECT_TYPE_ITEM, commands[1]);
            if(item == NULL) {
                std::cout << "Found no item named: " << commands[1] << std::endl;
                return false;
            }
            
            if(!pickItem(item)) {
                std::cout << "You can't pick up item: " << commands[1] << std::endl;
                return false;
            }
            
            std::cout << "You picked up item: " << commands[1] << std::endl;
            
            return true;
        } else if(commands.size() == 3) {
            Container * container = env->find<Container>(OBJECT_TYPE_CONTAINER, commands[1]);
            if(container == NULL) {
                std::cout << "Found no container named: " <<commands[1] << std::endl;
                return false;
            }
            
            Item * item = container->find<Item>(OBJECT_TYPE_ITEM, commands[2]);
            if(item == NULL) {
                std::cout << "Found no item named: " << commands[2] << " in container: " << commands[1] << std::endl;
                return false;
            }
            
            if(!pickItem(item, container)) {
                std::cout << "You can't pick up item: " << commands[2] << " in container: " << commands[1] << std::endl;
                return false;
            }

            std::cout << "You picked up item: " << commands[2] << " from container: " << commands[1]<< std::endl;
            
            return true;
        }
        
        std::cout << "Invalid command syntax. Usage: pick [CONTAINER] ITEM" << std::endl;
        return false;
    };
    
    commands["drop"] = [this](const std::vector<std::string> & commands) -> bool {
        if(commands.size() < 2) {
            std::cout << "You forgot to write what you wanted to drop." << std::endl;
            return false;
        }
        
        Backpack * inv = getInventory();
        if(commands.size() == 2) {
            Item * item = inv->find<Item>(OBJECT_TYPE_ITEM, commands[1]);
            if(item == NULL) {
                std::cout << "Found no item named: " << commands[1] << " in your inventory." << std::endl;
                return false;
            }
            
            if(!dropItem(item)) {
                std::cout << "You can't drop item: " << commands[2] << " from your inventory. " << std::endl;
                return false;
            }
            
            std::cout << "You dropped item: " << commands[2] << " from your inventory. " << std::endl;
            
            return true;
        } else if(commands.size() == 3) {
            Environment * env = getEnvironment();
            Container * container = env->find<Container>(OBJECT_TYPE_CONTAINER, commands[1]);
            if(container == NULL) {
                std::cout << "Found no container named: " <<commands[1] << std::endl;
                return false;
            }
            
            Item * item = inv->find<Item>(OBJECT_TYPE_ITEM, commands[2]);
            if(item == NULL) {
                std::cout << "Found no item named: " << commands[2] << " in your inventory." << std::endl;
                return false;
            }
            
            if(!putItem(item, container)) {
                std::cout << "You can't put item: " << commands[2] << " in container: " << commands[1] << std::endl;
                return false;
            }
            
            std::cout << "You put item: " << commands[2] << " in container: " << commands[1] << std::endl;

            return true;
        }
        
        std::cout << "Invalid command syntax. Usage: drop [CONTAINER] ITEM" << std::endl;
        return false;
    };
    
    commands["put"] = commands["drop"];
        
    commands["open"] = [this](const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            std::cout << "You forgot to write what you wanted to open." << std::endl;
            return false;
        }
        
        Environment * env = getEnvironment();
        Container * container = env->find<Container>(OBJECT_TYPE_CONTAINER, commands[1]);
        if(container == NULL) {
            std::cout << "Found no container named: " <<commands[1] << std::endl;
            return false;
        }
        
        int takenSpace = container->getTakenSpace();
        std::string takenSpaceText = std::to_string(takenSpace);
        if(takenSpace == -1){
            takenSpaceText = "UNKNOWN";
        }
        
        std::cout << container->getDescription() << " (" << takenSpaceText << "/" << container->getMaxSize() << ")" << std::endl << TEXT_DIVIDER << std::endl;
        std::cout << container->storageListToString();
        
        return true;
    };
    
    commands["attack"] = [this](const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            std::cout << "You forgot to write what you wanted to attack." << std::endl;
            return false;
        }
        
        Environment * env = getEnvironment();

        auto findTarget = [env](std::string target) -> Character * {
            std::transform(target.begin(), target.end(), target.begin(), ::tolower);
            Character * found = NULL;
            env->for_each([&found, target] (PhysicalObject * obj) {
                if(obj->getSubType() == ENTITY_TYPE_MONSTER) {
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
        
        std::cout << std::endl << "You are initiating a fight with " << entity->getDescription() << "!" << std::endl;
        
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
    
    bool flee = false;
    const std::string desc = other->getDescription();
    const auto self = this;
    
    std::map<std::string, std::function<bool()>> actions;
    
    actions["kick"] = [self, &other, &desc]() {
        auto res = other->attack(self, 3);
        
        if(res == 0) {
            std::cout << "The " << desc << " blocked your attack!" << std::endl;
        } else {
            std::cout << "You kicked " + desc << " for " + std::to_string(res) + " hp!" << std::endl;
        }
        
        return true;
    };
    
    actions["hit"] = [self, &other, &desc]() {
        auto res = other->attack(self, other->getHealth());
        
        if(res == 0) {
            std::cout << "The " + desc << " blocked your attack!" << std::endl;
        } else {
            std::cout << "You hit " + desc << " for " + std::to_string(res) + " hp!" << std::endl;
        }
        
        return true;
    };
    
    actions["flee"] = [&flee]() {
        flee = true;
        return true;
    };
    
    std::cout << "You have " << getHealth() << "/" << getMaxHealth() << " health and ";
    std::cout << other->getDescription() << " has " << other->getHealth() << "/" << other->getMaxHealth() << " health." << std::endl;

    std::cout << "You can do the following:" << std::endl;
    for(auto & kv : actions) {
        std::cout << LIST_ITEM_PREFIX << kv.first << std::endl;
    }
    
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
    
    do { std::cout << INPUT_INDICATOR; } while(!performAttackCommand(getEngine().getInput()));
    
    if(!other->isAlive()) {
        std::cout << "You killed " << desc << "!" << std::endl;
        return;
    }
    
    if(!flee) {
        other->interact(this);
    }
}

Player::Attack Player::attack(const Character * attacker, const Attack & attack) {
    static const unsigned int dodgeProb = 10;
    
    Attack actual(attack.health);
    
    if(happen(dodgeProb)) {
        auto printAvoid = [&actual](const std::string & desc){
            std::cout << "You avoided getting " + desc + " by dodging the attack!" << std::endl;
        };
        
        printAvoid(attack.description.empty() ? "hit" : attack.description);
        actual.health = 0;
    } else {
        auto printAttack = [&actual](const std::string & desc){
            std::cout << "You got " + desc + " and lost " + std::to_string(actual.health) + " health!" << std::endl;
        };
        
        printAttack(attack.description.empty() ? "hit" : attack.description);
    }
    
    decHealth(actual.health);
    
    return actual;
}