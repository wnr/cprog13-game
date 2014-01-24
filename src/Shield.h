#ifndef __cprog13_game__Shield__
#define __cprog13_game__Shield__

#include <string>

#include "Armor.h"

namespace game {
    
    class Shield : public Armor {
        unsigned int blockProb;
        
    public:
        Shield();
        Shield(unsigned int blockProb);
        Shield(unsigned int blockProb, unsigned int armorRating);
        Shield(unsigned int blockProb, unsigned int armorRating, unsigned int dodgeRating);
        Shield(unsigned int blockProb, unsigned int armorRating, unsigned int dodgeRating, unsigned int weight);
        Shield(unsigned int blockProb, unsigned int armorRating, unsigned int dodgeRating, unsigned int weight, std::string name);
        Shield(const Shield & shield);
        Shield(Shield && shield);
        virtual ~Shield();
        
        int getBlockProb() const;
        
        virtual Shield* clone() const;
        
    protected:
        virtual std::string getStatisticalDescription() const;
    };
}

#endif
