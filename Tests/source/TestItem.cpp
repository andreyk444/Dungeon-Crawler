#include <gtest/gtest.h>

#include <Item/Item.h>
#include <Element/element.h>
#include <Entity/entity.h>


using namespace Tramp;


TEST(ConstructorTest, Potion){
	Potion potion1(CharacteristicType::CURRENT_HEALTH, 100);
    Potion potion2(CharacteristicType::MAX_HEALTH , 100);
    Potion potion3(CharacteristicType::DEXTERITY, 100);
    Potion potion4(CharacteristicType::POWER, 100);
    Potion potion5(CharacteristicType::STAMINA, 100);

    ASSERT_EQ(potion1.getChangeSize(), 100);
    ASSERT_EQ(potion2.getChangeSize(), 100);
    ASSERT_EQ(potion3.getChangeSize(), 100);
    ASSERT_EQ(potion4.getChangeSize(), 100);
    ASSERT_EQ(potion5.getChangeSize(), 100);

    ASSERT_EQ(potion1.getCharacteristicType(), CURRENT_HEALTH);
    ASSERT_EQ(potion2.getCharacteristicType(), MAX_HEALTH);
    ASSERT_EQ(potion3.getCharacteristicType(), DEXTERITY);
    ASSERT_EQ(potion4.getCharacteristicType(), POWER);
    ASSERT_EQ(potion5.getCharacteristicType(), STAMINA);

}

TEST(Method_test, Potion){
    Potion potion1(CharacteristicType::CURRENT_HEALTH, 100);
    //potion1.use();

}

TEST(ConstructorTest, BunchOfKeys){
    BunchOfKeys bunch(100);

    ASSERT_EQ(bunch.getCount(), 100);
}

TEST(Method_test, BunchOfKeys){
    BunchOfKeys bunch(100);

    //use();

}

TEST(ConstructorTest, RegularEquipment ){
    RegularEquipment equipment1(EquipmentType::AMULET,100);
    RegularEquipment equipment2(EquipmentType::ARMOR ,100);
    RegularEquipment equipment3(EquipmentType::HELMET ,100);


    ASSERT_EQ(equipment1.getDifance(), 100 );
    ASSERT_EQ(equipment1.getEquipmentType(), AMULET );

    ASSERT_EQ(equipment2.getDifance(), 100 );
    ASSERT_EQ(equipment2.getEquipmentType(), ARMOR );

    ASSERT_EQ(equipment3.getDifance(), 100 );
    ASSERT_EQ(equipment3.getEquipmentType(), HELMET );
}


TEST(Method_test, RegularEquipment){
    RegularEquipment equipment1(EquipmentType::AMULET,100);
    RegularEquipment equipment2(EquipmentType::ARMOR ,100);
    RegularEquipment equipment3(EquipmentType::HELMET ,100);

    ASSERT_EQ(equipment1.generateDefence(), 100);
    ASSERT_EQ(equipment2.generateDefence(), 100);
    ASSERT_EQ(equipment3.generateDefence(), 100);

}

TEST(ConstructorTest, RegularWeapon){
    std::string name1 = "gun";
    std::string name2 = "qwe";
    std::string name3 = "zxc";

    RegularWeapon weapon1(name1, 1, 10);
    RegularWeapon weapon2(name2, 2, 20);
    RegularWeapon weapon3(name3, 5, 50);

    ASSERT_EQ(weapon1.getName(), name1);
    ASSERT_EQ(weapon2.getName(), name2);
    ASSERT_EQ(weapon3.getName(), name3);

    ASSERT_EQ(weapon1.getDamage(), 1);
    ASSERT_EQ(weapon2.getDamage(), 2);
    ASSERT_EQ(weapon3.getDamage(), 5);

    ASSERT_EQ(weapon1.getMaxDamage(), 10);
    ASSERT_EQ(weapon2.getMaxDamage(), 20);
    ASSERT_EQ(weapon3.getMaxDamage(), 50);

}

TEST(Method_test, RegularWeapon){
    RegularWeapon weapon1("gun", 1, 10);
    RegularWeapon weapon2("zxc", 2, 20);
    RegularWeapon weapon3("qwe", 5, 50);

    ASSERT_EQ(weapon1.generateDamage(nullptr), 1);
    ASSERT_EQ(weapon2.generateDamage(nullptr), 2);
    ASSERT_EQ(weapon3.generateDamage(nullptr), 5);
}


TEST(ConstructorTest, ArtifactEquipment) {
    ArtifactEquipment equipment1(EquipmentType::HELMET, 123, 12);
    ArtifactEquipment equipment2(EquipmentType::ARMOR, 12, 212);
    ArtifactEquipment equipment3(EquipmentType::AMULET, 1233, 1);

    ASSERT_EQ(equipment1.getDifanceBonus(), 123);
    ASSERT_EQ(equipment2.getDifanceBonus(), 12);
    ASSERT_EQ(equipment3.getDifanceBonus(), 1233);
}

TEST(Method_test, ArtifactEquipment) {
    ArtifactEquipment equipment1(EquipmentType::HELMET, 123, 12);
    ArtifactEquipment equipment2(EquipmentType::ARMOR, 12, 212);
    ArtifactEquipment equipment3(EquipmentType::AMULET, 1233, 1);

    ASSERT_EQ(equipment1.generateDefence(), 135);
    ASSERT_EQ(equipment2.generateDefence(), 224);
    ASSERT_EQ(equipment3.generateDefence(), 1234);


}


TEST(ConstructorTest, EnchartedWeapon) {
    Water water("Water");
    auto waterPtr = std::make_shared<Water>(water);
    EnchartedWeapon weapon("name1", 1, 10, waterPtr);

    ASSERT_EQ(weapon.getElement(), waterPtr);

    Enemy enemy("BOTIK", 30, 5, 0, 10, nullptr);
    auto ptr = std::make_shared<Enemy>(enemy);
    weapon.generateDamage(ptr);
}

TEST(ConstructorTest, ArtifactWeapon) {
    ArtifactWeapon weapon("name2", 10, 20, 30);

    ASSERT_EQ(weapon.getDamage(), 10);
    ASSERT_EQ(weapon.getMaxDamage(), 20);
    ASSERT_EQ(weapon.getDamageBonus(), 30);

    ASSERT_EQ(weapon.generateDamage(nullptr), 20);


}

TEST(ConstructorTest, ArtifactAndEnchartedWeapon){
    ArtifactAndEnchartedWeapon weapon("name3", 10, 20, 30,nullptr);

    ASSERT_EQ(weapon.getDamage(), 10);
    ASSERT_EQ(weapon.getMaxDamage(), 20);
    ASSERT_EQ(weapon.getDamageBonus(), 30);
    ASSERT_EQ(weapon.getElement(), nullptr);

    ASSERT_EQ(weapon.generateDamage(nullptr), 20);


}

TEST(ConstructorTest, Chest){
    Chest chest("chest", 1, nullptr);

    ASSERT_EQ(chest.getLevel(), 1);
    ASSERT_EQ(chest.getItem(), nullptr);
    ASSERT_EQ(chest.isOpen(), false);

    chest.open();
    ASSERT_EQ(chest.isOpen(), true);
}

TEST(MethodTest, BunchOfKeys) {
    BunchOfKeys bunch(100);

    std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> table = {10, 20, 30, 40, 40};
    Character character(table, MAX_ITEMS);

    auto ptr = std::make_shared<Character>(character);
    bunch.use(ptr);
}

TEST(MethodTest, Potion) {
    Potion potion1(CharacteristicType::CURRENT_HEALTH, 100);

    std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> table = {10, 20, 30, 40, 40};
    Character character(table, MAX_ITEMS);

    auto ptr = std::make_shared<Character>(character);
    potion1.use(ptr);
}