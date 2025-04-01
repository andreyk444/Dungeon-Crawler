cmake_minimum_required(VERSION 3.16)
project(Controller)

set(CMAKE_CXX_STANDARD 20)

add_library(Controller STATIC source/Controller.cpp)
target_include_directories(Controller PUBLIC include)
target_link_libraries(Controller Utils GameObject Element Entity View )




