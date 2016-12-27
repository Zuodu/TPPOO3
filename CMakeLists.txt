cmake_minimum_required(VERSION 3.6)
project(TPPOO3)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES main.cpp Trajet.cpp TrajetSimple.cpp TrajetCompose.cpp Parcours.cpp Catalogue.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DWINDOWS)
add_executable(TPPOO3 ${SOURCE_FILES})