#!/bin/bash

cd build
export WEBOTS_HOME=/usr/local/webots
make

FILE=../code
if test -f "$FILE"; then
    mv ../code ../code.out
fi

cp ../code.out "$EREBUS_DIRECTORY/game/controllers/robot0Controller/robot0Controller"
