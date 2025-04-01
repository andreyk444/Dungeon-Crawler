//#include <thread>

#include <SFML/Graphics.hpp>
#include <Dungeon/Dungeon.h>
#include <View/View.h>
#include <Controller/Controller.h>
#include <Download/download.h>

using namespace Tramp;

void endGame(sf::RenderWindow *window, const std::string &filename) {
    sf::Texture texture;
    texture.loadFromFile(filename);


    sf::Sprite sprite(texture);
    sprite.setScale(window->getSize().x / sprite.getLocalBounds().width,
                    window->getSize().y / sprite.getLocalBounds().height);

    window->clear();
    window->draw(sprite);
    window->display();
    sf::sleep(sf::seconds(3));
    window->close();

}

int main() {

    //обьявение всех нужных моделей

    std::vector<Level> levels = downloadLevels("/Users/andrey/Desktop/Tramp_Game/Game_Download/Dungeon/map.txt");

    Character character = downloadCharacter("/Users/andrey/Desktop/Tramp_Game/Game_Download/Entity/Character.txt");

    Enemy enemy = downloadEnemy("/Users/andrey/Desktop/Tramp_Game/Game_Download/Entity/BaseEnemy.txt");
    Enemy enemy1 = downloadEnemy("/Users/andrey/Desktop/Tramp_Game/Game_Download/Entity/DemonEnemy.txt");
    Enemy enemy2 = downloadEnemy("/Users/andrey/Desktop/Tramp_Game/Game_Download/Entity/KenkuEnemy.txt");
    Enemy enemy3 = downloadEnemy("/Users/andrey/Desktop/Tramp_Game/Game_Download/Entity/MinotaurEnemy.txt");
    Enemy enemy4 = downloadEnemy("/Users/andrey/Desktop/Tramp_Game/Game_Download/Entity/MinotaurEnemyB.txt");
    Enemy enemy6 = downloadEnemy("/Users/andrey/Desktop/Tramp_Game/Game_Download/Entity/MummyEnemy.txt");
    Enemy enemy5 = downloadEnemy("/Users/andrey/Desktop/Tramp_Game/Game_Download/Entity/VampireEnemy.txt");


    std::shared_ptr<IItem> regularEquipment = downloadEquipment("/Users/andrey/Desktop/Tramp_Game/Game_Download/Equipment/Armor.txt");
    enemy.setItem(regularEquipment);





    std::vector<Enemy> enemies = {enemy};
    std::vector<Enemy> enemies1 = {enemy1, enemy2};
    std::vector<Enemy> enemies2= {enemy3, enemy6};
    std::vector<Enemy> enemies3 = {enemy4, enemy5};
    std::vector<Enemy> enemies4 = {};



    
    Dungeon dungeon(character, levels);
    dungeon.getLevels()[0].addItem(regularEquipment);


    //создание view

    ViewEnemy viewEnemy;
    if (!viewEnemy.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Enemy/ogre_f.png", sf::Vector2u(64, 64), enemy))
        return -1;
    ViewEnemy viewEnemy1;
    if (!viewEnemy1.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Enemy/demonspawn_red_f.png", sf::Vector2u(64, 64), enemy1))
        return -1;
    ViewEnemy viewEnemy2;
    if (!viewEnemy2.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Enemy/kenku_winged_f.png", sf::Vector2u(64, 64), enemy2))
        return -1;
    ViewEnemy viewEnemy3;
    if (!viewEnemy3.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Enemy/minotaur_f.png", sf::Vector2u(64, 64), enemy3))
        return -1;
    ViewEnemy viewEnemy4;
    if (!viewEnemy4.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Enemy/minotaur_f.png", sf::Vector2u(64, 64), enemy4))
        return -1;
    ViewEnemy viewEnemy5;
    if (!viewEnemy5.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Enemy/mummy_m.png", sf::Vector2u(64, 64), enemy5))
        return -1;
    ViewEnemy viewEnemy6;
    if (!viewEnemy6.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Enemy/vampire_m.png", sf::Vector2u(64, 64), enemy6))
        return -1;



    ViewCharacter viewCharacter;
    if (!viewCharacter.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Entity/Character/character2.png", sf::Vector2u(64, 64),character))
        return -1;


    ViewLevel map;
    if (!map.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Dungeon/tileset64.png", sf::Vector2u(64, 64), dungeon.getLevels()[dungeon.getLevelNumber()]))
            return -1;

    ViewItem viewArmor;
    if (!viewArmor.load("/Users/andrey/Desktop/Tramp_Game/Game_Download/Sprites/Items/chunli.png", sf::Vector2u(64, 64),regularEquipment ))
        return -1;




    std::vector<ViewEnemy> vEnemies = {viewEnemy};
    std::vector<ViewEnemy> vEnemies1 = {viewEnemy1, viewEnemy2};
    std::vector<ViewEnemy> vEnemies2 = {viewEnemy3, viewEnemy6};
    std::vector<ViewEnemy> vEnemies3 = {viewEnemy4, viewEnemy5};
    std::vector<ViewEnemy> vEnemies4 = {};

    std::vector<ViewItem> vItems = {viewArmor};
    std::vector<ViewItem> vItems1 = {};
    std::vector<ViewItem> vItems2 = {};
    std::vector<ViewItem> vItems3 = {};
    std::vector<ViewItem> vItems4 = {};



    ViewEnemies viewEnemies;
    viewEnemies.load(sf::Vector2u(64, 64), vEnemies);
    ViewEnemies viewEnemies1;
    viewEnemies1.load(sf::Vector2u(64, 64), vEnemies1);
    ViewEnemies viewEnemies2;
    viewEnemies2.load(sf::Vector2u(64, 64), vEnemies2);
    ViewEnemies viewEnemies3;
    viewEnemies3.load(sf::Vector2u(64, 64), vEnemies3);
    ViewEnemies viewEnemies4;
    viewEnemies4.load(sf::Vector2u(64, 64), vEnemies4);

    
    
    ViewItems viewItems;
    viewItems.load(sf::Vector2u(64, 64), vItems);



    
    auto VE = std::make_shared<ViewEnemies>(viewEnemies);
    auto VE1 = std::make_shared<ViewEnemies>(viewEnemies1);
    auto VE2 = std::make_shared<ViewEnemies>(viewEnemies2);
    auto VE3 = std::make_shared<ViewEnemies>(viewEnemies3);
    auto VE4 = std::make_shared<ViewEnemies>(viewEnemies4);
    std::vector<std::shared_ptr<ViewEnemies>> dEnem= {VE, VE1, VE2, VE3, VE4};


    ViewItems dItem= {viewItems};



    
    std::vector<std::vector<Enemy>> MEnemies = {enemies, enemies1,enemies2,enemies3,enemies4};
    for(auto &Eenemy : MEnemies[0])
        dungeon.getLevels()[0].addEnemy(Eenemy);
    for(auto &Eenemy : MEnemies[1])
        dungeon.getLevels()[1].addEnemy(Eenemy);
    for(auto &Eenemy : MEnemies[2])
        dungeon.getLevels()[2].addEnemy(Eenemy);
    for(auto &Eenemy : MEnemies[3])
        dungeon.getLevels()[3].addEnemy(Eenemy);

    
    
    std::vector<std::shared_ptr<IItem>> MItems = {regularEquipment};




    DungeonView dungeonView(dEnem, MEnemies, dItem,MItems, sf::Vector2u(64, 64));






    map.updateCharacter(viewCharacter);

    if(!dungeonView.getMEnemies()[dungeon.getLevelNumber()].empty())
        map.updateEnemies(*(dungeonView.getVEnemies()[dungeon.getLevelNumber()]));


    if (!dungeon.getLevels()[dungeon.getLevelNumber()].getItems().empty())
        map.updateItems(dungeonView.getVItems());




    //sf::RenderWindow window(sf::VideoMode(512, 256), "TrampGame"); для другой картинки(изначальной)
    sf::RenderWindow window(sf::VideoMode(1024, 600), "TrampGame");
    ControllerCharacter CCharacter(dungeon);
    AIController AI(dungeon);



    while (window.isOpen())
    {
        if (dungeon.getLevelNumber() == dungeon.getLevels().size() - 1)
            endGame(&window, "/Users/andrey/Desktop/Tramp_Game/Game_Download/END_GAME/win.png");
        else if(!character.isLive())
            endGame(&window, "/Users/andrey/Desktop/Tramp_Game/Game_Download/END_GAME/lose.png");


        sf::Event event;

        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                CCharacter.handleInput(event);

                AI.move();

            }



        }
        //обновление VIEW
        viewCharacter.updateCharacter(CCharacter.getCharacter());

        if (!AI.getDungeon().getLevels()[dungeon.getLevelNumber()].getEnemies().empty())
            (*(dungeonView.getVEnemies()[dungeon.getLevelNumber()])).updateEnemies(AI.getDungeon().getLevels()[dungeon.getLevelNumber()].getEnemies());


        dungeonView.getVItems().updateItems();
        dungeonView.getVItems().updateItems(AI.getDungeon().getLevels()[dungeon.getLevelNumber()].getItems());


        //Обновление карты
        map.update(dungeon.getLevels()[dungeon.getLevelNumber()]);

        map.updateCharacter(viewCharacter);


        if (!AI.getDungeon().getLevels()[dungeon.getLevelNumber()].getEnemies().empty()){
            map.is_enemies = true;
            map.updateEnemies(*(dungeonView.getVEnemies()[dungeon.getLevelNumber()]));
        }else
            map.is_enemies = false;


        if (!AI.getDungeon().getLevels()[dungeon.getLevelNumber()].getItems().empty())
            map.updateItems(dungeonView.getVItems());



        window.clear();
        window.draw(map);
        window.display();
    }

    return 0;
}

