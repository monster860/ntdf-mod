#!/bin/sh
ee-g++ --save-temps -fno-exceptions -Os -G 0 -c mod.cpp
node ./make_mod.js
