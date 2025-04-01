//
// Created by Андрей on 28.11.2023.
//

#ifndef TRAMP_C___CAST_H
#define TRAMP_C___CAST_H

#include <iostream>

template<class Der, class Base>
static bool tryCast(std::shared_ptr<Base> base, std::function<void(std::shared_ptr<Der>&&)> f) {
    auto der = std::dynamic_pointer_cast<Der>(base);
    if(der) {
        f(std::move(der));
        return true;
    }
    return false;
}

template<class Der, class Base>
static bool tryCast(std::shared_ptr<Base> base, std::function<void(std::shared_ptr<Der>&)> f) {
    auto der = std::dynamic_pointer_cast<Der>(base);
    if(der) {
        f(der);
        return true;
    }
    return false;
}


template<class Der, class Base>
static bool tryCast(std::shared_ptr<Base> base, std::function<void()> f) {
    auto der = std::dynamic_pointer_cast<Der>(base);
    if(der) {
        f();
        return true;
    }
    return false;
}

#endif //TRAMP_C___CAST_H
