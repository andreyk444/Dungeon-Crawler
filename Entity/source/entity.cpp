#include "Entity/entity.h"

#include <Item/Item.h>
#include <Dungeon/Dungeon.h>

#include <random>
#include <utility>

#include <Utils/Cast.h>
#include <Element/element.h>


namespace Tramp{


    void Character::equip(const std::shared_ptr<Tramp::IEquipable>& equipable){


        if (tryCast<IEquipment>(equipable, [this](std::shared_ptr<IEquipment>& ptr)
                                  {ptr->setCoordinates(getCoordinates());
                                    equipment_[static_cast<size_t>(ptr->getEquipmentType() )] = ptr;})
                                  ||
        tryCast<IWeapon>(equipable , [this](std::shared_ptr<IWeapon>&& ptr)
                                    {   ptr->getCoordinates() = getCoordinates();
                                        weapon_= std::move(ptr);})
                                    )
        {
            //убрать из поля
            return;
        }


    }
    void Character::unEquip(std::shared_ptr<Tramp::IEquipable> equipable) {

        tryCast<IEquipment>(equipable, [this](std::shared_ptr<IEquipment> &&ptr)
            { equipment_[ptr->getEquipmentType()] = nullptr;})
        ||
        tryCast<IWeapon>(equipable , [this]()
            {weapon_= nullptr;});


    }
    void Character::pickUp(const std::shared_ptr<Tramp::IItem>& item) {
        if (items_.size() < max_items_){
            items_.push_back(item);
        }
    }

    void Character::throwAway(const std::shared_ptr<Tramp::IItem>& item) {
        if (!items_.empty() ){
            auto findElement = std::find(items_.begin(), items_.end(), item);

            if (findElement != items_.end()){
                items_.erase(findElement);
            }
        }
    }


    void Character::tryHackChest(Chest& chest) {
      //
      //  std::srand((std::time(0)));

        double probabality = 1.0 - 0.1 * chest.getLevel();
        probabality = probabality < 0 ? 0 : probabality;

        double random = getHackingProbability( );

        if (random < probabality){
            chest.open();
        }
    }

    void Character::upLevel(CharacteristicType characteristicType) {
        if (experience_ >= 100) {
            experience_ -= 100;
            up_Characteristic(characteristicType, UP_LEVEL_CHARACTISTIC);
        }
    }

    void Character::up_Characteristic(Tramp::CharacteristicType characteristicType, size_t upCharacteristics) {
        tableCharacteristics_[characteristicType] += upCharacteristics;
    }

    void Character::getHit(size_t damage)   {
        int lessDamage = damage;
        if (getDefence()){
            lessDamage -= getDefence();
        }


        if (lessDamage <= 0) return;

        if (static_cast<int>(tableCharacteristics_[CURRENT_HEALTH] - lessDamage) <= 0){
            isLive_ = false;
            return;
        }

        tableCharacteristics_[CURRENT_HEALTH] -= lessDamage;



    }

    size_t Character::getExperience() const{return experience_;}
    size_t Character::getHealth() const {return getCharacteristic(CURRENT_HEALTH);}
    size_t Character::getMaxHealth() const {return getCharacteristic(MAX_HEALTH);}

    size_t Character::getDamage(std::shared_ptr<Enemy> enemy) const {
        if (weapon_)
            return weapon_->generateDamage(std::move(enemy));
        else{
            return DAMAGE_BY_HANDS;
        }
    }

    size_t Character::getDefence() const {
        size_t globalDefence = 0;

        for (const auto& val: equipment_){
            if (val)
                globalDefence += val->generateDefence();
        }
        return globalDefence;
    }

    std::shared_ptr<IWeapon> Character::getWeapon() const {return weapon_;}
    size_t Character::getCharacteristic(Tramp::CharacteristicType characteristicType) const {return tableCharacteristics_[characteristicType];}
    std::vector<std::shared_ptr<IItem> > Character::getItems() const {return items_;}
    size_t Character::getMaxItems() const {return max_items_;}
    size_t Character::getCountKeys() const {return countKeys_;}
    std::shared_ptr<IEquipment> Character::getEquipment(Tramp::EquipmentType equipmentType) const {return equipment_[equipmentType];}

    double Character::getHackingProbability() {
        long  generation = (std::random_device{}() % 1000+ 1);

        generation -= static_cast<long int>(tableCharacteristics_[DEXTERITY] * DEXTERITY_MULTIPLEER);
        generation = generation < 0 ? 0 : generation;
        return  static_cast<double>(generation) / 100;
    }

    size_t Character::getHitProbability() const {
        return getCharacteristic(DEXTERITY);
    }

    //void Character::move(WAY_DIRECTION wayDirection, ) {//тo do либо потзиция ечтьб у игрока либо как то по другому
        //но скорее всего не у игрока а мы меняем позицию игрового обьекта существа на площадке

    //}

    Character::Character(std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> tableCharacteristics, size_t max_items):
        tableCharacteristics_(tableCharacteristics), experience_(0), weapon_(nullptr), max_items_(MAX_ITEMS), countKeys_(0), coordinates_({1, 1}){}


    void Character::pickKeys(size_t count) {
        countKeys_ += count;
    }

    bool Character::move(WAY_DIRECTION dirrection, Dungeon &dungeon) {
        CellType nowType = dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second][coordinates_.first].getCellType();
        CellType type = dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second+ movements[dirrection].second][coordinates_.first + movements[dirrection].first].getCellType();
        if ( type == ENTITY)
            return false;
        else if(type == WALL) {
            return true;
        }

        if (nowType != STAIRS_DOWN && nowType != STAIRS_UP) {
            dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second][coordinates_.first].changeCell(
                    GAME_OBJECT);
        }

        coordinates_.first += movements[dirrection].first;
        coordinates_.second += movements[dirrection].second;

        for (auto &it: equipment_){
            if (it)
                it->updateCoordinates(coordinates_);
        }

        if (type != STAIRS_DOWN && type != STAIRS_UP) {
            //dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second][coordinates_.first].changeCell(GAME_OBJECT);
            dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second][coordinates_.first].changeCell(
                    ENTITY);
        }



        if (type == STAIRS_UP || type == STAIRS_DOWN) {
            Level &now = dungeon.getLevels()[dungeon.getLevelNumber()];

            Level &next = type == STAIRS_UP ?  dungeon.getLevels()[dungeon.getLevelNumber() - 1] :
                    dungeon.getLevels()[dungeon.getLevelNumber() + 1];

            for (auto &it :now.getItems())
                it->changeVisible(false);

            for (auto &it :next.getItems())
                it->changeVisible(true);


            for (auto &it: equipment_) {
                if (it) {
                    it->changeVisible(true);

                    next.addItem(it);

                    now.deleteItem(it);
                }
            }


            if (type == STAIRS_UP) --dungeon.levelNumber_;
            else ++dungeon.levelNumber_;

        }


        return true;
    }


    Enemy::Enemy(std::string name, size_t maxHealth, size_t damage, size_t defence, size_t experience, std::pair<size_t, size_t> coord ,std::shared_ptr<IItem>  item):
        name_{std::move(name)}, currentHealth_{maxHealth}, maxHealth_{maxHealth}, damage_{damage}, defence_{defence},experience_{experience}, item_{std::move(std::move(item))}, coordinates_{coord} {} // возможно тут еще натуральый элемент


    void Enemy::getHit(size_t hit)  {
        if (static_cast<int>(currentHealth_ - hit) <= 0){
            isLive_ = false;

        }
        currentHealth_ -= hit;


    }
    size_t Enemy::getExperience() const {return experience_;}
    size_t Enemy::getHealth() const {return currentHealth_;}
    size_t Enemy::getMaxHealth() const {return maxHealth_;}
    size_t Enemy::getDamage() const {return damage_;}
    size_t Enemy::getDefence() const {return defence_;}
    std::string Enemy::getName() const {return name_;}
    std::shared_ptr<IItem> Enemy::getItem() const {return item_;}

    bool Enemy::move(WAY_DIRECTION dirrection, Dungeon &dungeon) {

        std::lock_guard<std::mutex> lock(
                dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second+ movements[dirrection].second][coordinates_.first + movements[dirrection].first].
                        getMutex());

        CellType type = dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second+ movements[dirrection].second][coordinates_.first + movements[dirrection].first].getCellType();
        if (type == WALL || type == ENTITY || type == STAIRS_UP || type == STAIRS_DOWN){
            return false;
        }



        auto ptr = std::make_shared<Enemy>(*this);
        dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second][coordinates_.first].deleteObject(ptr);//так как на одной клетке только один врaг может быть то и имя будет одно
        dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second][coordinates_.first].changeCell(GAME_OBJECT);


        coordinates_.first += movements[dirrection].first;
        coordinates_.second += movements[dirrection].second;

        if (item_)
            item_->updateCoordinates(coordinates_);

        auto ptr1 = std::make_shared<Enemy>(*this);


        dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second][coordinates_.first].addObject(ptr1);
        dungeon.getLevels()[dungeon.getLevelNumber()].getPlayingField()[coordinates_.second][coordinates_.first].changeCell(ENTITY);

        return true;
    }

    void Enemy::moveTo(Dungeon& dungeon, std::pair<size_t, size_t> dist){
        //работа с потооком
        if (dist.first > coordinates_.first)

            move(RIGHT, dungeon);
        else if(dist.first < coordinates_.first)
            move(LEFT, dungeon);
        else if(dist.second < coordinates_.second)
            move(UP, dungeon);
        else if(dist.second > coordinates_.second)
            move(DOWN, dungeon);


    }



    InsectEnemy::InsectEnemy(std::string name, size_t maxHealth, size_t damage, size_t defence,
                             size_t experience, std::shared_ptr<Tramp::IItem> item,std::pair<size_t, size_t> coordinates, std::shared_ptr<Tramp::WeakElement> element):
            Enemy(std::move(name), maxHealth, damage, defence, experience,coordinates, std::move(item)), element_(std::move(element)) {

            }

    std::shared_ptr<WeakElement> InsectEnemy::getElement() const {return element_;}



    AnimalEnemy::AnimalEnemy(std::string name, size_t maxHealth, size_t damage, size_t defence,
                             size_t experience, std::shared_ptr<Tramp::IItem> item, std::pair<size_t, size_t> coordinates, std::shared_ptr<Tramp::WeakElement> element):
            Enemy(std::move(name), maxHealth, damage, defence, experience,coordinates, std::move(item)),element_(std::move(element)) {}

    std::shared_ptr<WeakElement> AnimalEnemy::getElement() const {return element_;}



    UndeadEnemy::UndeadEnemy(std::string name, size_t maxHealth, size_t damage, size_t defence,
                             size_t experience, std::shared_ptr<Tramp::IItem> item,std::pair<size_t, size_t> coordinates,  std::shared_ptr<Tramp::WeakElement> element):
            Enemy(std::move(name), maxHealth, damage, defence, experience, coordinates, std::move(item)) , element_(std::move(element)) {}

    std::shared_ptr<WeakElement> UndeadEnemy::getElement() const {return element_;}



    HumanoidEnemy::HumanoidEnemy(std::string name, size_t maxHealth, size_t damage, size_t defence,
                             size_t experience, std::shared_ptr<Tramp::IItem> item,std::pair<size_t, size_t> coordinates,  std::shared_ptr<Tramp::WeakElement> element):
            Enemy(std::move(name), maxHealth, damage, defence, experience, coordinates, std::move(item)), element_(std::move(element)){}

    std::shared_ptr<WeakElement> HumanoidEnemy::getElement() const {return element_;}


    DemonicEnemy::DemonicEnemy(std::string name, size_t maxHealth, size_t damage, size_t defence,
                             size_t experience, std::shared_ptr<Tramp::IItem> item, std::pair<size_t, size_t> coordinates, std::shared_ptr<Tramp::WeakElement> element):
            Enemy(std::move(name), maxHealth, damage, defence, experience,coordinates, std::move(item) ), element_(std::move(element) ){}

    std::shared_ptr<WeakElement> DemonicEnemy::getElement() const {return element_;}



}
