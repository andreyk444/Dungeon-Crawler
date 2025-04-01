//
// Created by Андрей on 13.11.2023.
//

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>

class IGameObject{

public:

    virtual ~IGameObject() = default;

    virtual std::string getName() const = 0;
};


#endif //GAMEOBJECT_H
