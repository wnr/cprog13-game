#ifndef __cprog13_game__Container__
#define __cprog13_game__Container__

#include <string>
#include <vector>

#include "Item.h"

namespace game {
    
    class Engine;
    
    class Container : public Object {
    protected:
        std::vector<std::unique_ptr<Item>> * inventory;
        const int maxSize;
    public:
        Container(std::string type, int maxSize);
        Container(std::string type, int maxSize, bool visible, bool carriable);
        Container(const Container & con);
        Container(Container && con);
        ~Container();
        
        int getMaxSize() const;
        int getRemainingSpace() const;
        virtual bool addItem(std::unique_ptr<Item> & item);
        virtual std::unique_ptr<Item> removeItem(const Item * item);
        virtual const std::vector<std::unique_ptr<Item>> * getInventory() const;
    
        virtual std::string toString() const;
        virtual std::string getDescription() const;
    };
}

#endif
