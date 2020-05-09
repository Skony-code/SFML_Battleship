cmake_minimum_required(VERSION 3.15)
project(SFML_Battleship)

set(CMAKE_CXX_STANDARD 17)

add_executable(SFML_Battleship main.cpp src/Model/Player.cpp src/Model/Player.h)

set(SFML_DIR "${CMAKE_CURRENT_LIST_DIR}/libs/SFML-2.5.1/lib/cmake/SFML")
file(GLOB ALL_REQUIRED_DLL "libs/required_dlls/*.dll")
file(COPY ${ALL_REQUIRED_DLL} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)