

#ifndef TRAMP_C___CONTROLLER_H
#define TRAMP_C___CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <Dungeon/Dungeon.h>
#include <View/View.h>
#include <thread>
#include <utility>

class ControllerCharacter{
private:
//    Character& character_;//у нас же герой есть в  dungeon
//    ViewCharacter& Vcharacter_;//не используем
    //Dungeon dungeon_;
    Dungeon& dungeon_;

    int attack(std::pair<size_t, size_t> coordinates) {
        Level &level = dungeon_.getLevels()[dungeon_.getLevelNumber()];
        Character &character_ = getCharacter();

        size_t index = 0;
        while (level.getEnemies()[index].getCoordinates() != coordinates) {
            ++index;

            if (index >= level.getEnemies().size())
                return -1;
        }

        level.getEnemies()[index].getHit(character_.getDamage(std::make_shared<Enemy>(level.getEnemies()[index])));


        if (!((level.getEnemies()[index]).isLive())){
            level.killEnemy((level.getEnemies()[index]));
            return index;
        }
        else
            character_.getHit((level.getEnemies()[index]).getDamage());

        return -1;

        //enemy.getHit(character_.getDamage());
    }
public:
    ControllerCharacter(Dungeon& d): dungeon_(d){}//Character& ch, ViewCharacter& vc, character_(ch), Vcharacter_(vc),

    void handleInput(sf::Event event){
        if (event.type == sf::Event::KeyPressed) {
            Character& character_ = getCharacter();
            if (event.key.code == sf::Keyboard::Up) {
                if (!character_.move(UP, dungeon_)) {
                    attack(std::pair{character_.getCoordinates().first , character_.getCoordinates().second - 1});

//
                }
            } else if (event.key.code == sf::Keyboard::Down) {
                if (!character_.move(DOWN, dungeon_)) {
                    attack(std::pair{character_.getCoordinates().first , character_.getCoordinates().second + 1});


                }
            }else if (event.key.code == sf::Keyboard::Left) {
                if (!character_.move(LEFT, dungeon_)){
                    attack(std::pair{character_.getCoordinates().first - 1 , character_.getCoordinates().second });


                }
            }else if (event.key.code == sf::Keyboard::Right) {
               if(!character_.move(RIGHT, dungeon_)){
                      attack(std::pair{character_.getCoordinates().first + 1 , character_.getCoordinates().second});

               }
             }else if(event.key.code == sf::Keyboard::E) {
                std::vector<std::shared_ptr<IItem>>& items= dungeon_.getLevels()[dungeon_.getLevelNumber()].getItems();
                if (items.empty()) return;

                auto it = items.begin();
                auto equipable =  std::dynamic_pointer_cast<IEquipable>(*it);

                while (equipable){
                    if (equipable->getCoordinates() == character_.getCoordinates()){
                        break;
                    }

                    ++it;
                    if(it == items.end()) return;

                    equipable =  std::dynamic_pointer_cast<IEquipable>(*it);

                }

                character_.equip(equipable);
                dungeon_.getLevels()[dungeon_.getLevelNumber()].getPlayingField()[character_.getCoordinates().second][character_.getCoordinates().first].deleteObject(equipable);
            }

        }
    }


    [[nodiscard]]  Character &getCharacter()  {return dungeon_.getCharacter();}

};

class AIController{
private:
    //std::vector<std::vector<Enemy>>& enemies_;

    Dungeon& dungeon_;
//    Character& character_;
    //возможно тут нужен будет масссив спрайтов врагов чтобы мы могли понимать какой из врагов сдох


public:
    AIController( Dungeon& d):  dungeon_(d){}

    [[nodiscard]] Character getCharacter()  {return dungeon_.getCharacter();}
    [[nodiscard]] Dungeon& getDungeon() {return dungeon_;}


    template<typename ItIn>
    void moveT(
            ItIn first, ItIn last)
    {
        while (first != last) {

            const std::pair<size_t, size_t> characterCoordinates = dungeon_.getCharacter().getCoordinates();

            first->moveTo(dungeon_, characterCoordinates);

            ++first;
        }
    }

    template<typename ItIn>
    void move_mt(
            ItIn first, ItIn last)
    {
        auto threadNum =
                std::thread::hardware_concurrency();


        auto elements = std::distance(first, last);

        threadNum = std::min<unsigned int>(threadNum, elements);

        std::vector<std::thread> threads(threadNum);



        for (size_t i = 0; i < threadNum; ++i) {
            size_t start_i = i * elements / threadNum;
            size_t end_i = (i + 1) * elements / threadNum;

            auto start = std::next(first, start_i);
            auto end = std::next(first, end_i);



            threads[i] = std::thread(
                    [=](){moveT(start, end);});
        }

        for(auto& th : threads) {
            th.join();
        }
    }
    void move() {

        Character character = getCharacter();
        std::vector<Enemy> &enemies = dungeon_.getLevels()[dungeon_.getLevelNumber()].getEnemies();



        move_mt(enemies.begin(), enemies.end());
        }





//
//        auto nThreads =
//                std::thread::hardware_concurrency();
//        std::vector<std::thread> threads(nThreads);
//
//        auto first = threads.begin();
//        auto last =threads.end();
//        auto elements = std::distance(first, last);

//        auto moveEnemyFunction = [this](Enemy& enemy, Dungeon& dungeon) {
//            const std::pair<size_t, size_t> characterCoordinates = getCharacter().getCoordinates();
//
//            enemy.moveTo(dungeon, characterCoordinates);
//        };

//        auto transformLambda = [&](auto first, auto last, auto first_out, auto func) {
//            std::transform(first, last, first_out, func);
//        };
//
//
//        for (size_t i = 0; i < nThreads; ++i){
//            size_t start_i = i * elements / nThreads;
//            size_t end_i = (i + 1) * elements / nThreads;
//
//            auto start = std::next(first, start_i);
//            auto end = std::next(first, end_i);
//
//            auto res_start = std::next(first, start_i);
//
//            threads[i] = std::thread(transformLambda,first, last, res_start, std::ref(moveEnemyFunction), std::ref(enemies[i]), std::ref(dungeon_));
//
//        }



//        for (std::thread& thread : threads) {
//            if (thread.joinable())
//                thread.join();
//        }
//    }
//



};



#endif //TRAMP_C___CONTROLLER_H


//Character character = getCharacter();
//std::vector<Enemy>& enemies = dungeon_.getLevels()[dungeon_.getLevelNumber()].getEnemies();
//
//size_t i = 0;
//for (Enemy& enemy : enemies) {//forEach
////            лекции
////40 врагов 5 потоков по 8 врагов в каждом использовать foreach
////std::for_each(std::execution::par_unseq,
////               from.begin(), from.end(), func);
//threads.emplace(threads.begin() + i, moveEnemyFunction, std::ref(enemy), std::ref(dungeon_));
//
////            if (size() == nThreads)
//}



//void move() {
//    std::vector<std::thread> threads;
//    std::mutex mutex;
//
//    auto moveEnemyFunction = [this, &mutex](Enemy& enemy, Dungeon& dungeon, const std::pair<size_t, size_t>& characterCoordinates) {
//        std::lock_guard<std::mutex> lock(mutex);
//        enemy.moveTo(dungeon, characterCoordinates);
//    };
//
//    Character character = getCharacter();
//    std::vector<Enemy>& enemies = dungeon_.getLevels()[dungeon_.getLevelNumber()].getEnemies();
//
//    for (Enemy& enemy : enemies) {
//        threads.emplace_back(moveEnemyFunction, std::ref(enemy), std::ref(dungeon_), std::cref(character.getCoordinates()));
//    }
//
//
//    for (std::thread& thread : threads) {
//        thread.join();
//    }
//}


//
//auto moveEnemyFunction = [this](Enemy& enemy, Dungeon& dungeon) {
//    const std::pair<size_t, size_t> characterCoordinates = getCharacter().getCoordinates();
//
//    enemy.moveTo(dungeon, characterCoordinates);
//};
//
//Character character = getCharacter();
//std::vector<Enemy>& enemies = dungeon_.getLevels()[dungeon_.getLevelNumber()].getEnemies();
//
//size_t i = 0;
//for (Enemy& enemy : enemies) {//forEach
////            лекции
////40 врагов 5 потоков по 8 врагов в каждом использовать foreach
////std::for_each(std::execution::par_unseq,
////               from.begin(), from.end(), func);
//threads.emplace(threads.begin() + i, moveEnemyFunction, std::ref(enemy), std::ref(dungeon_));
//
////            if (size() == nThreads)
//}

//    void move(){
//        Character character_ = getCharacter();
//        for(Enemy & enemy: dungeon_.getLevels()[dungeon_.getLevelNumber()].getEnemies())//enemies_[dungeon_.getLevelNumber()]
//            enemy.moveTo(dungeon_, character_.getCoordinates());
//
//    }
//