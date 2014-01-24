#include "Player.h"
#include "Environment.h"
#include "Engine.h"
#include "Backpack.h"
#include "KeyLock.h"
#include "Container.h"
#include "Food.h"
#include "BreakableItem.h"
#include "Equipment.h"

#include "Constants.h"
#include "rand.h"

#include <set>
#include <map>
#include <iostream>
#include <vector>

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
    std::function<void (std::vector<std::string> commandWords, std::function<bool(const std::vector<std::string> &)>)> addCommands = [this](std::vector<std::string> commandWords, std::function<bool(const std::vector<std::string> &)> operation){
        if(commandWords.size() < 1) {
            throw std::invalid_argument("You must at least have one word associated with the command");
        }
        uniqueCommands.push_back(commandWords.front());
        for(std::string word: commandWords){
            if(commands.find(word) != commands.end()) {
                throw std::invalid_argument("The word: " + word + " is associated with more than one command");
            }
            commands[word] = operation;
        }
        
    };
    
    std::function<bool (const std::vector<std::string> & commands, const std::string & helpText, const std::string & usageCommands)> isHelp = [](const std::vector<std::string> & commands, const std::string & helpText, const std::string & usageCommands){
        if(commands.size() != 2){ return false; };
        if(commands[1] != "help"){ return false; };
        
        std::cout << TEXT_DIVIDER << " HELP: " << commands[0] << " " << TEXT_DIVIDER << std::endl;
        if(helpText != "") {
            std::cout << helpText << std::endl;
        }
        std::cout << "Usage: " << commands[0] << " " << usageCommands << std::endl;
        return true;
    };
    
    addCommands({"go", "move", "goto"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands, "Used for navigating through the world.", "LOCATION")) { return false;}
            
        if(commands.size() != 2) {
            std::cout << "You forgot to write where you wanna go." << std::endl;
            return false;
        }
        
        return this->move(commands[1]);
    });
    
    addCommands({"look"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands, "Look for example at different characters or on items to get more information. You can look at almost anything in the world.", "[CONTAINER] [OBJECT]")) { return false;}
        Environment * env = getEnvironment();
        if(commands.size() == 1) {
            printUpdateInfo();
        } else if(commands.size() == 2) {
            if(isCommandInventory(commands[1])) {
                std::cout << getInventory()->getDescription() << std::endl;
                return false;
            }
            if(isCommandEquipment(commands[1])) {
                std::cout << getEquipment()->getDescription() << std::endl;
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
            } else if(isCommandEquipment(commands[1])) {
                Equipment * eq = getEquipment();
                item = eq->find(commands[2]);
                if(item == NULL) {
                    std::cout << "Found no item named: " << commands[2] << " in your equipment." << std::endl;
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
    });
    
    addCommands({"stats"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands,"Get information about you.",  "")) { return false;}
        std::cout << getDescription() << std::endl;
        return false;
    });
    
    addCommands({"inventory", "backpack", "inv"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands, "Get information about your inventory that contains items.", "")) { return false;}
        Backpack * inv = getInventory();
        std::cout << inv->getDescription() << std::endl;
        return false;
    });
    
    addCommands({"equipment"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands, "Get information about your current equipment.", "")) { return false;}
        Equipment * eq = getEquipment();
        std::cout << eq->getDescription() << std::endl;
        return false;
    });
    
    addCommands({"pick"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands,"Pick up items from the ground or from containers like for example Chests.", "[CONTAINER] ITEM")) { return false;}
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
    });
    
    addCommands({"drop", "put"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands, "Drop items on the ground or drop them into containers.", "[CONTAINER] ITEM")) { return false;}
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
    });
    
    addCommands({"open"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands,"The same as 'look CONTAINER'.", "CONTAINER")) { return false;}
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
    });
    
    addCommands({"unlock"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands, "Unlock containers or items using this command.", "[CONTAINER] LOCKED_OBJECT KEY")) { return false;}
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
            return false;
        } else {
            std::cout << "You can't unlock: " << lockName << containerString << " using key: " << keyName << std::endl;
            return false;
        }
    });
    
    addCommands({"eat", "drink"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands,"Use this command to consume items. Tip: Write 'drink' so you don't accidentally chew liquids.", "ITEM")) { return false;}
        if(commands.size() != 2) {
            std::cout << "Invalid command syntax. Usage: eat FOOD" << std::endl;
            return false;
        }
        
        Consumable * cItem = getInventory()->find<Consumable>(OBJECT_TYPE_ITEM, ITEM_TYPE_CONSUMABLE, commands[1]);
        if(cItem == NULL) {
            std::cout << "Found no consumable item named: " << commands[1]  << " in your inventory."<< std::endl;
            return false;
        }
        
        std::string consumableName = cItem->getName();
        std::string response = cItem->consume(this);
        std::cout << "You digested " << consumableName  << " and " << response << std::endl;
        return false;
    });
    
    addCommands({"equip", "eq"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands, "Used for equipping items. You can only equip one of each type of equippable item.", "[ITEM]")) { return false;}
        if(commands.size() != 2) {
            std::cout << "Invalid command syntax. Usage: equip ITEM" << std::endl;
            return false;
        }
        
        Backpack * inv = getInventory();
        Item * item = inv->find(commands[1]);
        if(item == NULL) {
            std::cout << "Found no equipable item named: " << commands[1] << std::endl;
            return false;
        }
        
        BreakableItem * bItem = dynamic_cast<BreakableItem*>(item);
        if(bItem == nullptr) {
            std::cout << "The item: " << item->getName() << " is not equipable." << std::endl;
            return false;
        }
        
        if(equip(bItem)) {
            std::cout << "You equipeed item: " << bItem->getName() << std::endl;
            return false;
        } else {
            std::cout << "You failed to equip: " << bItem->getName() << std::endl;
            return false;
        }
    });
    
    addCommands({"unequip", "uneq", "ueq"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands,"Used for removing equipped items and putting them back to your inventory, if you have enough space.", "ITEM")) { return false;}
        if(commands.size() != 2) {
            std::cout << "Invalid command syntax. Usage: equip ITEM" << std::endl;
            return false;
        }
        
        Equipment * eq = getEquipment();
        BreakableItem * bItem = eq->find(commands[1]);
        if(bItem == NULL) {
            std::cout << "Found no equiped item named: " << commands[1] << std::endl;
            return false;
        }
        if(unEquip(bItem)) {
            std::cout << "You unequiped item: " << bItem->getName() << std::endl;
            return false;
        } else {
            std::cout << "You failed to unequip: " << bItem->getName() << std::endl;
            return false;
        }
    });
    
    addCommands({"attack", "att"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands, "KILL!", "CHARACTER")) { return false;}
        if(commands.size() != 2) {
            std::cout << "You forgot to write what you wanted to attack." << std::endl;
            return false;
        }
        
        Character * character = getEnvironment()->find<Character>(OBJECT_TYPE_CHARACTER, commands[1], {this});
        
        if(character == NULL) {
            std::cout << "There is no " + commands[1] << " in the area." << std::endl;
            return false;
        }
        
        if(!character->startInteraction(this)) {
            std::cout << "The " << character->getName() << " busy fighting already." << std::endl;
            return false;
        }
        
        std::cout << std::endl << "You are initiating a fight with " << character->getName() << "!" << std::endl;
        
        interact(character);
        
        character->endInteraction(this);
        endInteraction(character);
        
        
        return true;
    });
    
    addCommands({"pass", "wait", "skip"}, [isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands,"Wait a moment and let others take their turn.", "")) { return false;}
        return true;
    });
    
    addCommands({"exit"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands,"Exit the game. No turning back after this.", "")) { return false;}
        this->getEngine()->kill();
        return true;
    });
    
    addCommands({"help"}, [this, isHelp](const std::vector<std::string> & commands) -> bool {
        if(isHelp(commands,"Helpception?", "")) { return false;}
        std::cout << std::endl;
        std::cout << TEXT_DIVIDER << " HELP START " << TEXT_DIVIDER << std::endl;
        std::cout << "For more help on individual commands, write: COMMAND help" << std::endl;
        std::cout << "COMMANDS" << std::endl;
        std::cout << TEXT_DIVIDER << std::endl;
        
        for(auto command : getUniqueCommands()) {
            std::cout << command << std::endl;
        }
        
        std::cout << TEXT_DIVIDER << " HELP END " << TEXT_DIVIDER << std::endl;
        return false;
    });
}

bool Player::performCommand(const std::vector<std::string> & input) {
    if(input.empty()) {
        return false;
    }
    
    std::string key = input[0];
    key = toLowerCase(key);

    if(commands.count(key) == 0) {
        std::cout << "Invalid command '" + input[0] + "'. Type 'help' for assistance." << std::endl;
        return false;
    }
    
    auto command = commands[key];
    
    return command(input);
}

bool Player::startInteraction(Character * other) {
    auto res = Character::startInteraction(other);

    if(res) {
        std::cout << std::endl << "You are being attacked by " << other->getName() << "!" << std::endl;
    }
    
    return res;
}

void Player::endInteraction(Character * other) {
    Character::endInteraction(other);
    //TODO: Want this?
    //std::cout << other->getName() + " leaves the fight." << std::endl;
}

void Player::interact(Character * other) {
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
            std::cout << "You " << attackDesc << " " << desc << " for " << std::to_string(actual.health) << " hp! " << actual.description << std::endl;
        }
    };
    
    actions["kick"] = [this, &attack]() {
        unsigned int attackPower = getAttackPower();
        if(isCriticalHit(attackPower)) {
            attack("critical kick", attackPower);
        } else {
            attack("kick", attackPower);
        }
        return true;
    };
    
    actions["hit"] = [self, &other, &attack]() { //TODO remove this or kick
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
    Attack actual = Character::attack(attacker, attack);
    
    decHealth(actual.health);
    
    if(actual.health == 0) {
        auto printAvoid = [&actual](const std::string & desc){
            std::cout << "You " + actual.description + " the attack and thus avoided getting " + desc + "!" << std::endl;
        };
        
        printAvoid(attack.description.empty() ? "hit" : attack.description);
    } else {
        auto printAttack = [&actual](const std::string & desc){
            std::cout << "You got " + desc + " and lost " + std::to_string(actual.health) + " health! " + actual.description << std::endl;
        };
        
        printAttack(attack.description.empty() ? "hit" : attack.description);
    }
    
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

bool Player::isCommandEquipment(std::string command) const {
    command = toLowerCase(command);
    if(command == "eq" || command == "equip" || command == "equipment") {
        return true;
    } else {
        return false;
    }
}

void Player::affectDurability(BreakableItem * bi, unsigned int power) const {
    if(bi != NULL) {
        if(bi->affectDurability(power)) {
            std::cout << bi->getName() << " broke!" << std::endl;
        }
    }
}

std::string Player::getPersonalDescription() const {
    return "This is you (" + getName() + ")";
}

std::string Player::getStatisticalDescription() const {
    std::string desc = Character::getStatisticalDescription();
    desc += "\nArmor rating: " + std::to_string(getArmorRating());
    desc += "\nDodge prob: " + std::to_string(getDodgeProb());
    desc += "\nBlock prob: " + std::to_string(getBlockProb());
    desc += "\nDmg: " + std::to_string(getMinDmg()) + "-" + std::to_string(getMaxDmg());
    desc += "\nCrit prob: " + std::to_string(getCritProb());
    desc += "\nCrit mod: " + std::to_string(getCritMod());
    return desc;
}

std::vector<std::string> & Player::getUniqueCommands() {
    return uniqueCommands;
}