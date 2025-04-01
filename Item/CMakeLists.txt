cmake_minimum_required(VERSION 3.16)
project(Item)

set(CMAKE_CXX_STANDARD 20)

add_library(Item STATIC source/item.cpp)
target_include_directories(Item PUBLIC include)
target_link_libraries(Item Utils GameObject Element Entity )




