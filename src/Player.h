#ifndef __cprog13_game__Player__
#define __cprog13_game__Player__

#include "Character.h"

#include <map>
#include <vector>

namespace game {
    class Player : public Character {
        std::map<std::string, std::function<bool(const std::vector<std::string> &)>> commands;
        std::vector<std::string> uniqueCommands;
        
    public:
        Player(Environment * env, unsigned int maxHealth, std::string name);
        Player(Environment * env, std::string subType, unsigned int maxHealth, std::string name, unsigned int baseArmorRating, unsigned int baseDodgeProb, unsigned int baseBlockProb, unsigned int baseMinDmg, unsigned int baseMaxDmg, unsigned int baseCritProb, unsigned int baseCritMod);
        Player(const Player & player);
        Player(Player && player);
        ~Player();
        
        void update(Environment & env);
        
        bool startInteraction(Character * other);
        void endInteraction(Character * other);
        void interact(Character * other);
        
        Attack attack(Character * attacker, const Attack & attack);
        Attack performAttack(Character * defender, std::string attackType);
        virtual Attack afterDefence(Character * defender, const Attack & effect);
        virtual Attack afterOffence(Character * attacker, const Attack & effect);
        
        void kill();
        
        void affectDurability(BreakableItem * bi, unsigned int power) const;
        
        virtual Player* clone() const;
        
        
    private:
        void update();
        void initCommands();
        
        void printUpdateInfo() const;
        bool performCommand(const std::vector<std::string> & inputs);
        bool isCommandInventory(std::string command ) const;
        bool isCommandEquipment(std::string command ) const;
        std::vector<std::string> & getUniqueCommands();
        
        std::string getPersonalDescription() const;
        std::string getStatisticalDescription() const;
    };
}

#endif
