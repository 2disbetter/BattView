cmake_minimum_required(VERSION 3.5)
project(Battview)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(BattView main.cpp)
target_link_libraries(BattView Qt6::Widgets)