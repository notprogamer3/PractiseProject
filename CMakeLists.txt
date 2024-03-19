cmake_minimum_required(VERSION 3.27)
project(Practica2_QT)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 COMPONENTS Core REQUIRED)



add_executable(Practica2_QT main.cpp)
target_link_libraries(Practica2_QT Qt6::Core)