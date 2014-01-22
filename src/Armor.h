#ifndef __cprog13_game__Armor__
#define __cprog13_game__Armor__

#include <string>

#include "BreakableItem.h"

namespace game {
    
    class Armor : public BreakableItem {
        unsigned int armorRating;
        unsigned int dodgeRating;
        
    public:
        Armor(std::string subType);
        Armor(std::string subType, unsigned int armorRating);
        Armor(std::string subType, unsigned int armorRating, unsigned int dodgeRating);
        Armor(std::string subType, unsigned int armorRating, unsigned int dodgeRating, unsigned int weight);
        Armor(std::string subType, unsigned int armorRating, unsigned int dodgeRating, unsigned int weight, std::string name);
        Armor(const Armor & armor);
        Armor(Armor && armor);
        virtual ~Armor();
        
        unsigned int getArmorRating() const;
        
        unsigned int getDodgeRating() const;
        
    protected:
        virtual std::string getStatisticalDescription() const;
    
    private:
        bool isSubTypeAllowed(const std::string & subType) const;
    };
}

#endif
