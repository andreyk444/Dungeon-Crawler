# Dungeon Crawler: Labyrinth of Shadows


Рогалик-подземелье на C++ с элементами RPG, созданный в учебных целях для освоения продвинутого ООП и паттернов проектирования.

## 🔥 Особенности проекта
- Полноценная система предметов с наследованием (`IItem`, `IUseable`, `IEquipable`)
- Сложная система характеристик персонажа (`CharacteristicType`)
- Различные типы врагов с элементами стихий (`InsectEnemy`, `UndeadEnemy` и др.)
- Генерация подземелий с использованием матриц (`Matrix<DungeonCell>`)
- Система инвентаря и экипировки
- Элементы стихий и их взаимодействия (`InatureElement`)

## 🏗️ Архитектура кода
```cpp
namespace Tramp {
    // Базовые интерфейсы
    class IItem : public IGameObject;
    class IUseable : public IItem;
    class IEquipable: public IItem;
    
    // Реализации предметов
    class Potion : public IUseable;
    class RegularWeapon : public IWeapon;
    class ArtifactEquipment : public RegularEquipment, public IArtifact;
    
    // Система персонажей
    class Character : public IEntity;
    class Enemy : public IEntity;
    
    // Генерация подземелий
    class DungeonCell;
    class Level;
    class Dungeon;
}
```
🧩 Ключевые компоненты

Система предметов

```cpp
enum EquipmentType {
    AMULET = 0,
    HELMET,
    ARMOR,
    EQUIPMENT_TYPE_SIZE
};

class IItem : public IGameObject {
    // Базовый интерфейс для всех предметов
    ...
};

class Potion : public IUseable {
    CharacteristicType characteristicType_;
    size_t changeSize_;
    // Реализация использования
    ...
};
```
Система персонажей

```cpp

class Character : public IEntity {
private:
    std::array<size_t, CHARACTERISTICHS_TYPE_SIZE> tableCharacteristics_;
    std::shared_ptr<IWeapon> weapon_;
    std::array<std::shared_ptr<IEquipment>, EQUIPMENT_TYPE_SIZE> equipment_;
public:
    void equip(const std::shared_ptr<IEquipable>&);
    size_t getDamage(std::shared_ptr<Enemy>) const;
    ...
};
```
Генерация уровней

```cpp
class Level {
private:
    Matrix<DungeonCell> playingField_;
    std::vector<Enemy> enemies_;
    std::vector<std::shared_ptr<IItem>> items_;
public:
    void addEnemy(Enemy &enemy);
    void killEnemy(Enemy &enemy);
    ...
};
```
🛠 Сборка и запуск

Требования:

CMake 3.10+
Компилятор с поддержкой C++17
```bash
mkdir build && cd build
cmake .. && make
./DungeonCrawler
```
📊 Статистика кода

- 10+ классов предметов
- 5+ типов врагов
- Полноценная система характеристик
- Гибкая система экипировки
- Матричная система уровней
