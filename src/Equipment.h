#ifndef __cprog13_game__Equipment__
#define __cprog13_game__Equipment__

#include <string>
#include "GameStorage.h"
#include "BreakableItem.h"

namespace game {
    class Armor;
    class Equipment : public PhysicalObject, public GameStorage<BreakableItem> {
    public:
        Equipment();
        
        ~Equipment();
        virtual std::unique_ptr<BreakableItem> push_back(std::unique_ptr<BreakableItem> element);
        
        BreakableItem * findItemWithSubType(const std::string subType) const;
        
        template<class E>
        E * findItemWithSubType(const std::string subType) const {
            E * item = find<E>("", subType, "");
            return item;
        }
        
        unsigned int getMinDmg() const;
        unsigned int getMaxDmg() const;
        float getDodgeProb() const;
        float getBlockProb() const;
        float getCritProb() const;
        unsigned int getCritMod() const;
        unsigned int getArmorRating() const;
        
        bool affectDurability(const std::string & subType, unsigned int power) const;
        bool affectArmorDurability(unsigned int power) const;
        
        void for_each_armor(const std::function<bool (Armor*)>) const;
        
        std::string getDescription() const;
        
        virtual Equipment * clone() const;

    private:
        std::string getPersonalDescription() const;
        std::string getStatisticalDescription() const;
    };
}

#endif
