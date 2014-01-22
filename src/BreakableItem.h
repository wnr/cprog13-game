#ifndef __cprog13_game__BreakableItem__
#define __cprog13_game__BreakableItem__

#include <string>
#include "Item.h"

namespace game {
    
    class BreakableItem : public Item {
        int durability;
        unsigned int maxDurability;

    public:
        BreakableItem(std::string subType, unsigned int weight);
        BreakableItem(std::string subType, unsigned int weight, std::string name);
        BreakableItem(std::string subType, unsigned int weight, std::string name, unsigned int durability);
        BreakableItem(const BreakableItem & bi);
        BreakableItem(BreakableItem && bi);
        virtual ~BreakableItem();
        
        bool breakItem();
        bool decDurability(int amount);
        bool incDurability(int amount);
        
        bool isWorking() const;
        int getDurability() const;
        int getMaxDurability() const;
        
        bool isArmor() const;
        bool isWeapon() const;
    protected:
        std::string getStatisticalDescription() const;
    private:
        void changeDurability(int amount);
    };
}

#endif