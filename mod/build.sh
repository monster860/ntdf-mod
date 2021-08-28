#!/bin/bash
ee-g++ --save-temps -fno-exceptions -Os -G 0 -c mod.cpp
node ./make_mod.js
cd loader
ee-gcc *.c -I$(echo -n $PS2SDK)/ee/include -I$(echo -n $PS2SDK)/common/include -Os -G 0 -L$(echo -n $PS2SDK)/ee/lib -ldebug -lpad -Wl,-Ttext -Wl,0x1000000 -o ../df_hack.elf
cd ..