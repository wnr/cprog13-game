#ifndef __cprog13_game__Equipment__
#define __cprog13_game__Equipment__

#include <string>
#include "GameStorage.h"
#include "BreakableItem.h"

namespace game {
    class Armor;
    class Equipment : public GameStorage<BreakableItem> {
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
        
        unsigned int getAttackPower() const;
        unsigned int getDodgeProb() const;
        unsigned int getBlockProb() const;
        unsigned int getArmorRating() const;
        
    private:
        void for_each_armor(const std::function<bool (Armor*)>) const;
    };
}

#endif
