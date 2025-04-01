cmake_minimum_required(VERSION 3.16)
project(Dungeon)

set(CMAKE_CXX_STANDARD 20)

add_library(Dungeon STATIC source/dungeon.cpp)

target_include_directories(Dungeon PUBLIC include)

target_link_libraries(Dungeon Entity  GameObject Item Matrix)



