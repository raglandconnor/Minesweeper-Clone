cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Minesweeper_Clone)

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
set(SFML_DIR "opt/homebrew")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio REQUIRED)
add_executable(Minesweeper_Clone main.cpp
        WelcomeWindow.cpp
        WelcomeWindow.h
        Board.cpp
        Board.h
        TextureManager.cpp
        TextureManager.h
        Tile.cpp
        Tile.h
        LeaderboardWindow.cpp
        LeaderboardWindow.h
)
target_link_libraries(Minesweeper_Clone sfml-system sfml-window sfml-graphics sfml-audio)