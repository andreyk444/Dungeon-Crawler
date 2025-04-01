cmake_minimum_required(VERSION 3.16)
project(View)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)

add_library(View STATIC source/View.cpp)
target_include_directories(View PUBLIC include)
target_link_libraries(View Utils GameObject Element Entity )

target_link_libraries(View sfml-graphics sfml-audio)




