#!/bin/bash
# You will want to edit this file to point to the correct mount path.
# /mnt/loop /mnt/sda1 /mnt/hda1 /mnt/sr0 figure it out n00b.
#^^^^^haha thanx Demon child :P^^^^^^ that was based on a linux OS
#the way i have it set up below it  changes the regular win32 filepath to a POSIX path (/j/) with 
#-b, --binary     (default)    text files are equivalent to binary files
#/j/ is the drive letter of your psp the rest is expanitory.
#btw thanx Demon_child for this lol ;D
#Btw this is used inplace of psplink sence its a bitch and wont work on a PSP Slim with 5.00 m33-6 


make clean || { echo "Clean source as root"; exit 1; }
make || { echo "Error while building source"; exit 1; }
psp-packer DayPR.prx || { echo "Error while packing"; exit 1; } 
mount -b J:/ /j/  || { echo "Error while mounting psp"; exit 1; }
mv DayPR.prx /j/seplugins/DayPR.prx  || { echo "Directory does not exist, try mounting your psp first."; exit 1; } 
umount /j/ || { echo "Error while unmounting psp"; exit 1; } 
