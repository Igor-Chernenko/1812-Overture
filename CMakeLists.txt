cmake_minimum_required(VERSION 3.10)
project(1812-Overture)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(1812-Overture main.cpp window.cpp window.hpp)
target_link_libraries(1812-Overture sfml-graphics sfml-window sfml-system)
