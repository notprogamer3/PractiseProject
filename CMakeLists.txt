cmake_minimum_required(VERSION 3.27)
project(Practica2_QT)

set(CMAKE_CXX_STANDARD 20)


find_package(Boost COMPONENTS system filesystem container REQUIRED)

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui UiTools Widgets)


qt_add_executable(Practica2_QT main.cpp
        src/MenuItem.cpp
        src/MenuItem.h
        src/Deposit.cpp
        src/Deposit.h
        src/Functions.cpp
        src/Functions.h
        src/SetupUi.h
        src/SetupUi.cpp
        src/SetupUi.h
)

target_link_libraries(Practica2_QT PUBLIC ${Boost_LIBRARIES}  Qt::Core
        Qt::Gui
        Qt::UiTools
        Qt::Widgets)