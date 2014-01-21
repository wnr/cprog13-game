#ifndef __cprog13_game__OwningStorage__
#define __cprog13_game__OwningStorage__

//A list that stores data in unique_ptr's with custom functions to access/manipulate data.
//The OwningStorage owns the memory of whats stored and the only way of moving the owning of the data
//is to remove it from the storage.
//Also, only unique values can be stored in the storage.

#include <functional>
#include <stdexcept>
#include <list>

namespace game {
    
    template<class T>
    class OwningStorage {
        std::list<std::unique_ptr<T>> data;
        
    public:
        OwningStorage() {}
        virtual ~OwningStorage() {}
        
        bool exist(const T * element) const {
            return index(element) != -1;
        }
        
        virtual std::unique_ptr<T> push_back(std::unique_ptr<T> element) {
            if(exist(element.get())) {
                //This means there are two unique_ptr to the same object. Releaase this ptr and throw exception.
                element.release();
                throw std::invalid_argument("Element already exists in storage.");
            }
            
            data.push_back(std::move(element));
            return nullptr;
        }

        virtual std::unique_ptr<T> remove(const T * element) {
            std::unique_ptr<T> ptr = nullptr;
            
            for(auto it = data.begin(); it != data.end(); it++) {
                if((*it).get() == element) {
                    ptr = std::move(*(it));
                    data.erase(it);
                    break;
                }
            }
            
            return ptr;
        }
        
        template<class E>
        std::unique_ptr<E> remove(const T * element) {
            std::unique_ptr<E> result((E*)((remove(element).release())));
            return result;
        }
        
        //Will keep iterating through storage and performing operation on every element until operation function returns false.
        virtual void for_each(const std::function<bool(T * element)> & operation, const std::vector<T*> skips = {}) const {
            std::list<T *> processed;
            
            //Finds the last element of the processed list in the data list, and returns an iterator to the next element.
            auto catchup = [&processed, this]() {
                auto found = data.end();
                
                for(auto it = processed.rbegin(); it != processed.rend(); it++) {
                    auto e = std::find_if(data.begin(), data.end(), [&it](const std::unique_ptr<T> & ptr){
                        return ptr.get() == (*it);
                    });
                    
                    if(e != data.end()) {
                        found = e;
                        break;
                    }
                }
                
                if(found != data.end()) {
                    return std::next(found, 1);
                } else {
                    //Couldn't find any of the processed elements. Start from the start then.
                    return data.begin();
                }
                
            };
            
            for(auto it = data.begin(); it != data.end();) {
                auto prev = std::prev(it, 1);
                auto next = std::next(it, 1);
                
                T * element = (*it).get();
                
                //Store the element in the processed list. Doesn't matter if skipped or not.
                processed.push_back(element);
                
                if(std::find(skips.begin(), skips.end(), element) == skips.end()) {
                    //Element not found in skips list. So process element.
                    
                    if(operation(element) == false) {
                        break;
                    }
                }
                
                //Sanity check for the iterator.
                if(std::next(it, 1) == next && std::prev(it, 1) == prev) {
                    //The iterator is valid. Keep iterating as normal.
                    it++;
                } else {
                    //Remove has occured which invalidated some or all of the iterators.
                    //Perform a catch-up.
                    it = catchup();
                }
            }
        }
        
        size_t size() const {
            return data.size();
        }
        
        void clear() {
            data.clear();
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
