cmake_minimum_required(VERSION 3.25)
project(Timber)

set(CMAKE_CXX_STANDARD 23)

set(SFML_INCLUDE_DIR "/usr/local/sfml/include")
set(SFML_LIBRARY_DIR "/usr/local/sfml/lib")
set(SFML_DIR "/usr/local/sfml/lib/cmake/SFML")

link_directories(SFML_LIBRARY_DIR)
include_directories(SFML_INCLUDE_DIR)

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio)

if(SFML_FOUND)
    message(STATUS "SFML_INCLUDE_DIR: ${SFML_INCLUDE_DIR}")
    message(STATUS "SFML_LIBRARIES: ${SFML_LIBRARIES}")
    message(STATUS "SFML_VERSION: ${SFML_VERSION}")
endif()

add_executable(Timber main.cpp)
target_link_libraries (Timber sfml-graphics sfml-window sfml-system)