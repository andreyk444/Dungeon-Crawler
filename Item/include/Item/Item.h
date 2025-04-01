#ifndef Item_hpp
#define Item_hpp


#include <string>
#include <Utils/Cast.h>
#include <gameObject/GameObject.h>

#include <map>

namespace Tramp {
    class IItem;
}

class ItemManager {
public:
    using factory_t = std::function<std::shared_ptr<Tramp::IItem>()>;
private:
    ItemManager() = default;
    std::map<std::string, factory_t> factories;
public:

    void addFactory(std::string name, factory_t factory) {
        factories.emplace(std::move(name), std::move(factory));
    }

    void removeFactory(const std::string& name) {
        factories.erase(name);
    }

    class ItemModuleToken {
        ItemManager& manager;
        std::string name;
    public:
        ItemModuleToken(ItemManager& mgr, std::string name, factory_t factory): manager(mgr), name(std::move(name)) {
            manager.addFactory(this->name, std::move(factory));
        }

        ~ItemModuleToken() {
            manager.removeFactory(name);
        }

    };

    static ItemManager& getInstance() {
        static ItemManager manager;
        return manager;
    }

    static ItemModuleToken registerModule(std::string name, factory_t factory) {
        return ItemModuleToken(getInstance(), std::move(name), std::move(factory));
    }

};

namespace Tramp {
    class Enemy;
  //  class IGameObject;
    class InatureElement;

    /**
 @brief Перечисление типов характеристик героя
 */
    enum CharacteristicType: unsigned {
        POWER = 0,
        DEXTERITY,//ловкость
        STAMINA,
        CURRENT_HEALTH,
        MAX_HEALTH,
        CHARACTERISTICHS_TYPE_SIZE
    };

    /**
     @brief Перечисление возможных типов снаряжения
     */
    enum EquipmentType:unsigned {
        AMULET = 0,
        HELMET,
        ARMOR,
        EQUIPMENT_TYPE_SIZE
    };


    /**
     @brief Класс предмета
     */
    class IItem : public IGameObject {
    public:
        ~IItem() override = default;

        virtual void updateCoordinates(std::pair<size_t, size_t>& ) = 0;
        virtual  std::pair<size_t, size_t>& getCoordinates() = 0;
        virtual const bool isVisible() const = 0;
        virtual void changeVisible(bool) = 0;


    };

    /**
    @brief Класс используемых предметов
    */
    class IUseable : public IItem{
    public:


        //~IUseable() override = default;

        /**
         @brief Метод для использования предмета на каком-либо игровом объекте
         @param gameObject игровой объект, на котором будет использован предмет

         */
        virtual void use( std::shared_ptr<IGameObject> gameObject) const  = 0;
    };

    /**
      @brief Класс надеваемых предметов
     */
    class IEquipable: public IItem{
    public:
        virtual std::pair<size_t, size_t>& getCoordinates() = 0;
       // ~IEquipable() override = default;
    };

    /**
         @brief Класс Зелье
    */
    class Potion : public IUseable {
    private:
        std::pair<size_t, size_t> coordinates_;
        //!Тип характеристики персонажа, которое повышает зелье
        CharacteristicType characteristicType_;
        //! Размер на сколько будет повышена характеристика
        size_t changeSize_;
        std::string name_ = "Potion";
        bool isVisible_;

    public:
       void changeVisible(bool v) override{isVisible_ = v;};

        const bool isVisible() const override{return isVisible_;}
        void updateCoordinates(std::pair<size_t, size_t>& coordinates) override{coordinates_ = coordinates;}
        std::pair<size_t, size_t>& getCoordinates() override{return coordinates_;}

        /**
         @brief Конструткор для создания зелья
         @param characteristicType Тип характеристики персонажа, которое повышает зелье
         @param changeSize Размер на сколько будет повышена характеристика


         */

        Potion(CharacteristicType characteristicType, size_t changeSize);
        //Potion() = default;
        [[nodiscard]] std::string getName() const override{return name_;}

       // ~Potion() override = default;


        /**
          @brief Метод для получения размера на сколько будет повышена характеристика
          @return Размер на сколько будет повышена характеристика

          */
        [[nodiscard]] size_t getChangeSize() const;

        /**
          @brief Метод для получения типа характеристики персонажа, который повысит зелье
          @return Тип характеристики персонажа, которое повышает зелье

          */
        [[nodiscard]] CharacteristicType getCharacteristicType() const;

        /**
         @brief Метод для использования предмета на каком-либо игровом объекте
         @param IGameObject игровой объект, на котором будет использован предмет
         */
        void use( std::shared_ptr<IGameObject> ) const override ;//на герое или на враге
    };

    /**
     @brief Класс Связка ключей
    */
    class BunchOfKeys : public IUseable {
    private:
        std::pair<size_t, size_t> coordinates_;
        //!Количество ключей в связке
        size_t count_;
        std::string name_ = "Bunch of keys";
        bool isVisible_;

    public:
        void changeVisible(bool v) override{isVisible_ = v;};

        const bool isVisible() const override{return isVisible_;}

        void updateCoordinates(std::pair<size_t, size_t>& coordinates) override{coordinates_ = coordinates;}
        std::pair<size_t, size_t>& getCoordinates() override{return coordinates_;}

        [[nodiscard]] std::string getName() const override{return name_;}

        /**
         @brief Конструткор для создания связки ключей
         @param count Количество ключей в связке

         */
        explicit BunchOfKeys(size_t count);

        //!Удаленный конструктор без аргументов
        BunchOfKeys() = delete;
        //~BunchOfKeys() override = default;

        /**
          @brief Метод для получения количества ключей в связке
          @return Количество ключей в связке

          */
        [[nodiscard]] size_t getCount() const;

        /**
         @brief Метод для использования предмета на каком-либо игровом объекте
         @param IGameObject игровой объект, на котором будет использован предмет
         */
        void use( std::shared_ptr<IGameObject> gameObject) const  override;


    };

    /**
     @brief Интерфес оружия
    */
    class IWeapon : public IEquipable {
    public:
        //~IWeapon() override = default;

        /**
          @brief Метод для вычисления наносимого урона
          @return Размер наносимого урона

          */
        virtual size_t generateDamage(std::shared_ptr<Enemy>) = 0;
    };

    /**
     @brief Интерфес снаряжения
    */
    class IEquipment : public IEquipable {
    public:
       // ~IEquipment() override =default;

        /**
          @brief Метод для вычисления защиты
          @return Размер защиты

          */
        virtual void setCoordinates(std::pair<size_t, size_t>& coo) = 0;
        virtual size_t generateDefence() = 0;
        [[nodiscard]] virtual  EquipmentType getEquipmentType() const = 0;

    };

    /**
     @brief Класс обычного снаряжения
    */
    class RegularEquipment : public IEquipment {
    private :
        std::pair<size_t, size_t> coordinates_;
        //! Размер защиты того или иного снаряжения
        size_t defence_;
        //!Тип снаряжения
        EquipmentType equipmentType_;
        std::string name_ = "Equipment";
        bool isVisible_ = true;


    public:
        RegularEquipment():  defence_(0),coordinates_(std::pair<size_t, size_t>{}),
        equipmentType_(EQUIPMENT_TYPE_SIZE),name_("EquipmentCopy"){

        }

        void changeVisible(bool v) override{isVisible_ = v;};


        const bool isVisible() const override{return isVisible_;}

        [[nodiscard]] std::string getName() const override{return name_;}
        std::pair<size_t, size_t>& getCoordinates()  override{return coordinates_;}
        void setCoordinates(std::pair<size_t, size_t>& coo) override {coordinates_ = coo;}

//        const std::pair<size_t, size_t>& getCoordinates() const {return coordinates_;}
        void updateCoordinates(std::pair<size_t, size_t>& coo) override{
            coordinates_.first = coo.first;
            coordinates_.second = coo.second;
        }

        //~RegularEquipment()  override = default;
        /**
         @brief Конструткор для создания обычного снаряжения
         @param   equipmentType Тип снаряжения
         @param  defence Размер защиты того или иного снаряжения

         */
        RegularEquipment(EquipmentType  equipmentType, size_t  defence,std::pair<size_t, size_t>& );
        //!Удаленный конструктор, не принимающий аргументов


        /**
          @brief Метод для вычисления зашиты
          @return Размер защиты

          */
         size_t generateDefence() override;

        /**
          @brief Метод для получения зашиты
          @return Размер защиты

          */
        [[nodiscard]] size_t getDifance() const;

        /**
          @brief Метод для получения типа снаряжения
          @return Тип снаряжения

          */
        [[nodiscard]] EquipmentType getEquipmentType() const override;

    };


    /**
     @brief Класс обычного оружия
    */
    class RegularWeapon : public IWeapon {
    private:
        //!Имя оружия
        std::string name_;
        //!Наноосимый урон оружием
        size_t damage_;
        //!Максимальный наносимый урон оружием
        size_t maxDamage_;

        std::pair<size_t, size_t> coordinates_;
        bool isVisible_;

    public:

        void changeVisible(bool v) override{isVisible_ = v;};

        const bool isVisible() const override{return isVisible_;}

        std::pair<size_t, size_t>& getCoordinates()  override{return coordinates_;}


        //~RegularWeapon() override = default;
        //!Удаленный конструктор обычного оружия, не принимающий аргументов
        RegularWeapon() = delete;
        /**
         @brief Конструткор для создания обычного оружия
         @param   name Имя оружия
         @param   damage Наноосимый урон оружием
         @param  maxDamage Максимальный наносимый урон оружием

         */
        RegularWeapon(std::string name, size_t damage, size_t maxDamage);

        /**
          @brief Метод для вычисления наносимого урона
          @return Размер наносимого урона

          */
        size_t generateDamage(std::shared_ptr<Enemy>) override;

        /**
          @brief Метод для получения размера урона
          @return Размер наносимого урона

          */
        [[nodiscard]] size_t getDamage() const;

        /**
          @brief Метод для получения максимального размера урона
          @return Размер максимального наносимого урона

          */
        [[nodiscard]] size_t getMaxDamage() const;

        /**
          @brief Метод для получения названия оружия
          @return Название оружия

          */
        [[nodiscard]] std::string getName() const override;
    };


    /**
     @brief Класс артифактных предметов
    */
    class IArtifact {
    public:
       // virtual ~IArtifact() = default;

    };

    /**
     @brief Класс зачарованных предметов
    */
    class IEncharted {
    public:
        //virtual ~IEncharted() = default;

        /**
          @brief Метод для получения природного элемента
          @return Природный элемент

          */
        [[nodiscard]] virtual std::shared_ptr<InatureElement> getElement() const  = 0;
    };

    /**
     @brief Класс артефактного снаряжения
    */
    class ArtifactEquipment : public RegularEquipment, public IArtifact {
    private:
        //!Бонус для защиты
        size_t defenceBonus_;

    public:

        //~ArtifactEquipment() override  = default;
        //!Удаленный конструктор, не принимающий аргументов
        ArtifactEquipment() = delete;

        /**
         @brief Конструктор для создания афртефактного  снаряжения
         @param   equipmentType Тип снаряжения
         @param   defence Размер защиты
         @param  defence_bonus Размер бонусной защиты

         */

        ArtifactEquipment(EquipmentType equipmentType, size_t defence, size_t defence_bonus,std::pair<size_t, size_t>);

        /**
          @brief Метод для генерации размера защиты
          @return Размер защиты

          */
        size_t generateDefence() override;

        /**
          @brief Метод для получения бонуса для защиты
          @return Бонус для защиты

          */
        [[nodiscard]] size_t getDifanceBonus() const;
    };

    /**
      @brief Класс зачарованного оружия
     */
    class EnchartedWeapon : public RegularWeapon, public IEncharted {
    private:
        //! Природный элемент зачарования, из которого можно понять, по чему наносит повышенный урон, а по чему пониженный
        std::shared_ptr<InatureElement> element_;//элемент которым явл оружие
        //InatureElement* elementIn_;//элемент по которому оружие наносит повышенный или пониженный урон
    public:
        //~EnchartedWeapon() override = default;
        //!Удаленный конструктор, не принимающий аргументов
        EnchartedWeapon() = delete;

        /**
         @brief Конструктор для создания зачарованного оружия

         @param   name Имя оружия
         @param   damage Размер атаки
         @param  damageMax Размер максимальной атаки
         @param  element Элемент, которым зачаровано оружие

         */
        EnchartedWeapon(std::string name, size_t damage,size_t damageBonus,  const std::shared_ptr<InatureElement> &element);

      //  InatureElement* getElementOut() const;

        /**
          @brief Метод для получения природного элемента
          @return Природный элемент

          */
        [[nodiscard]] std::shared_ptr<InatureElement> getElement() const override;

        /**
          @brief Метод для генерации размера защиты
          @return Размер защиты

          */
        size_t generateDamage(std::shared_ptr<Enemy>) override;


    };

    /**
      @brief Класс артефактного оружия
     */
    class ArtifactWeapon : public RegularWeapon, public IArtifact {
    private:
        //!Бонус к наносимому урону
        size_t damageBonus_;
    public:
        //~ArtifactWeapon() override = default ;
        //!Удаленный конструктор, не принимающий аргументов
        ArtifactWeapon() = delete;
        /**
         @brief Конструктор для создания артифактного оружия

         @param   name Имя оружия
         @param   damage Размер атаки
         @param  max_damage Размер максимальной атаки
         @param  damage_bonus Размер атаки, добавляемой к основной

         */
        ArtifactWeapon(std::string name, size_t damage,size_t max_damage, size_t damage_bonus);

        /**
          @brief Метод для получения бонуса к наносимому урону
          @return Бонус к наносимому урону

          */
        [[nodiscard]] size_t getDamageBonus() const;

        /**
          @brief Метод для генерации наносимого урона
          @return Наносимый урон

          */
        size_t generateDamage(std::shared_ptr<Enemy>) override;

    };

    /**
      @brief Класс зачарованного и артефактного оружия

      */
    class ArtifactAndEnchartedWeapon : public RegularWeapon, public IArtifact, public IEncharted {
    private:
        //!Бонус к наносимому урону
        size_t damageBonus_;
        //! Природный элемент зачарования, из которого можно понять, по чему наносит повышенный урон, а по чему пониженный

        std::shared_ptr<InatureElement> element_;
    public:
        //~ArtifactAndEnchartedWeapon() override = default;
        //!Удаленный конструктор, не принимающий аргументов
        ArtifactAndEnchartedWeapon() = delete;
        /**
         @brief Конструктор для создания артифактного и зачарованного оружия

         @param   name Имя оружия
         @param   damage Размер атаки
         @param  max_damage Размер максимальной атаки
         @param  damage_bonus Размер атаки, добавляемой к основной
         @param  element Элемент, который дает зачарование

         */
        ArtifactAndEnchartedWeapon(std::string name, size_t damage, size_t max_damage ,size_t damage_bonus,  std::shared_ptr<InatureElement> element);

        /**
          @brief Метод для получения бонуса к наносимому урону
          @return Бонус к наносимому урону

          */
        [[nodiscard]] size_t getDamageBonus() const;

        /**
          @brief Метод для получения природного элемента
          @return Природный элемент

          */
        [[nodiscard]] std::shared_ptr<InatureElement> getElement() const override;

        /**
          @brief Метод для генерации наносимого урона
          @return Наносимый урон

          */
        size_t generateDamage(std::shared_ptr<Enemy>) override;

    };

    /**
      @brief Класс зачарованного и артефактного оружия

      */
    class Chest : public IGameObject {
    private:
        std::pair<size_t, size_t> coordinates_;
        //!Название сундука
        std::string name_;
        //!Уровень сундука
        size_t level_;
        //!Предмет, лежащий в сундуке
        std::shared_ptr<IItem> item_;
        //!Состояние сундука
        bool isOpen_;

    public:

        // ~Chest()  override = default;
       //!Удаленный конструктор, не принимающий аргументов
        Chest() = delete;

       //!Конструктор для создания сундука
        Chest(std::string, size_t, const std::shared_ptr<IItem> &);

        /**
          @brief Метод для получения уровня сундука
          @return Уровень сундука

          */
        [[nodiscard]] size_t getLevel() const;

        /**
          @brief Метод для получения предмета, лежащего в сундуке
          @return Предмет, лежащий в сундуке

          */
        [[nodiscard]] std::shared_ptr<IItem> getItem() const;
        [[nodiscard]] std::string getName() const override {return name_;}


        /**
          @brief Метод для проверки, открыт ли сундук
          @return Открыт или закрыт сундук

          */
        [[nodiscard]] bool isOpen() const;

        /**
          @brief Метод для открытия сундука
          */
        void open();



    };


}
#endif 
