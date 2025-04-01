#ifndef Dungeon_h
#define Dungeon_h

#include "gameObject/GameObject.h"
#include "Item/Item.h"
#include <Entity/entity.h>
#include <vector>
#include <Matrix/matrix.hpp>


namespace Tramp {

    enum CellType: unsigned {
        WALL = 0,
        STAIRS_UP,
        STAIRS_DOWN,
        GAME_OBJECT,
        ENTITY

    };

    class DungeonCell{
    private:
        std::shared_ptr<std::mutex> mutex_;

        CellType cellType_;
        std::vector<std::shared_ptr<IGameObject>> gameObjects_;//без ссылки так как надо есть celltype
    public:
        std::mutex &getMutex(){return *mutex_;};

        DungeonCell();
        explicit DungeonCell(CellType);
        explicit DungeonCell(std::vector<std::shared_ptr<IGameObject>>);

        [[nodiscard]] CellType getCellType() const;
        [[nodiscard]] const  std::vector<std::shared_ptr<IGameObject>>& getGameObjects()const ;
        void changeCell(CellType);
        void addObject(std::shared_ptr<IGameObject> );
        void deleteObject(std::shared_ptr<IGameObject>);

    };



    class Level{
    private:
        Matrix<DungeonCell> playingField_;
        std::vector<Enemy > enemies_;
        std::vector<std::shared_ptr<IItem>> items_;


    public:
        Level() = delete;
        Level(Matrix<DungeonCell>&&);
        ~Level() = default;

        [[nodiscard]]  Matrix<DungeonCell>& getPlayingField() ;
        [[nodiscard]]  std::vector<Enemy >& getEnemies() ;
        [[nodiscard]]  std::vector<std::shared_ptr<IItem>>& getItems() {return items_;} ;

        void addEnemy(Enemy &enemy){
            enemies_.push_back(enemy);
            playingField_[enemy.getCoordinates().second][enemy.getCoordinates().first].changeCell(Tramp::ENTITY);
        }
        void addItem(std::shared_ptr<IItem> item){
            items_.push_back(item);
        }
         size_t deleteItem(std::shared_ptr<IItem> item){
            auto it = items_.begin();
            size_t index = 0;
            while (*(it) != item){
                ++it;
                index++;
                if (it != items_.end())
                    return -1;
            }

            items_.erase(it);
            return index;
        }

        void killEnemy(Enemy &enemy){
            auto it = enemies_.begin();
            while (it->getName() != enemy.getName()){
                ++it;
            }

            playingField_[enemy.getCoordinates().second][enemy.getCoordinates().first].changeCell(Tramp::GAME_OBJECT);
            if (it ->getItem()) {
                it->getItem()->updateCoordinates(it->getCoordinates());
                //playingField_[enemy.getCoordinates().second][enemy.getCoordinates().first].addObject(it->getItem());
                it->getItem()->changeVisible(true);

            }
           // items_.push_back(it->getItem());
            enemies_.erase(it);

        }

    };


    class Dungeon{
    private:
        friend Character;

        Character& character_;

        size_t levelNumber_;
        std::vector<Level>& levels_;


    public:


        Dungeon() = delete;
        Dungeon(Character&,   std::vector<Level>&);

        [[nodiscard]] Character& getCharacter() ;

        [[nodiscard]] size_t getLevelNumber() const;
        [[nodiscard]] std::vector<Level>& getLevels() ;
    };

}


#endif
