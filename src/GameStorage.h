#ifndef __cprog13_game__GameStorage__
#define __cprog13_game__GameStorage__

//A class that extends the generic class OwningStorage to have more game-specific storage related methods.
#include "OwningStorage.h"
#include "BaseObject.h"
#include "Constants.h"
#include <map>

namespace game {
    
    template<class T>
    class GameStorage : public OwningStorage<T> {
        
    public:
        GameStorage() {}
        virtual ~GameStorage() {}
        
        virtual T * find(const std::string & mainType, std::string searchString, bool caseinsens = true) const {
            T * result = NULL;
            
            
            if(caseinsens) {
                std::transform(searchString.begin(), searchString.end(), searchString.begin(), ::tolower);
            }
            
            for_each_count([caseinsens, &result, searchString, mainType, this](T * element, int val) {
                if(element->getMainType() != mainType) {
                    return true; //Continue searching
                }
                std::string matchString = getModName(element, val);
                if(caseinsens) {
                    std::transform(matchString.begin(), matchString.end(), matchString.begin(), ::tolower);
                }
                
                if(matchString == searchString) {
                    result = element;
                    return false;
                } else {
                    return true; //Continue searching
                }
            });
            return result;
        }
        
        template<class E>
        E * find(const std::string & mainType, std::string searchString, bool caseinsens = true) const {
            return (E*) find(mainType, searchString, caseinsens);
        }
        
        virtual std::string storageListToString() const {
            return storageListToString(LIST_ITEM_PREFIX);
        }
        
        virtual std::string storageListToString(const std::string & prefix) const {
            std::string * result = new std::string("");
            for_each_count([prefix, result, this](T * element, int val){
                result->append(prefix);
                result->append(getModName(element, val));
                result->append("\n");
                return true;
            });
            return *result;
        }
        
    private:
        std::string getModName(T * element, int val) const {
            if(val == 0) {
                return element->getName();
            } else {
                return element->getName() + "(" + std::to_string(val) + ")";
            }

        }
        
        void for_each_count(const std::function<bool(T *, int)> operation) const {
            std::map<std::string, int> map;
            this->for_each([&operation, &map](T * element){
                std::string objectName = element->getName();
                std::map<std::string, int>::iterator mapIt = map.find(objectName);
                int elementNameFoundAmount = 0;
                if(mapIt != map.end()){
                    elementNameFoundAmount = mapIt->second;
                }
                map[objectName] = elementNameFoundAmount + 1;
                return operation(element, elementNameFoundAmount);
            });
        }
    };
}

#endif
