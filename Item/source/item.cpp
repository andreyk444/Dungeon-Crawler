#include "Item/Item.h"

#include <Element/element.h>
#include <Entity/entity.h>

#include <utility>


namespace Tramp {

    static auto potionToken = ItemManager::registerModule("potion",
                  std::function([]()->std::shared_ptr<IItem>{return std::shared_ptr<Potion>();}));



    Potion::Potion(CharacteristicType characteristicType, size_t changeSize):
        characteristicType_{characteristicType}, changeSize_{changeSize} {}

    size_t Potion::getChangeSize() const{ return changeSize_;}
    CharacteristicType Potion::getCharacteristicType() const {return characteristicType_;}

    void Potion::use( std::shared_ptr<IGameObject> gameObject) const{
        tryCast<Character>(gameObject, [this](std::shared_ptr<Character> &ptr){
            ptr->up_Characteristic(characteristicType_, changeSize_);
        });
    }



    BunchOfKeys::BunchOfKeys(size_t count): count_{count} {}
    size_t BunchOfKeys::getCount() const {return count_;}

    void BunchOfKeys::use(std::shared_ptr<IGameObject> gameObject) const {
        tryCast<Character>(gameObject, [this](std::shared_ptr<Character> &ptr){
            ptr->pickKeys(count_);
        });
    }

    RegularEquipment::RegularEquipment(EquipmentType equipmentType, size_t defence,std::pair<size_t, size_t>& coo):
        equipmentType_{equipmentType}, defence_{defence}, coordinates_(coo), isVisible_(true) {}


    size_t RegularEquipment::generateDefence() {
        return defence_;
    }

    size_t RegularEquipment::getDifance() const {return defence_;}
    EquipmentType RegularEquipment::getEquipmentType() const {return equipmentType_;}


    RegularWeapon::RegularWeapon(std::string name, size_t damage, size_t maxDamage):
        name_(std::move(name)), damage_(damage), maxDamage_(maxDamage) {}

    size_t RegularWeapon::generateDamage(std::shared_ptr<Enemy>) {
        return damage_;
    }

    size_t RegularWeapon::getMaxDamage() const {return maxDamage_;}
    size_t RegularWeapon::getDamage() const {return damage_;}
    std::string RegularWeapon::getName() const {return name_;}


    ArtifactEquipment::ArtifactEquipment(Tramp::EquipmentType equipmentType, size_t defenceBonus, size_t defence, std::pair<size_t, size_t> coo):
            RegularEquipment(equipmentType, defence, coo), defenceBonus_{defenceBonus} {}



    size_t ArtifactEquipment::generateDefence() {return  getDifance() + defenceBonus_;}
    size_t ArtifactEquipment::getDifanceBonus() const {return defenceBonus_;}


    EnchartedWeapon::EnchartedWeapon(std::string name, size_t damage,size_t maxDamage, const std::shared_ptr<InatureElement>& element):
            RegularWeapon(std::move(name), damage, maxDamage){
        element_ = element;
    }


    std::shared_ptr<InatureElement>  EnchartedWeapon::getElement() const {return element_;}

    size_t EnchartedWeapon::generateDamage(std::shared_ptr<Enemy> enemy) {//когда вызываем от героя generateDamage вызывыть эту функциию и передавать в нее элемент
        size_t global_damage = getDamage();

        if (enemy) {
            if (enemy->getElement()) {
                if (enemy->getElement()->getElement() == element_)
                    global_damage *= static_cast<int>(enemy->getElement()->getMultipleer());
            }
        }

        return global_damage;
    }


    ArtifactWeapon::ArtifactWeapon(std::string name, size_t damage,  size_t maxDamage, size_t damageBonus):
            RegularWeapon(std::move(name), damage, maxDamage), damageBonus_{damageBonus} {}

    size_t ArtifactWeapon::getDamageBonus() const {return damageBonus_;}
    size_t ArtifactWeapon::generateDamage(std::shared_ptr<Enemy>) {
        size_t globalDamage = (damageBonus_ + getDamage());
        size_t max = getMaxDamage();

        return   globalDamage < max ? globalDamage : max;
    }


    ArtifactAndEnchartedWeapon::ArtifactAndEnchartedWeapon(std::string name, size_t damage, size_t maxDamage, size_t damageBonus,
                                                           std::shared_ptr<Tramp::InatureElement> element):
            RegularWeapon(std::move(name), damage, maxDamage), damageBonus_{damageBonus}, element_{std::move(element)}{}


    size_t ArtifactAndEnchartedWeapon::getDamageBonus() const {return damageBonus_;}
    std::shared_ptr<InatureElement> ArtifactAndEnchartedWeapon::getElement() const {return element_;}
    size_t ArtifactAndEnchartedWeapon::generateDamage(std::shared_ptr<Enemy> enemy) {
        size_t global_damage = getDamage() + damageBonus_;

        if (enemy) {
            if (enemy->getElement()->getElement() == element_)
                global_damage *= static_cast<int>(enemy->getElement()->getMultipleer());
        }

        size_t max = getMaxDamage();
        return global_damage < max ? global_damage : max;

    }




    Chest::Chest(std::string name, size_t level, const std::shared_ptr<Tramp::IItem>& item):
        name_{std::move(name)}, level_{level},  isOpen_{false} {
        item_ = item;
    }


    size_t Chest::getLevel() const {return level_;}

    std::shared_ptr<IItem> Chest::getItem() const {return item_;}

    bool Chest::isOpen() const {return isOpen_;}

    void Chest::open(){
        isOpen_ = true;
    }

}



