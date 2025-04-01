#include <gtest/gtest.h>

#include <Dungeon/Dungeon.h>
#include <vector>
#include <algorithm>


using namespace Tramp;

TEST(ConstructorTest, DungeonCell){
    DungeonCell cell(Tramp::WALL);

    std::vector<std::shared_ptr<IGameObject>> v;
    RegularWeapon weapon("name",10, 20 );
    auto sh = std::make_shared<RegularWeapon>(weapon);

    v.push_back(sh);

    DungeonCell cell2(v);
    DungeonCell cell3;

    ASSERT_EQ(cell.getCellType(), WALL);
    ASSERT_EQ(cell2.getCellType(), GAME_OBJECT);
    ASSERT_EQ(cell3.getCellType(), GAME_OBJECT);

    ASSERT_TRUE(cell.getGameObjects().empty());
    ASSERT_EQ(cell2.getGameObjects(), v);


}

TEST(ConstructorTest, DungeonLevel){

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
//////////////////
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

    Matrix<DungeonCell> matrix(5, 8);
    matrix[1][2] = cell1;
//    matrix[1][3] = cell2;
//    matrix[2][2] = cell3;
    matrix[1][5] = cell4;
    matrix[3][2] = cell5;
    matrix[4][2] = cell6;
    matrix[0][7] = cell7;
    matrix[1][1] = cell8;
    matrix[0][2] = cell9;



    Level level(std::move(matrix));

    for (size_t i = 0; i < level.getPlayingField().rows(); ++i) {
        for (size_t j = 0; j < level.getPlayingField().columns(); ++j) {
       //     std::cout <<level.getPlayingField().at(i, j).getGameObjects().size() << " ";
            ASSERT_EQ(level.getPlayingField().at(i, j).getGameObjects(), level.getPlayingField()[i][j].getGameObjects());
        }
      //  std::cout << "\n";
    }
//
//    level.getPlayingField()[1][1].changeCell(DOOR_OPEN);
//    ASSERT_EQ(level.getPlayingField()[1][1].getCellType(), DOOR_OPEN);

    level.getPlayingField()[0][2].deleteObject(sh1);
    ASSERT_EQ(level.getPlayingField()[0][2].getGameObjects().size(), 1);

    level.getPlayingField()[0][2].addObject(sh1);
    ASSERT_EQ(level.getPlayingField()[0][2].getGameObjects().size(), 2);



}

TEST(ConstructorTest, Dungeon){
    Enemy enemy("BOTIK", 30, 5, 0, 10, nullptr);
    InsectEnemy insectEnemy("insect", 30, 5, 0, 10, nullptr, nullptr);
    HumanoidEnemy humanoidEnemy("humanoid", 30, 5, 0, 10, nullptr, nullptr);
    DemonicEnemy demonicEnemy("demonic", 30, 5, 0, 10, nullptr, nullptr);
    std::vector<Enemy> enemies = {enemy, insectEnemy, humanoidEnemy, demonicEnemy};

    std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> table = {10, 20, 30, 40 ,40};
    Character character(table, MAX_ITEMS);

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
    ASSERT_EQ(dung.getCharacter().getName(), character.getName());
    ASSERT_EQ(dung.getEnemies().size(), enemies.size());
    ASSERT_EQ(dung.getLevels().size(), levels.size());
    ASSERT_EQ(dung.getLevelNumber(), 0);


}