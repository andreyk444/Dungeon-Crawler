cmake_minimum_required(VERSION 3.16)
project(GameObject)

set(CMAKE_CXX_STANDARD 20)

#add_library(GameObject STATIC source/gameObject.cpp)
add_library(GameObject INTERFACE)
#target_include_directories(GameObject PUBLIC include)


target_include_directories(GameObject INTERFACE include)





