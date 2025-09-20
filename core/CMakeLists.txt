cmake_minimum_required(VERSION 3.16)
project(devos_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
add_library(devos_core STATIC
    src/dungeon.cpp
    src/player.cpp
)

target_include_directories(devos_core PUBLIC include)

# Demo executable
add_executable(devos_demo src/main.cpp)
target_link_libraries(devos_demo PRIVATE devos_core)
