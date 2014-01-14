#ifndef __cprog13_game__Key__
#define __cprog13_game__Key__

#include <string>

#include "Item.h"
#include <iostream>

namespace game {
    
    class Key : public Item {
    protected:
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
        bool differenceOperator(const Key &, const std::function<int(int, int)> &) const;
    };
}

#endif
