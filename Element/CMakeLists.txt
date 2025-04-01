cmake_minimum_required(VERSION 3.16)
project(Element)

set(CMAKE_CXX_STANDARD 20)

add_library(Element STATIC source/element.cpp)

target_include_directories(Element PUBLIC include)





