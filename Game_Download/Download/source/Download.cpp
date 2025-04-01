#include "Download/download.h"

using namespace Tramp;


std::vector<Level> downloadLevels(const std::string& filename){
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        throw std::runtime_error("FILE NOT OPENED");
    }

    size_t numberLevels;
    inputFile >> numberLevels;

    std::vector<Level> levels;

    for (size_t k = 0; k < numberLevels; k++) {


        size_t rows, column;
        inputFile >> rows >> column;

        Matrix<DungeonCell> playField(rows, column);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < column; j++) {
                size_t cellType;
                inputFile >> cellType;

                playField[i][j] = DungeonCell(static_cast<CellType>(cellType));
            }
        }

        Level level(std::move(playField));
        levels.push_back(level);

    }

    return levels;
}
Level downloadLevel(const std::string& filename){
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        throw std::runtime_error("FILE NOT OPENED");
    }

    size_t rows, column;
    inputFile >> rows >> column;

    Matrix<DungeonCell> playField(rows, column);
    for (size_t i = 0; i < rows; i++){
        for (size_t j = 0; j < column; j++){
            size_t cellType;
            inputFile >> cellType;

            playField[i][j] = DungeonCell(static_cast<CellType>(cellType));
        }
    }

    return Level(std::move(playField));
}

Character downloadCharacter(const std::string& filename){
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        throw std::runtime_error("FILE NOT OPENED");
    }

    size_t maxItems;
    inputFile >> maxItems;
    std::array<size_t, CharacteristicType::CHARACTERISTICHS_TYPE_SIZE> table{};
    for (size_t i = 0 ; i < 5; i++){
        inputFile >> table[i];
    }

    return Character(table, maxItems);

}

std::shared_ptr<IItem> downloadEquipment(const std::string& filename){
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        throw std::runtime_error("FILE NOT OPENED");
    }

    char  cType;
    size_t defence;
    std::pair<size_t, size_t> coordinates;
    inputFile >> cType >> defence >> coordinates.first >> coordinates.second;

    return std::make_shared<RegularEquipment>(RegularEquipment(static_cast<EquipmentType>(cType - 48), defence, coordinates));

}

Enemy downloadEnemy(const std::string& filename){
    std::ifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::cerr << "Unable to open the file: " << filename << std::endl;
        throw std::runtime_error("FILE NOT OPENED");
    }

    std::string name;
    size_t  maxHealth,  damage, defence, experience;
    std::pair<size_t, size_t> coordinates;
    inputFile >> name >> maxHealth >> damage >> defence >> experience >> coordinates.first >> coordinates.second;



    return Enemy(name, maxHealth,  damage, defence, experience,coordinates, nullptr);
}

