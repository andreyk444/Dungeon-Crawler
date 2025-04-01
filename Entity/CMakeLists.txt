cmake_minimum_required(VERSION 3.16)
project(Entity)

set(CMAKE_CXX_STANDARD 20)

add_library(Entity STATIC source/entity.cpp)

target_include_directories(Entity PUBLIC include)

target_link_libraries(Entity Utils Item GameObject Dungeon )



