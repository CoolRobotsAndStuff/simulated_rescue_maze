#!/bin/bash

cd build
make

FILE=../code
if test -f "$FILE"; then
    mv ../robot0Controllers ../robot0Controller.out
fi

cp ../code.out "/home/joaquin/Documents/RCJ2023-SimulatedRescueMaze/Erebus-v21_2_4/game/controllers/robot0Controller"
