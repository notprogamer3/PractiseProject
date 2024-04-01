cmake_minimum_required(VERSION 3.27)
project(Practica2_QT)

set(CMAKE_CXX_STANDARD 20)


INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )


add_executable(Practica2_QT main.cpp
        src/MenuItem.cpp
        src/MenuItem.h
        src/Deposit.cpp
        src/Deposit.h
        src/Functions.cpp
        src/Functions.h
)

target_link_libraries(Practica2_QT ${Boost_LIBRARIES})