#include <Dungeon/Dungeon.h>

#include <utility>


namespace Tramp {


    DungeonCell::DungeonCell(CellType cellType ):cellType_{cellType}  {mutex_ = std::make_shared<std::mutex>();}

    DungeonCell::DungeonCell(std::vector<std::shared_ptr<IGameObject>> gameObjects):cellType_{GAME_OBJECT}   {
        gameObjects_ =  std::move(gameObjects);
        mutex_ = std::make_shared<std::mutex>();
    }

    CellType DungeonCell::getCellType() const {return cellType_;}

    const std::vector<std::shared_ptr<IGameObject>>& DungeonCell::getGameObjects() const {

        return gameObjects_;
    }

    DungeonCell::DungeonCell(): cellType_(GAME_OBJECT) {mutex_ = std::make_shared<std::mutex>();}

//    void Level::changeCell(CellType type, size_t row, size_t column) {
//        if (playingField_.at(row, column).cellType_ != GAME_OBJECT){
//            playingField_.at(row, column).gameObjects_.clear();
//        }
//        playingField_.at(row, column).cellType_ = type;
//    }

    void DungeonCell::addObject(std::shared_ptr<IGameObject> obj) {
        gameObjects_.push_back(obj);//
    }

    void DungeonCell::deleteObject(std::shared_ptr<IGameObject> obj) {
        auto it = gameObjects_.begin();
        while (it != gameObjects_.end()){//change check
            if ((*(*it)).getName() == (*obj).getName()){
                break;
            }
            ++it;
        }

        if (it != gameObjects_.end()){
            gameObjects_.erase(it);
        }
    }

    void DungeonCell::changeCell(CellType type) {
        if (type != GAME_OBJECT){
            gameObjects_.clear();
        }

        cellType_= type;
    }

    Level::Level(Matrix<Tramp::DungeonCell> && playingField){ //character_{character}{//, Tramp::Character &character
        playingField_ = std::move(playingField);

    }

    Matrix<DungeonCell>& Level::getPlayingField(){return playingField_;}

    std::vector<Enemy> &Level::getEnemies()  {
        return enemies_;
    }




    Dungeon::Dungeon(Tramp::Character& character,  std::vector<Level>& levels)://std::vector<Enemy>  enemyies,
        character_{character}, levelNumber_{0}, levels_{levels} {
 //       enemies_ = std::move(enemyies);
//        levels_ = std::move(levels);
}


    Character& Dungeon::getCharacter() {return character_;}

   // const std::vector<Enemy>& Dungeon::getEnemies() const {return enemies_;}

    size_t Dungeon::getLevelNumber() const {return levelNumber_;}

    std::vector<Level>& Dungeon::getLevels() {return levels_;}



}