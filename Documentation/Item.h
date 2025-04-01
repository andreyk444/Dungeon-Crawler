#ifndef Item_hpp
#define Item_hpp

#include <gameObject/GameObject.h>
#include <Element/element.h>
#include <string>

namespace Tramp {

    /**
 @brief Перечисление типов характеристик героя
 */
    enum CharacteristicType: unsigned {
        POWER = 0,
        DEXTERITY,//ловкость
        STAMINA,
        MAX_HEALTH,
        CURRENT_HEALTH,
        CHARACTERISTICHS_TYPE_SIZE
    };

    /**
     @brief Перечисление возможных типов снаряжения
     */
    enum EquipmentType {
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
        //~IItem() override = default;

    };

    /**
    @brief Класс используемых предметов
    */
    class IUseable : public IItem{
    public:


        //~IUseable() override = default;

        /**
         @brief Метод для использования предмета на каком-либо игровом объекте
         @param IGameObject игровой объект, на котором будет использован предмет

         */
        virtual void use(IGameObject& ) const  = 0;
    };

    /**
      @brief Класс надеваемых предметов
     */
    class IEquipable: public IItem{
    public:
       // ~IEquipable() override = default;
    };

    /**
         @brief Класс Зелье
    */
    class Potion : public IUseable {
    private:
        //!Тип характеристики персонажа, которое повышает зелье
        CharacteristicType characteristicType_;
        //! Размер на сколько будет повышена характеристика
        size_t changeSize_;
    public:
        //!Конструктор для создания зелья
        Potion(CharacteristicType, size_t );
        //Potion() = default;

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
        void use(IGameObject& ) const override ;//на герое или на враге
    };

    /**
     @brief Класс Связка ключей
    */
    class BunchOfKeys : public IUseable {
    private:
        //!Количество ключей в связке
        size_t count_;
    public:
        //! Конструктор для создания связки ключей
        explicit BunchOfKeys(size_t);

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
        void use(IGameObject& ) const override ;//только на герое действует или на сундуке

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
        virtual size_t generateDamage() = 0;
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
        virtual size_t generateDefence() = 0;
    };

    /**
     @brief Класс обычного снаряжения
    */
    class RegularEquipment : public IEquipment {
    private :
        //! Размер защиты того или иного снаряжения
        size_t defence_;
        //!Тип снаряжения
        EquipmentType equipmentType_;
    public:
        //~RegularEquipment()  override = default;
        //!Конструктор для создания обычного снаряжения
        RegularEquipment(EquipmentType , size_t );
        //!Удаленный конструктор, не принимающий аргументов
        RegularEquipment() = delete;

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
        [[nodiscard]] EquipmentType getEquipmentType() const;

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

    public:
        //~RegularWeapon() override = default;
        //!Удаленный конструктор обычного оружия, не принимающий аргументов
        RegularWeapon() = delete;
        //!Конструктор для создания обычного оружия
        RegularWeapon(std::string, size_t, size_t);

        /**
          @brief Метод для вычисления наносимого урона
          @return Размер наносимого урона

          */
        size_t generateDamage() override;

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
        [[nodiscard]] std::string getName() const;
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
        //!Конструктор для создания афртефактного  снаряжения
        ArtifactEquipment(EquipmentType, size_t, size_t);

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

        //!Конструктор для создания зачарованного оружия
        EnchartedWeapon(std::string, size_t,size_t,  const std::shared_ptr<InatureElement> &);

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
        size_t generateDamage() override;


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
        //!Конструктор для создания артифактного оружия
        ArtifactWeapon(std::string, size_t,size_t, size_t);

        /**
          @brief Метод для получения бонуса к наносимому урону
          @return Бонус к наносимому урону

          */
        [[nodiscard]] size_t getDamageBonus() const;

        /**
          @brief Метод для генерации наносимого урона
          @return Наносимый урон

          */
        size_t generateDamage() override;

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
        //!Конструктор для создания артифактного и зачарованного оружия
        ArtifactAndEnchartedWeapon(std::string, size_t, size_t,size_t,  const std::shared_ptr<InatureElement> &);

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
        size_t generateDamage() override;

    };

    /**
      @brief Класс зачарованного и артефактного оружия

      */
    class Chest : public IGameObject {
    private:
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
