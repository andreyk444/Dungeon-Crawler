cmake_minimum_required(VERSION 3.23)
project(Tramp_C__)

set(CMAKE_CXX_STANDARD 20)


#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)

add_compile_options(-fsanitize=thread -g)
add_link_options(-fsanitize=thread)

find_package(SFML 2.6 COMPONENTS graphics audio REQUIRED)
add_executable( main main.cpp)

add_subdirectory(Utils)
add_subdirectory(Matrix)
add_subdirectory(GameObject)
add_subdirectory(Element)
add_subdirectory(Item)
add_subdirectory(Entity)
add_subdirectory(Dungeon)
add_subdirectory(View)
add_subdirectory(Controller)
#add_subdirectory(Tests)
add_subdirectory(Game_Download/Download)

target_link_libraries(main Matrix Dungeon View Controller sfml-graphics sfml-audio Download)
