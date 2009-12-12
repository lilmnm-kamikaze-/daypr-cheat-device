TARGET = Installer 
#name of the elf and prx
OBJS = Installer.o 
#files that will be added into the eboot, prx

INCDIR = 
# the director for the used libs if you are useing some not in the SDK
CFLAGS = -O2 -G0 -Wall 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)
#build flags and some time builind defins

BUILD_PRX = 1
#builds a prx
EXTRA_TARGETS = EBOOT.PBP
#make it build a EBOOT.PBP
PSP_EBOOT_TITLE = DayPR Installer
#name of the eboot and prx if its used into a UMD
#PSP_EBOOT_ICON = name_of_image.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
#SDK stuff leave it alone!