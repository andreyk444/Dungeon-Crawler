#include <gtest/gtest.h>

#include <Entity/entity.h>
#include <Item/Item.h>
#include <Dungeon/Dungeon.h>

using namespace Tramp;

TEST(ConstructorTest, Character){
    std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> table = {10, 20, 30, 40 ,40};
    Character character(table, MAX_ITEMS);

    ASSERT_EQ(character.getCharacteristic(Tramp::POWER), 10);
    ASSERT_EQ(character.getCharacteristic(Tramp::DEXTERITY), 20);
    ASSERT_EQ(character.getCharacteristic(Tramp::STAMINA), 30);
    ASSERT_EQ(character.getCharacteristic(Tramp::MAX_HEALTH), 40);
    ASSERT_EQ(character.getCharacteristic(Tramp::CURRENT_HEALTH), 40);

    character.getHit(5);
    ASSERT_EQ(character.getCharacteristic(Tramp::CURRENT_HEALTH), 35);

    ASSERT_EQ(character.getExperience(), 0);
    ASSERT_EQ(character.getHealth(), 35);
    ASSERT_EQ(character.getMaxHealth(), 40);
    ASSERT_EQ(character.getDefence(), 0);
    ASSERT_EQ(character.getWeapon(), nullptr);

    ASSERT_EQ(character.getEquipment(Tramp::AMULET), nullptr);
    ASSERT_EQ(character.getEquipment(Tramp::ARMOR), nullptr);
    ASSERT_EQ(character.getEquipment(Tramp::HELMET), nullptr);

    ASSERT_EQ(character.getMaxItems(), MAX_ITEMS);

    ASSERT_EQ(character.getCountKeys(), 0);

    character.upLevel(STAMINA);

    character.up_Characteristic(DEXTERITY,10);
    character.up_Characteristic(STAMINA ,10);
    character.up_Characteristic(POWER, 10);
    character.up_Characteristic(CURRENT_HEALTH, 10);
    character.up_Characteristic(MAX_HEALTH, 10 );

    ASSERT_EQ(character.getCharacteristic(Tramp::POWER), 20);
    ASSERT_EQ(character.getCharacteristic(Tramp::DEXTERITY), 30);
    ASSERT_EQ(character.getCharacteristic(Tramp::STAMINA), 40);
    ASSERT_EQ(character.getCharacteristic(Tramp::MAX_HEALTH), 50);
    ASSERT_EQ(character.getCharacteristic(Tramp::CURRENT_HEALTH), 45);

    ASSERT_EQ(character.getHitProbability(), 30);

    character.pickKeys(123);
    ASSERT_EQ(character.getCountKeys(), 123);

}

TEST(ConstructorTest, Enemy){
    Enemy enemy("BOTIK", 30, 5, 0, 10, nullptr);

    ASSERT_EQ(enemy.getHealth(), 30);
    ASSERT_EQ(enemy.getExperience(), 10);
    ASSERT_EQ(enemy.getMaxHealth(), 30);
    ASSERT_EQ(enemy.getDamage(), 5);
    ASSERT_EQ(enemy.getDefence(), 0);
    ASSERT_EQ(enemy.getName(), "BOTIK");
    ASSERT_EQ(enemy.getItem(), nullptr);

    enemy.getHit(10);
    ASSERT_EQ(enemy.getHealth(), 20);
    ASSERT_EQ(enemy.getMaxHealth(), 30);
    ASSERT_EQ(enemy.getElement(), nullptr);


}

TEST(ConstructorTest, InsectEnemy){
    InsectEnemy insectEnemy("insect", 30, 5, 0, 10, nullptr, nullptr);

    ASSERT_EQ(insectEnemy.getElement(), nullptr);
}

TEST(ConstructorTest, UndeadEnemy){
    UndeadEnemy undeadEnemy("insect", 30, 5, 0, 10, nullptr, nullptr);

    ASSERT_EQ(undeadEnemy.getElement(), nullptr);
}

TEST(ConstructorTest, AnimalEnemy){
    AnimalEnemy animalEnemy("insect", 30, 5, 0, 10, nullptr, nullptr);

    ASSERT_EQ(animalEnemy.getElement(), nullptr);
}

TEST(ConstructorTest, HumanoidEnemy){
    HumanoidEnemy humanoidEnemy("humanoid", 30, 5, 0, 10, nullptr, nullptr);

    ASSERT_EQ(humanoidEnemy.getElement(), nullptr);
}

TEST(ConstructorTest, DemonicEnemy){
    DemonicEnemy demonicEnemy("demonic", 30, 5, 0, 10, nullptr, nullptr);

    ASSERT_EQ(demonicEnemy.getElement(), nullptr);
}

TEST(CharacterMethodTest, Equip){
    std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> table = {10, 20, 30, 40 ,40};
    Character character(table, MAX_ITEMS);

    RegularEquipment equipment1(EquipmentType::AMULET,100);
    auto Pequip = std::make_shared<RegularEquipment>(equipment1);

    RegularWeapon weapon1("yes", 1, 10);
    auto Pweap = std::make_shared<RegularWeapon>(weapon1);


    character.equip(Pequip);
    character.equip(Pweap);

    character.unEquip(Pequip);
    character.unEquip(Pweap);


}


TEST(CharacterMethodTest, PickUp) {
    std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> table = {10, 20, 30, 40, 40};
    Character character(table, MAX_ITEMS);

    RegularEquipment equipment1(EquipmentType::AMULET, 100);
    auto Pequip = std::make_shared<RegularEquipment>(equipment1);
    RegularWeapon weapon1("yes", 1, 10);
    auto Pweap = std::make_shared<RegularWeapon>(weapon1);

    character.pickUp(Pequip);
    character.pickUp(Pweap);

    std::vector<std::shared_ptr<IItem>> v =  character.getItems();
    Enemy enemy("BOTIK", 30, 5, 0, 10, nullptr);
    auto ptr = std::make_shared<Enemy>(enemy);
    size_t damage = character.getDamage(ptr);
    character.throwAway(Pequip);
    character.throwAway(Pweap);

}

TEST(CharacterMethodTest, tryHackChest) {
    std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> table = {10, 20, 30, 40, 40};
    Character character(table, MAX_ITEMS);

    Chest chest("chest", 1, nullptr);

    character.tryHackChest(chest);
}

TEST(CharacterMethodTest, move){
    std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> table = {10, 20, 30, 40, 40};
    Character character(table, MAX_ITEMS);

    Enemy enemy("BOTIK", 30, 5, 0, 10, nullptr);
    InsectEnemy insectEnemy("insect", 30, 5, 0, 10, nullptr, nullptr);
    HumanoidEnemy humanoidEnemy("humanoid", 30, 5, 0, 10, nullptr, nullptr);
    DemonicEnemy demonicEnemy("demonic", 30, 5, 0, 10, nullptr, nullptr);
    std::vector<Enemy> enemies = {enemy, insectEnemy, humanoidEnemy, demonicEnemy};



    DungeonCell cell1(Tramp::WALL);
//    DungeonCell cell2(Tramp::DOOR_CLOSE);
//    DungeonCell cell3(Tramp::DOOR_OPEN);
    DungeonCell cell4(Tramp::GAME_OBJECT);
    DungeonCell cell5(Tramp::UPSTAIRS_DOWN);
    DungeonCell cell6(Tramp::UPSTAIRS_UP);
    std::vector<std::shared_ptr<IGameObject>> v;
    RegularWeapon weapon("name",10, 20 );
    std::shared_ptr<IGameObject> sh = std::make_shared<RegularWeapon>(weapon);
    v.push_back(sh);
    std::vector<std::shared_ptr<IGameObject>> v2;
    RegularEquipment equipment(Tramp::ARMOR, 21);
    std::shared_ptr<IGameObject> sh1 = std::make_shared<RegularEquipment>(equipment);
    std::shared_ptr<IGameObject> sh2 = std::make_shared<RegularWeapon>(weapon);
    v2.push_back(sh1);
    v2.push_back(sh2);
    std::vector<std::shared_ptr<IGameObject>> v3;
    ArtifactEquipment eq1(Tramp::HELMET,10, 20 );
    std::shared_ptr<IGameObject> sh3 = std::make_shared<ArtifactEquipment>(eq1);
    v3.push_back(sh3);
    DungeonCell cell7(v);
    DungeonCell cell8(v3);
    DungeonCell cell9(v2);
    Matrix<DungeonCell> matrix(6, 8);
    matrix[1][2] = cell1;
//    matrix[1][3] = cell2;
//    matrix[2][2] = cell3;
    matrix[1][5] = cell4;
    matrix[3][2] = cell5;
    matrix[4][2] = cell6;
    matrix[1][7] = cell7;
    matrix[1][1] = cell8;
    matrix[5][2] = cell9;
    Level level(std::move(matrix));

    for (size_t i = 0; i < level.getPlayingField().rows(); ++i) {
        for (size_t j = 0; j < level.getPlayingField().columns(); ++j) {
            if (i ==0 || i ==level.getPlayingField().rows() || j == 0 || j== level.getPlayingField().columns() - 1 ){
                level.getPlayingField()[i][j].changeCell(WALL);
            }
        }
    }

    std::vector<Level> levels = {level};

    Dungeon dung(character, enemies, levels);

    character.move(Tramp::DOWN, dung.getLevels()[dung.getLevelNumber()]);
    enemy.moveTo(dung.getLevels()[dung.getLevelNumber()], std::pair<size_t, size_t>(1,1));
}

