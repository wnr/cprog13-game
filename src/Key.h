#ifndef __cprog13_game__Key__
#define __cprog13_game__Key__

#include <string>

#include "Item.h"
#include <iostream>

namespace game {
    
    class Key : public Item {
        int level;
        std::string identifier;
    public:
        Key(int level, std::string identifier);
        Key(const Key & key);
        Key(Key && key);
        virtual ~Key();
        
        bool operator==(const Key & key) const;
        bool operator>=(const Key & key) const;
        bool operator>(const Key & key) const;
        bool operator<=(const Key & key) const;
        bool operator<(const Key & ket) const;
    
        virtual std::string toString() const;
    private:
        bool differenceOperator(const Key & key, const std::function<bool(int, int)> & operation) const;
    };
}

#endif
