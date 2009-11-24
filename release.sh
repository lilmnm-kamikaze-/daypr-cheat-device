#!/bin/bash
make clean || { echo "Clean source as root"; exit 1; }
make || { echo "Error while building source"; exit 1; }
psp-packer DayPR.prx || { echo "Error while packing"; exit 1; }
mv DayPR.prx Release/OTHER/ || { mkdir Release/OTHER && move DayPR.prx Release/OTHER/DayPR.prx; exit 1; }

make clean || { echo "Clean source as root"; exit 1; }
make || { echo "Error while building source"; exit 1; }
psp-fixup-imports -m patches/map.txt DayPR.prx  || { echo "Error while patching, perhaps you've packed the prx before patching it?"; exit 1; }
psp-packer DayPR.prx || { echo "Error while packing"; exit 1; }
mv DayPR.prx Release/371/ || { mkdir Release/371 && move DayPR.prx Release/371/DayPR.prx; exit 1; }
