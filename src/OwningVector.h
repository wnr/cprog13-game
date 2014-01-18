#ifndef __cprog13_game__OwningVector__
#define __cprog13_game__OwningVector__

//A vector that stores data in unique_ptr's with custom functions to access/manipulate data.
//The OwningVector owns the memory of whats stored and the only way of moving the owning of the data
//is to remove it from the vector.
//Also, only unique values can be stored in the vector.

#include <functional>
#include <stdexcept>
#include <vector>
#include <map>

namespace game {
    
    template<class T>
    class OwningVector {
        
        std::vector<std::unique_ptr<T>> data;
        
    public:
        OwningVector() {}
        virtual ~OwningVector() {}
        
        bool exist(const T * element) const {
            return index(element) != -1;
        }
        
        void push_back(std::unique_ptr<T> element) {
            if(exist(element.get())) {
                throw std::invalid_argument("Element already exists in vector.");
            }
            
            data.push_back(std::move(element));
        }

        std::unique_ptr<T> remove(const T * element) {
            unsigned int index = this->index(element);
            
            if(index == -1) {
                return nullptr;
            }
            
            auto ptr = std::move(data[index]);
            
            data.erase(data.begin() + index);
            
            return ptr;
        }
        
        template<class E>
        std::unique_ptr<E> remove(const T * element) {
            std::unique_ptr<E> result(static_cast<E*>(remove(element).release()));
            return result;
        }
        
        template<class E>
        E * find(const std::string mainType, std::string searchString) const {
            E * result;
            E ** resultHolder = &result;
            
            mapFunction([resultHolder, searchString, mainType](T * e, int val) {
                std::string matchString;
                if(e->getMainType() != mainType) {
                    return true; //Continue searching
                }
                if(val == 0) {
                    matchString = e->getDescription();
                } else {
                    matchString = e->getDescription() + " (" + std::to_string(val);
                }
                
                if(matchString == searchString) {
                    (*resultHolder) = (E*)e;
                    return false;
                } else {
                    return true; //Continue searching
                }
            });
            return result;
        }
        
        //Will keep iterating through vector and performing operation on every element until operation function returns false.
        virtual void for_each(const std::function<bool(T * element)> & operation) {
            for(auto & e : data) {
                if(operation(e.get()) == false) {
                    break;
                }
            }
        }
        
        virtual void for_each(const std::function<bool(const T * element)> & operation) const {
            for(const auto & e : data) {
                if(operation(e.get()) == false) {
                    break;
                }
            }
        }
        
        size_t size() const {
            return data.size();
        }
        
        std::string listToString() const {
            std::string * result;
            mapFunction([result](T * b, int val){
                if(val == 0) {
                    result->append(b->toString() + "/n");
                } else {
                    result->append(b->toString() + " (" + std::to_string(val) + ")/n");
                }
                return true;
            });
        }
        
    private:
        //Returns the index of the element in the array. Returns -1 if not found.
        unsigned int index(const T * element) const {
            unsigned int index = 0;
            
            for_each([&index, element] (const T * e) {
                if(e == element) {
                    return false; //stop the for_each loop.
                }
                
                index++;
                
                return true; //continue searching.
            });
            
            if(index == data.size()) {
                return -1;
            }
            
            return index;
        }
        
        void mapFunction(const std::function<bool(T *, int)> operation) const {
            std::string result;
            std::map<std::string, int> map;
            std::map<std::string, int>::iterator it;
            for(auto & a : data) {
                auto * e = a.get();
                std::string objectName = e->getDescription();
                it = map.find(objectName);
                if(it == map.end()){
                    if (!operation(e, 0)) {
                        break;
                    }
                    map[objectName] = 1;
                    result.append(objectName);
                } else {
                    if (!operation(e, it->second)) {
                        break;
                    }
                    result.append(objectName + " (" + std::to_string(it->second) + ")");
                    map[objectName] = it->second + 1;
                }
            }

        }
    };
}

#endif
