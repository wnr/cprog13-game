#ifndef __cprog13_game__Equipment__
#define __cprog13_game__Equipment__

#include <string>
#include "GameStorage.h"
#include "BreakableItem.h"

namespace game {
    
    class Equipment : public GameStorage<BreakableItem> {
    public:
        Equipment();
        ~Equipment();
        virtual std::unique_ptr<BreakableItem> push_back(std::unique_ptr<BreakableItem> element);
        
        BreakableItem * findItemWithSubType(const std::string subType) const;
    };
}

#endif
