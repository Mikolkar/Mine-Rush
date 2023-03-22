#!/bin/bash
if [ "$1" = "" ]; then
    cd src/
    ./sdl2_game
elif [ "$1" = "-t-e" ]; then
    cd src/
    ./mine_terminal easy
elif [ "$1" = "-t-m" ]; then
    cd src/
    ./mine_terminal medium
elif [ "$1" = "-t-h" ]; then
    cd src/
    ./mine_terminal hard
elif [ "$1" = "-t-h" ]; then
    cd src/
    ./mine_terminal hard
elif [ "$1" = "remove-makefiles" ]; then
    cd build/
    rm -r cmake_install.cmake
    rm CMakeCache.txt
    rm CPackConfig.cmake
    rm CPackSourceConfig.cmake
    rm -R CMakeFiles/
elif [ "$1" = "build-makefiles" ]; then
    cd build/
    make
else
    echo "Niepoprawne argumenty."
fi