#ifndef GNAME_H
#define GNAME_H

#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspumd.h>
#include <stdio.h>
#include <stdlib.h>
#include <psppower.h>
#include "H/theme-color.h"
#include "H/config.h"
#include "H/ctrl.h"
#include "H/GUI.h"
#include "H/Defines.h"

char vert[10]={0xBA};

static char ui_gname[12 + 0x81];
static int ui_hex_mode = 0;

extern void ui_init()
{
	int i, fd;
	ui_hex_mode = 0;
	memset(ui_gname, ' ', 12);
	ui_gname[12] = 0;
	for (i = 0; i < 10; i ++)
	{
		fd = sceIoOpen(UMD_DATA, PSP_O_RDONLY, 0777);
		if (fd >= 0)
			break;
		sceKernelDelayThread(1000000);
	}
	if (fd >= 0)
	{
		sceIoRead(fd, ui_gname, 11);
		sceIoClose(fd);
	}
	for (i = 0; i < 10; i ++)
	{
		fd = sceIoOpen(PARAM_SFO, PSP_O_RDONLY, 0777);
		if (fd >= 0)
			break;
		sceKernelDelayThread(1000000);
	}
	if (fd >= 0)
	{
		sceIoLseek32(fd, 0x158, SEEK_SET);
		sceIoRead(fd, &ui_gname[12], 0x80);
		ui_gname[12 + 0x80] = 0;
		int i;
		for(i = 12; i < 12 + 0x80; i ++)
		{
			if(ui_gname[i] == 0)
				break;
			if(ui_gname[i] < 0)
				ui_gname[i] = '_';
		}
		sceIoClose(fd);
	}
}

extern void ui_cls()
{
	pspDebugScreenPuts(vert);pspDebugScreenPuts(AUTHOR_S NAME_PR VER_STR VER_SFX); pspDebugScreenPuts(NEWLINE);
	pspDebugScreenPuts(vert);pspDebugScreenPuts(Playing_Game);pspDebugScreenPuts(ui_gname); pspDebugScreenPuts(NEWLINE);
	//char cpu[17];
	//sprintf(cpu, "CPU/BUS: %d/%d", scePowerGetCpuClockFrequency(), scePowerGetBusClockFrequency());
	//pspDebugScreenPuts(vert);pspDebugScreenPuts(cpustr);pspDebugScreenPuts("\n");
}

#endif
