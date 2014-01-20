#ifndef __cprog13_game__BreakableItem__
#define __cprog13_game__BreakableItem__

#include <string>
#include "Item.h"

namespace game {
    
    class BreakableItem : public Item {
        int durability;
        int maxDurability;

    public:
        BreakableItem(std::string type, unsigned int volume);
        BreakableItem(std::string type, bool visible, unsigned int volume);
        BreakableItem(const BreakableItem & bi);
        BreakableItem(BreakableItem && bi);
        virtual ~BreakableItem();

        
        bool breakItem();
        bool decDurability(int amount);
        bool incDurability(int amount);
        
        bool isWorking() const;
        int getDurability() const;
        int getMaxDurability() const;
    private:
        void changeDurability(int amount);
    };
}

#endif