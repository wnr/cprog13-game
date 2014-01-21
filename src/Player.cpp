#include "Player.h"
#include "Environment.h"
#include "Engine.h"
#include "Backpack.h"
#include "KeyLock.h"
#include "Container.h"

#include "Constants.h"
#include "rand.h"

#include <iostream>

using namespace game;

Player::Player(Environment * env, unsigned int maxHealth, std::string name) : Character(env, CHARACTER_TYPE_PLAYER, maxHealth, name) {
    initCommands();
}

Player::Player(const Player & player)   : Character(player), commands(player.commands) {}
Player::Player(Player && player)        : Character(player), commands(player.commands) {}

Player::~Player() {}

void Player::update() {
    Character::update();
    
    printUpdateInfo();
    
    do { std::cout << INPUT_INDICATOR; } while(!performCommand(getEngine()->getInput()));
}

void Player::printUpdateInfo() const {
    Environment * env = getEnvironment();
    
    std::cout << std::endl << "Location: " << env->getFullInfo() << std::endl;
    
    std::cout << "You can go to:" << std::endl;
    
    for(auto dir : env->getDirections()) {
        std::cout << LIST_ITEM_PREFIX << dir << std::endl;
    }

    //If only 1 thing in environment then it is the player itself, so skip then.
    if(env->size() > 1) {
        std::cout << "-----------" << std::endl;
        std::cout << "You can see the following:" << std::endl;
    
        std::cout << env->getStorageListAsString({(PhysicalObject*)this});
    }
}

void Player::initCommands() {
    commands["look"] = [this](const std::vector<std::string> & commands) -> bool {
        Environment * env = getEnvironment();
        if(commands.size() == 1) {
            printUpdateInfo();
        } else if(commands.size() == 2) {
            if(isCommandInventory(commands[1])) {
                std::cout << getInventory()->getDescription() << std::endl;
                return false;
            }
            PhysicalObject * physicalObject = env->find(commands[1]);
            if(physicalObject == NULL) {
                std::cout << "Found no item named: " << commands[1] << std::endl;
            } else {
                std::cout << physicalObject->getDescription() << std::endl;
            }
        } else if(commands.size() == 3) {
            Item * item = NULL;
            if(isCommandInventory(commands[1])) {
                Backpack * inv = getInventory();
                item = inv->find(commands[2]);
                if(item == NULL) {
                    std::cout << "Found no item named: " << commands[2] << " in your inventory." << std::endl;
                    return false;
                }
            } else {
                Container * con = env->find<Container>(OBJECT_TYPE_CONTAINER, commands[2]);
                if(con == NULL) {
                    std::cout << "Found no container named: " <<commands[1] << std::endl;
                    return false;
                } else {
                    item = con->find(commands[2]);
                    if(item == NULL) {
                        std::cout << "Found no item named: " << commands[2] << " in container: " << con->getName() << std::endl;
                        return false;
                    }
                }
            }
            std::cout << item->getDescription() << std::endl;
        }
        
        return false;
    };
    
    commands["exit"] = [this](const std::vector<std::string> &) -> bool {
        this->getEngine()->kill();
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
    commands["wait"] = commands["pass"];
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
        std::cout << inv->getDescription() << std::endl;
        return false;
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
            
            return false;
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
            
            return false;
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
            Item * item = inv->find(commands[1]);
            if(item == NULL) {
                std::cout << "Found no item named: " << commands[1] << " in your inventory." << std::endl;
                return false;
            }
            
            if(!dropItem(item)) {
                std::cout << "You can't drop item: " << commands[1] << " from your inventory. " << std::endl;
                return false;
            }
            
            std::cout << "You dropped item: " << commands[1] << " from your inventory. " << std::endl;
            return false;
            
        } else if(commands.size() == 3) {
            Environment * env = getEnvironment();
            Container * container = env->find<Container>(OBJECT_TYPE_CONTAINER, commands[1]);
            if(container == NULL) {
                std::cout << "Found no container named: " <<commands[1] << std::endl;
                return false;
            }
            
            Item * item = inv->find(commands[2]);
            if(item == NULL) {
                std::cout << "Found no item named: " << commands[2] << " in your inventory." << std::endl;
                return false;
            }
            
            if(!putItem(item, container)) {
                std::cout << "You can't put item: " << commands[2] << " in container: " << commands[1] << std::endl;
                return false;
            }
            
            std::cout << "You put item: " << commands[2] << " in container: " << commands[1] << std::endl;

            return false;
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
        std::string takenSpaceText = unsignedValToString(takenSpace);
        
        std::cout << container->getDescription() << std::endl;
        
        return false;
    };
    
    commands["attack"] = [this](const std::vector<std::string> & commands) -> bool {
        if(commands.size() != 2) {
            std::cout << "You forgot to write what you wanted to attack." << std::endl;
            return false;
        }
        
        Environment * env = getEnvironment();

        auto findTarget = [env](std::string target) -> Character * {
            target = toLowerCase(target);
            Character * found = NULL;
            env->for_each([&found, target] (PhysicalObject * obj) {
                if(obj->getSubType() == CHARACTER_TYPE_MONSTER) {
                    Character * character = static_cast<Character*>(obj);
                    std::string desc = character->getName();
                    desc = toLowerCase(desc);
                    if(desc == target) {
                        found = character;
                        return false;
                    }
                }
        
                return true;
            });
            
            return found;
        };
        
        auto character = findTarget(commands[1]);
        
        if(character == NULL) {
            std::cout << "There is no " + commands[1] << " in the area." << std::endl;
            return false;
        }
        
        std::cout << std::endl << "You are initiating a fight with " << character->getName() << "!" << std::endl;
        
        interact(character);
        
        return true;
    };
    
    commands["unlock"] = [this](const std::vector<std::string> & commands) -> bool {
        Environment * env = getEnvironment();
        Backpack * inv = getInventory();
        if(commands.size() < 3 || commands.size() > 4) {
            std::cout << "Invalid command syntax. Usage: unlock [CONTAINER] LOCKED_OBJECT KEY" << std::endl;
            return false;
        }
        KeyLock * lock = NULL;
        std::string containerString;
        std::string lockString;
        std::string keyString;
        if(commands.size() == 4) {
            lockString = commands[2];
            keyString = commands[3];
            Container * con;
            if(isCommandInventory(commands[1])) {
                con = inv;
            } else {
                con = env->find<Container>(OBJECT_TYPE_CONTAINER, commands[1]);
            }
            if(con == NULL) {
                std::cout << "Found no container named: " << commands[1] << std::endl;
                return false;
            }
            lock = dynamic_cast<KeyLock *>(con->find(commands[1]));
            
            containerString = " in container named: " + con->getName();

        } else if(commands.size() == 3) {
            containerString = "";
            lockString = commands[1];
            keyString = commands[2];
            lock = dynamic_cast<KeyLock *>(env->find(commands[1]));
        }
        if(lock == NULL) {
            std::cout << "Found no lockable object named: " << lockString << containerString << std::endl;
        return false;
        }
        Key * key = inv->find<Key>(OBJECT_TYPE_ITEM, ITEM_TYPE_KEY, keyString);
        if(key == NULL) {
            std::cout << "Found no key named: " << keyString  << " in your inventory."<< std::endl;
            return false;
        }
        std::string keyName = key->getName();
        PhysicalObject * test = dynamic_cast<PhysicalObject*>(lock); // Needed because not strictly
        if(test == nullptr) {
            throw std::runtime_error("The lockable item was not a PhysicalObject. Should not be possible.");
        }
        std::string lockName = test->getName();
        if(lock->unlock(key, *inv)) {
            std::cout << "You unlocked: " << lockName << containerString << " using key: " << keyName << std::endl;
            return true;
        } else {
            std::cout << "You can't unlock: " << lockName << containerString << " using key: " << keyName << std::endl;
            return false;
        }
    };
    
}

bool Player::performCommand(const std::vector<std::string> & input) {
    if(input.empty()) {
        return false;
    }
    
    std::string key = input[0];
    key = toLowerCase(key);

    
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
    const std::string desc = other->getName();
    const auto self = this;
    
    std::map<std::string, std::function<bool()>> actions;
    
    auto attack = [self, &desc, other](const std::string & attackDesc, unsigned int health) {
        Attack actual = other->attack(self, health);
        
        if(actual.health == 0) {
            std::cout << "The " << desc << " " << (actual.description.empty() ? "blocked" : actual.description) << " your " << attackDesc << "!" << std::endl;
        } else {
            std::cout << "You " << attackDesc << " " << desc << " for " << std::to_string(actual.health) << " hp!" << std::endl;
        }
    };
    
    actions["kick"] = [&attack]() {
        attack("kick", 3);
        return true;
    };
    
    actions["hit"] = [self, &other, &attack]() {
        attack("hit", other->getHealth());
        return true;
    };
    
    actions["flee"] = [&flee]() {
        flee = true;
        return true;
    };
    
    std::cout << "You have " << getHealth() << "/" << getMaxHealth() << " health and ";
    std::cout << other->getName() << " has " << other->getHealth() << "/" << other->getMaxHealth() << " health." << std::endl;

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
    
    do { std::cout << INPUT_INDICATOR; } while(!performAttackCommand(getEngine()->getInput()));
    
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

void Player::kill() {
    Character::kill();
    
    std::cout << "You died." << std::endl;
    getEngine()->kill();
}

bool Player::isCommandInventory(std::string command) const {
    command = toLowerCase(command);
    if(command == "inv" || command == "backpack" || command == "inventory") {
        return true;
    } else {
        return false;
    }
}