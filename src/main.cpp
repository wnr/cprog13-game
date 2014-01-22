
#include <iostream>
#include <sstream>

#include "Engine.h"

#include "OwningStorage.h"
#include "rand.h"

using namespace game;

bool testRand() {
    auto res = rand(0, 1);
    
    if(res != 0) {
        return false;
    }
    
    res = rand(50, 51);
    
    if(res != 50) {
        return false;
    }
    
    return true;
}

bool testOwningStorage() {
    OwningStorage<std::string> vector;
    
    std::stringstream ss;
    
    auto add = [&vector](std::string n) -> std::string * {
        std::string * s = new std::string(n);
        
        vector.push_back(std::unique_ptr<std::string>(s));
        return s;
    };
    
    auto * p0 = add("0");
    auto * p1 = add("1");
    auto * p2 = add("2");
    auto * p3 = add("3");
    auto * p4 = add("4");
    auto * p5 = add("5");
    auto * p6 = add("6");
    auto * p7 = add("7");
    auto * p8 = add("8");
    auto * p9 = add("9");
    
    //0,1,2,3,4,5,6,7,8,9
    vector.for_each([&ss, &vector, p0, p3, p2, p9] (std::string * str) {
        ss << *str << " ";
        
        //Case 0: Remove itself on beginning.
        if(*str == "0") {
            vector.remove(p0);
        }
        
        //Case 1: Remove itself on non-beginning and non-end.
        if(*str == "2") {
            vector.remove(p2);
        }
        
        //Case 2: Remove itself on end.
        if(*str == "9") {
            vector.remove(p9);
        }
        
        return true;
    });
    
    p9 = add("9");
    
    //1,3,4,5,6,7,8,9
    vector.for_each([&ss, &vector, p1, p4, p7, p9] (std::string * str) {
        ss << *str << " ";
        
        //Case 3: Remove prev begin
        if(*str == "3") {
            vector.remove(p1);
        }
        
        //Case 4: Remove prev non-begin
        if(*str == "5") {
            vector.remove(p4);
        }
        
        //Case 5: Remove next non-end
        if(*str == "6") {
            vector.remove(p7);
        }
        
        //Case 6: Remove next end
        if(*str == "8") {
            vector.remove(p9);
        }
        
        return true;
    });
    
    vector.clear();
    
    p0 = add("0");
    p1 = add("1");
    p2 = add("2");
    p3 = add("3");
    p4 = add("4");
    p5 = add("5");
    p6 = add("6");
    p7 = add("7");
    p8 = add("8");
    p9 = add("9");
    
    //0,1,2,3,4,5,6,7,8,9
    vector.for_each([&ss, &vector, p0, p1, p2, p8, p9] (std::string * str) {
        ss << *str << " ";
        
        //Case 7: Remove elements before current but not prev.
        if(*str == "4") {
            vector.remove(p0);
            vector.remove(p1);
            vector.remove(p2);
        }
    
        //Case 8: Remove elements after current but not next.
        if(*str == "6") {
            vector.remove(p8);
            vector.remove(p9);
        }
    
        return true;
    });
    
    //3,4,5,6,7
    vector.for_each([&ss, &vector, p3, p4, p5, p6, p7] (std::string * str) {
        ss << *str << " ";
        
        //Case 9: Remove all elements before including current but not next.
        if(*str == "4") {
            vector.remove(p3);
            vector.remove(p4);
        }
        
        //Case 10: Remove elements after current including current.
        if(*str == "5") {
            vector.remove(p5);
            vector.remove(p6);
            vector.remove(p7);
        }
        
        return true;
    });
    
    p0 = add("0");
    p1 = add("1");
    p2 = add("2");
    p3 = add("3");
    p4 = add("4");
    
    //0,1,2,3,4
    vector.for_each([&ss, &vector, p3, p4, p5, p6, p7] (std::string * str) {
        ss << *str << " ";
        
        //Case 11: Remove whole vector.
        if(*str == "2") {
            vector.clear();
        }
        
        return true;
    });
    
    vector.clear();
    
    p0 = add("0");
    p1 = add("1");
    p2 = add("2");
    p3 = add("3");
    p4 = add("4");
    p5 = add("5");
    
    //0,1,2,3,4,5
    vector.for_each([&ss, &vector, p1, p4] (std::string * str) {
        ss << *str << " ";
        
        if(*str == "0") {
            vector.remove(p1);
            vector.remove(p4);
        }
        
        return true;
    });
    
    std::string expected = "0 1 2 3 4 5 6 7 8 9 1 3 4 5 6 8 0 1 2 3 4 5 6 7 3 4 5 0 1 2 0 2 3 5 ";
    std::string actual = ss.str();
    if(expected != actual) {
        std::cout << "Failed Owning Storage test!\n\nExpected: \t" + expected + "\nActual: \t" + actual + "\n\n";
        return false;
    }
    
    return true;
}

int main(int argc, const char * argv[])
{
    if(!testOwningStorage()) {
        std::cout << "\n\nFailed Owning Storage test\n\n";
        return 1;
    }
    
    if(!testRand()) {
        std::cout << "\n\nFailed rand test\n\n";
        return 1;
    }

    
    try
    {
        Engine::getInstance()->run();
    }
    catch(std::exception & ex)
    {
        std::cout << std::endl << std::endl << "EXCEPTION: " << ex.what() << std::endl;
        return 1;
    }
    
    return 0;
}