cmake_minimum_required(VERSION 3.16)
project(Download)

set(CMAKE_CXX_STANDARD 20)


add_library(Download STATIC source/Download.cpp)
target_include_directories(Download PUBLIC include)
target_link_libraries(Download Utils Dungeon Element Entity Item Controller View)

target_link_libraries(Download sfml-graphics sfml-audio)





