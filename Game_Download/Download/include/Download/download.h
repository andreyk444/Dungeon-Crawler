#include <iostream>
#include <SFML/Graphics.hpp>
#include <Matrix/matrix.hpp>
#include <fstream>
#include <string>
#include <Dungeon/Dungeon.h>
#include <View/View.h>
#include <Controller/Controller.h>

#ifndef DOWNLOAD
#define DOWNLOAD


std::vector<Level> downloadLevels(const std::string& filename);
Level downloadLevel(const std::string& filename);
Character downloadCharacter(const std::string& filename);
Enemy downloadEnemy(const std::string& filename);
std::shared_ptr<IItem> downloadEquipment(const std::string& filename);

#endif //DOWNLOAD
