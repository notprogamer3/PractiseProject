



set(CMAKE_CXX_STANDARD 20)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)

find_package(Qt6 REQUIRED COMPONENTS Core Gui UiTools Widgets Test)
include_directories (${Boost_INCLUDE_DIRS})
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

enable_testing(true)


add_executable (Boost_Tests_run Deposits_test.cpp "../src/Deposit.h" "../src/Deposit.cpp")
target_link_libraries (Boost_Tests_run ${Boost_LIBRARIES} Qt::Core
        Qt::Gui
        Qt::UiTools
        Qt::Widgets
        Qt::Test)