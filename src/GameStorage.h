#ifndef __cprog13_game__GameStorage__
#define __cprog13_game__GameStorage__

//A class that extends the generic class OwningStorage to have more game-specific storage related methods.
#include "OwningStorage.h"
#include "utils.h"
#include "BaseObject.h"
#include "Constants.h"
#include "rand.h"
#include <map>
#include <vector>

namespace game {
    
    template<class T>
    class GameStorage : public OwningStorage<T> {
        
    public:
        GameStorage() {}
        virtual ~GameStorage() {}
        
        virtual T * find(const std::string & mainType, std::string searchString, bool caseinsens = true) const {
            T * result = NULL;
            
            
            if(caseinsens) {
                searchString = toLowerCase(searchString);
            }
            
            for_each_count([caseinsens, &result, searchString, mainType, this](T * element, int val) {
                if(mainType != "" && element->getMainType() != mainType) {
                    return true; //Continue searching
                }
                std::string matchString = getModName(element, val);
                if(caseinsens) {
                    matchString = toLowerCase(matchString);
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
        E * random(const std::string & mainType, const std::vector<T*> skips = {}) const {
            std::vector<T*> candidates;
            
            this->for_each([&candidates, &mainType](T * element){
                if(element->getMainType() == mainType) {
                    candidates.push_back(element);
                }
                
                return true;
            }, skips);
            
            if(candidates.empty()) {
                return NULL;
            }
            
            auto picked = rand((unsigned int)candidates.size(), false);
            
            return (E*)candidates[picked];
        }
        
        template<class E>
        E * find(const std::string & mainType, std::string searchString, bool caseinsens = true) const {
            return (E*) find(mainType, searchString, caseinsens);
        }
        
        T * find(std::string searchString, bool caseinsens = true) const {
            return find("", searchString, caseinsens);
        }

        virtual std::string storageListToString(const T * skip) const {
            std::vector<const T*> skips({skip});
            return storageListToString(skips);
        }
        
        virtual std::string storageListToString(const std::string listPrefix, const T * skip) const {
            std::vector<const T*> skips({skip});
            return storageListToString(listPrefix, skips);
        }
        
        virtual std::string storageListToString(const std::vector<const T*> skips = {}) const {
            return storageListToString(TEXT_DIVIDER, skips);
        }
        
        virtual std::string storageListToString(const std::string listPrefix, const std::vector<const T*> skips = {}) const {
            return storageListToString(listPrefix, LIST_ITEM_PREFIX, skips);
        }
        
        virtual std::string storageListToString(const std::string & listPrefix, const std::string & itemPrefix, const std::vector<const T*> skips = {}) const {
            std::string * result;
            if(listPrefix == "") {
                result = new std::string("");
            } else {
                result = new std::string(listPrefix + "\n");
            }
            for_each_count([itemPrefix, result, this, &skips](T * element, int val){
                if(std::find(skips.begin(), skips.end(), element) != skips.end()) {
                    //Found in skips list. So skip element.
                    return true;;
                }
                
                result->append(itemPrefix);
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
