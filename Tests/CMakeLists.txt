cmake_minimum_required(VERSION 3.16)

project(Tests)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

if(UNIX)
     set(gtest_source_url https://github.com/google/googletest/archive/release-1.11.0.tar.gz)
elseif(WIN32)
    set(gtest_source_url https://github.com/google/googletest/archive/release-1.11.0.zip)
else()
    message(FATAL_ERROR "Операционная система не поддерживается")
endif()


include(FetchContent)
FetchContent_Declare(
  googletest
  URL ${gtest_source_url}    
)

FetchContent_MakeAvailable(googletest)

enable_testing()


add_executable (Tests   source/main.cpp
                        source/TestItem.cpp
                        source/TestElement.cpp
                        source/TestEntity.cpp
                        source/TestDungeon.cpp
                        Test_Matrix/TestMatrix.cpp
                        )

target_link_libraries(Tests	gtest
                           	gtest_main
                            Matrix
                            Element
                            Item
                            Entity
                            Dungeon

        )


