#!/bin/bash

cd build
make

FILE=../code
if test -f "$FILE"; then
    mv ../code ../code.out
fi

cp ../code.out "$EREBUS_DIRECTORY/game/controllers/robot0Controller/robot0Controller"
