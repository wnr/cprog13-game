#include <iostream>
#include "Engine.h"

#include "OwningStorage.h"

using namespace game;


int main(int argc, const char * argv[])
{
    try
    {
        Engine::getInstance().run();
    }
    catch(std::exception & ex)
    {
        std::cout << std::endl << std::endl << "EXCEPTION: " << ex.what() << std::endl;
        return 1;
    }
    

//    OwningStorage<std::string> vector;
//    
//    vector.push_back(std::unique_ptr<std::string>(new std::string("0")));
//    vector.push_back(std::unique_ptr<std::string>(new std::string("1")));
//    vector.push_back(std::unique_ptr<std::string>(new std::string("2")));
//    vector.push_back(std::unique_ptr<std::string>(new std::string("3")));
//    
//    std::string * last;
//    vector.for_each([&last, &vector] (std::string * str) {
//        std::cout << *str << " ";
//        
//        if(*str == "2") {
//            vector.remove(str);
//        }
//        
//        if(*str == "3") {
//            last = str;
//        }
//        
//        return true;
//    });
//    
//    vector.for_each([&vector, last] (std::string * str) {
//        std::cout << *str << " ";
//        
//        if(*str == "0") {
//            vector.remove(last);
//        }
//        
//        return true;
//    });
//    
    return 0;
}