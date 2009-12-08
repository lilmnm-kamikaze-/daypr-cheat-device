TARGET = Installer
OBJS = Installer.o 

INCDIR = 
CFLAGS = -O2 -G0 -Wall 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = DayPR Installer
#PSP_EBOOT_ICON = ebootdata/bakonice.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
