TARGET = DayPR
OBJS = C/DayPR.o C/exports.o C/module.o C/pspdebugkb.o C/snprintf.o C/extra_menus.o C/GUI.o C/blit.o C/ctrl.o C/config.o C/theme-color.o C/usb.o

# Define to build this as a prx (instead of a static elf)
BUILD_PRX=1
# Define the name of our custom exports (minus the .exp extension)
PRX_EXPORTS=C/exports.exp

USE_KERNEL_LIBS = 1
USE_KERNEL_LIBC = 1

INCDIR = 
CFLAGS = -O2 -G0 -w -Wall -msingle-float -g -fno-builtin-printf -DRELEASE -fno-strict-aliasing -fno-builtin-printf 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspchnnlsv -lpsputility -lpspdebug -lpspge_driver -lpspwlan -lpspumd -lpspctrl_driver -lpsppower \
       -lpsppower_driver -lpsppower_driver -lpspdisplay_driver -lpspusb_driver -lpspusbbus_driver \
	   -lpspusb -lpspusbstor
	   
LDFLAGS = -nostdlib  -nodefaultlibs -g

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak


