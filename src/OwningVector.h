#ifndef __cprog13_game__OwningVector__
#define __cprog13_game__OwningVector__

//A vector that stores data in unique_ptr's with custom functions to access/manipulate data.
//The OwningVector owns the memory of whats stored and the only way of moving the owning of the data
//is to remove it from the vector.
//Also, only unique values can be stored in the vector.

#include <functional>
#include <stdexcept>
#include <vector>

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
        
        //Will keep iterating through vector and performing operation on every element until operation function returns false.
        void for_each(const std::function<bool(T * element)> & operation) {
            for(auto & e : data) {
                if(operation(e.get()) == false) {
                    break;
                }
            }
        }
        
        void for_each(const std::function<bool(const T * element)> & operation) const {
            for(const auto & e : data) {
                if(operation(e.get()) == false) {
                    break;
                }
            }
        }
        
        size_t size() const {
            return data.size();
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
    };
}

#endif
