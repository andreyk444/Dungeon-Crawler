

#ifndef getSmth_hpp
#define getSmth_hpp

#include <cstdio>
#include <iostream>
#include <limits>

template<class T>
T getNum(T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) {
    T a;
    while(true) {
        std::cin >> a;
        if(std::cin.eof())
            throw std::runtime_error("Failed to read number: EOF");
        else if(std::cin.bad())
            throw std::runtime_error(std::string("Failed to read number: ") );

        else if(std::cin.fail() || a < min || a > max) {
            std::cin.clear();

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "You are wrong; repeat please!" << std::endl;
        }
        else
            return a;
    }
}

#endif /* getSmth_hpp */
