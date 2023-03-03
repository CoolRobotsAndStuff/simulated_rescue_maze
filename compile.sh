#!/bin/bash

cd build
make

cd ..

FILE=./code
if test -f "$FILE"; then
    mv ./code ./code.out
fi

cp ./code.out "$EREBUS_DIRECTORY/game/controllers/robot0Controller/robot0Controller"