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
#include <set>

namespace game {
    
    template<class T>
    class GameStorage : public OwningStorage<T> {
        
    public:
        GameStorage() {}
        virtual ~GameStorage() {}
        
        virtual T * find(const std::string & mainType, const std::string & subType, std::string searchString, const std::vector<const T*> & skips = {}, bool caseinsens = true) const {
            
            T * result = NULL;
            
            if(caseinsens) {
                searchString = toLowerCase(searchString);
            }
            
            for_each_count([caseinsens, &result, searchString, mainType, subType, this](T * element, int val) {
                if(mainType != "" && element->getMainType() != mainType) {
                    return true; //Continue searching
                }
                if(subType != "" && element->getSubType() != subType) {
                    return true; //Continue searching
                }
                std::string matchString = getModName(element, val);
                if(caseinsens) {
                    matchString = toLowerCase(matchString);
                }
                
                if(searchString == "" || matchString == searchString) {
                    result = element;
                    return false;
                } else {
                    return true; //Continue searching
                }
            }, skips);
            
            return result;
        }
        
        T * find(const std::string & mainType, std::string searchString, const std::vector<const T*> & skips = {}, bool caseinsens = true) const {
            return find(mainType, "", searchString, skips, caseinsens);
        }
        
        T * find(std::string searchString, const std::vector<const T*> & skips = {}, bool caseinsens = true) const {
            return find("", searchString, skips, caseinsens);
        }
        
        template<class E>
        E * find(const std::string mainType, std::string searchString, const std::vector<const T*> & skips = {}, bool caseinsens = true) const {
            return (E*) find<E>(mainType, "", searchString, skips, caseinsens);
        }
        
        template<class E>
        E * find(const std::string & mainType, const std::string & subType, std::string searchString, const std::vector<const T*> & skips = {}, bool caseinsens = true) const {
            return (E*) find(mainType, subType, searchString, skips, caseinsens);
        }
        
        template<class E>
        E* random(const std::string & mainType = "", const std::vector<const T*> & skips = {}, std::function<bool (E*)> operation = [](){return true;}) const {
            std::vector<E*> candidates;
            
            this->for_each([&candidates, &mainType, operation](T * element){
                if(mainType == "" || element->getMainType() == mainType) {
                    if(operation((E*)element)) {
                        candidates.push_back((E*)element);
                    }
                }
                
                return true;
            }, skips);
            
            if(candidates.empty()) {
                return NULL;
            }
            
            auto picked = rand((unsigned int)candidates.size());
            
            return candidates[picked];
        }
        
        virtual std::string getStorageListAsString(const std::vector<const T*> skips = {}, const std::string & itemPrefix = LIST_ITEM_PREFIX) const {
            std::string * result = new std::string("");
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
        
        void for_each_count(const std::function<bool(T *, int)> operation, const std::vector<const T*> & skips = {}) const {
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
            }, skips);
        }
    };
}

#endif
