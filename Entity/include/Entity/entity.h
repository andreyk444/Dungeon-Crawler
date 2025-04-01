

#ifndef Entity_hpp
#define Entity_hpp

#include <iostream>
#include <utility>
#include <vector>
#include <array>
#include <unordered_map>
#include  <gameObject/GameObject.h>

#include <Item/Item.h>

namespace Tramp {


#define UP_LEVEL_CHARACTISTIC 15
#define DEXTERITY_MULTIPLEER 20
#define MAX_ITEMS 5
#define DAMAGE_BY_HANDS 5

    enum CharacteristicType :unsigned ;
    enum EquipmentType :unsigned ;

    class WeakElement;
    class InatureElement;
    class Dungeon;

    class Level;


    enum WAY_DIRECTION: unsigned{
        UP = 0,
        DOWN,
        LEFT,
        RIGHT
    };

    static inline std::array<std::pair<int, int>, 4> movements
            {std::pair{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

    class IEntity: public IGameObject{
    public:

        virtual void getHit(size_t)  = 0;
        [[nodiscard]] virtual size_t getExperience() const = 0;
        [[nodiscard]] virtual size_t getHealth() const = 0;
        [[nodiscard]] virtual size_t getMaxHealth() const = 0;
        //[[nodiscard]] virtual size_t getDamage() const = 0;
        [[nodiscard]] virtual size_t getDefence() const = 0;
        [[nodiscard]] virtual  std::pair<size_t, size_t>& getCoordinates() = 0;

        virtual bool move(WAY_DIRECTION, Dungeon& ) = 0;
    };

    class Character: public IEntity {
    private:
        std::string name_ = "Charater";

        std::pair<size_t ,size_t> coordinates_ = {1, 1};
        //Character(std::array<size_t, 5> tableCharacteristics, size_t max_items);

        std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> tableCharacteristics_{};

        size_t experience_{};

        std::shared_ptr<IWeapon> weapon_;

        std::array<std::shared_ptr<IEquipment>, EQUIPMENT_TYPE_SIZE> equipment_;
        static const size_t max_equipment_ = EQUIPMENT_TYPE_SIZE;

        std::vector<std::shared_ptr<IItem>> items_;
        size_t max_items_{};

        size_t countKeys_{};
        bool isLive_ = true;
    public:

        [[nodiscard]] bool isLive() const{return isLive_;}

        Character() = delete;
        ~Character() override = default;
        Character(std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> , size_t);
        [[nodiscard]] std::string getName() const override {return name_;}

        void unEquip(std::shared_ptr<IEquipable>);
        void equip(const std::shared_ptr<IEquipable>&);

        void throwAway(const std::shared_ptr<IItem>&);
        void pickUp(const std::shared_ptr<IItem>&);

        void tryHackChest(Chest &);//открывает или нет сундук

        void upLevel(CharacteristicType);
        void up_Characteristic(CharacteristicType, size_t);
        void pickKeys(size_t count);

        void getHit(size_t)  override;
        [[nodiscard]] size_t getExperience() const override;
        [[nodiscard]] size_t getHealth() const override;
        [[nodiscard]] size_t getMaxHealth() const override;
        [[nodiscard]] size_t getDefence() const override;
        bool move(WAY_DIRECTION, Dungeon&) override;
        [[nodiscard]] std::pair<size_t, size_t>& getCoordinates()  override{return coordinates_;}

        [[nodiscard]] size_t getDamage(std::shared_ptr<Enemy>) const;

        [[nodiscard]] std::shared_ptr<IWeapon> getWeapon() const;
        [[nodiscard]] size_t getCharacteristic(CharacteristicType) const;
        [[nodiscard]] std::shared_ptr<IEquipment> getEquipment(EquipmentType) const;
        [[nodiscard]] std::vector<std::shared_ptr<IItem>> getItems() const;// может один элемент по индексу возвращать
        [[nodiscard]] size_t getHitProbability() const;
        double getHackingProbability() ;
        [[nodiscard]] size_t getMaxItems() const;
        [[nodiscard]] size_t getCountKeys() const;


    };

    class Enemy : public IEntity {
    protected:
        std::string name_;
        std::pair<size_t ,size_t> coordinates_;

        size_t currentHealth_;
        size_t maxHealth_;

        size_t damage_;
        size_t defence_;

        size_t experience_;
        std::shared_ptr<IItem> item_;

        bool isLive_ = true;



    public:
        ~Enemy() override = default;
        Enemy() = delete;
//        Enemy& operator = (const Enemy& enemy) = default;
//        Enemy& operator = (Enemy&& enemy) noexcept  = default;
        Enemy(std::string, size_t maxHealth, size_t, size_t, size_t, std::pair<size_t , size_t>, std::shared_ptr<IItem>);


        [[nodiscard]] bool isLive() const{return isLive_;}

        void getHit(size_t)  override;
        [[nodiscard]] size_t getExperience() const override;
        [[nodiscard]] size_t getHealth() const override;
        [[nodiscard]] size_t getMaxHealth() const override;
        [[nodiscard]] size_t getDamage() const;
        [[nodiscard]] size_t getDefence() const override;
        [[nodiscard]] std::pair<size_t, size_t>& getCoordinates() override{return coordinates_;}
        bool move(WAY_DIRECTION, Dungeon&) override;


        [[nodiscard]] std::string getName() const override;

        [[nodiscard]] std::shared_ptr<IItem> getItem() const;//что выпадает при смерти
        void setItem(std::shared_ptr<IItem>& ptr){

            auto itemV = std::dynamic_pointer_cast<RegularEquipment>(ptr);

            if (itemV){
                itemV->changeVisible(false);
                itemV->updateCoordinates(coordinates_);

                item_ = itemV;//std::make_shared<RegularEquipment>(*

            }

        }


        void moveTo( Dungeon&, std::pair<size_t, size_t>);


        [[nodiscard]] virtual  std::shared_ptr<WeakElement> getElement() const{return nullptr;};

//        [[nodiscard]]  std::shared_ptr<WeakElement> getElement() const;

    };

    class InsectEnemy: public Enemy{
    private:
        std::shared_ptr<WeakElement> element_;
    public:
        ~InsectEnemy() override = default;
        InsectEnemy() = delete;
        InsectEnemy(std::string, size_t maxHealth, size_t, size_t, size_t, std::shared_ptr<IItem>,std::pair<size_t, size_t> coordinates,  std::shared_ptr<WeakElement>);
        [[nodiscard]]  std::shared_ptr<WeakElement> getElement() const override;



    };

    class AnimalEnemy: public Enemy{
    private:
        std::shared_ptr<WeakElement> element_;
    public:
        AnimalEnemy() = delete;
        ~AnimalEnemy() override = default;
        AnimalEnemy(std::string, size_t maxHealth, size_t, size_t, size_t, std::shared_ptr<IItem>,std::pair<size_t, size_t> coordinates,  std::shared_ptr<WeakElement>);
        [[nodiscard]]  std::shared_ptr<WeakElement> getElement() const override;

    };

    class UndeadEnemy: public Enemy{
    private:
        std::shared_ptr<WeakElement> element_;
    public:
        UndeadEnemy() = delete;
        ~UndeadEnemy() override = default;
        UndeadEnemy(std::string, size_t maxHealth, size_t, size_t, size_t, std::shared_ptr<IItem>,std::pair<size_t, size_t> coordinates,  std::shared_ptr<WeakElement>);

        [[nodiscard]]  std::shared_ptr<WeakElement> getElement() const override;

    };

    class HumanoidEnemy: public Enemy{
    private:
        std::shared_ptr<WeakElement> element_;
    public:
        HumanoidEnemy() = delete;
        HumanoidEnemy(std::string, size_t maxHealth, size_t, size_t, size_t, std::shared_ptr<IItem>,std::pair<size_t, size_t> coordinates,  std::shared_ptr<WeakElement>);
        ~HumanoidEnemy() override = default;

        [[nodiscard]]  std::shared_ptr<WeakElement> getElement() const override;

    };

    class DemonicEnemy: public Enemy{
    private:
        std::shared_ptr<WeakElement> element_;
    public:
        DemonicEnemy() =delete;
        DemonicEnemy(std::string, size_t maxHealth, size_t, size_t, size_t, std::shared_ptr<IItem>,std::pair<size_t, size_t> coordinates,  std::shared_ptr<WeakElement>);
        ~DemonicEnemy() override = default;

        [[nodiscard]]  std::shared_ptr<WeakElement> getElement() const override;

    };
}


#endif
