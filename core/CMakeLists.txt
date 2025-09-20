cmake_minimum_required(VERSION 3.16)
project(devos_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find the ncurses library (aliased as Curses)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Source files for the static library
add_library(devos_core STATIC
    src/dungeon.cpp
    src/player.cpp
    src/generator.cpp
)

target_include_directories(devos_core PUBLIC include)

# Demo executable
add_executable(devos_demo src/main.cpp)

# Link the executable against our library and the ncurses library
target_link_libraries(devos_demo PRIVATE devos_core ${CURSES_LIBRARY})
