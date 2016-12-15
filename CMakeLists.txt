cmake_minimum_required(VERSION 3.6)
project(TPPOO2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Trajet.cpp TrajetSimple.cpp TrajetCompose.cpp Parcours.cpp Catalogue.cpp)
add_executable(TPPOO2 ${SOURCE_FILES})