#!/bin/bash

cd build
make

cd ..

FILE=./simulated_rescue_maze
if test -f "$FILE"; then
    mv ./simulated_rescue_maze ./simulated_rescue_maze.out
fi

cp ./simulated_rescue_maze.out "$EREBUS_DIRECTORY/game/controllers/robot0Controller/robot0Controller"