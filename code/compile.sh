#!/bin/bash

cd build
make
cp ../code "$EREBUS_DIRECTORY/game/controllers/robot0Controller/robot0Controller"