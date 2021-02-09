## Building

You need the following:
- PS2 toolchain, [found here](https://github.com/ps2dev/ps2toolchain). This will require a linux environment. If you are on windows you may use Windows Subsystem for Linux
- Node.JS
- A copy of the `SCUS_973.67` file found on the game disk. This file must be placed in the mod folder of this repository

To build, use the `build.sh` shell script. This will create two files. `934F9081.pnach`, and `df_hack.elf`.

To run this mod on emulator, you place the .pnach file in the cheats folder, and enable cheats.

To run this mod on console, you will need some way of running elf files, such as a FreeMCBoot card. Simply run the df_hack.elf file, with the disk inserted into the PS2
