#include <Element/element.h>

#include <utility>


namespace Tramp {

    WeakElement::WeakElement(std::shared_ptr<InatureElement> element, double multipleer): multipleer_{multipleer},
        element_{std::move(element)}{}


    double WeakElement::getMultipleer() const {return multipleer_;}

    std::shared_ptr<InatureElement> WeakElement::getElement() const {
        return element_;
    }

    Water::Water(std::string name):name_{std::move(name)} {}
    std::string Water::getName() const  {return  name_;}

    Fire::Fire(std::string name):name_{std::move(name)}  {}
    std::string Fire::getName() const {return name_;}

    Holy::Holy(std::string name):name_{std::move(name)}  {}
    std::string Holy::getName() const{return name_;}

    Devil::Devil(std::string name):name_{std::move(name)}  {}
    std::string Devil::getName() const{return name_;}


}