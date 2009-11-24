#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include "H/ctrl.h"
#include "H/Defines.h"

static unsigned int last_btn = 0;
static unsigned int last_tick = 0;
static unsigned int repeat_flag = 0;

extern unsigned int ctrl_read()
{
	SceCtrlData ctl;
	sceCtrlPeekBufferPositive(&ctl, 1);

	if (ctl.Buttons == last_btn)
	{
		if (ctl.TimeStamp - last_tick < (repeat_flag ? CTRL_REPEAT_INTERVAL : CTRL_REPEAT_TIME)) return 0;
		repeat_flag = 1;
		last_tick = ctl.TimeStamp;
		return last_btn;
	}
	repeat_flag = 0;
	last_btn  = ctl.Buttons;
	return last_btn;
}

extern void ctrl_waitrelease()
{
	SceCtrlData ctl;
	do {
		sceCtrlPeekBufferPositive(&ctl, 1);
		sceKernelDelayThread(20000);
	} while ((ctl.Buttons & 0xF0FFFF) != 0);
}

extern unsigned int ctrl_waitany()
{
	unsigned int key;
	while((key = (ctrl_read() & 0xF0FFFF)) == 0)
	{
		sceKernelDelayThread(20000);
	}
	return key;
}

extern unsigned int ctrl_waitkey(unsigned int keyw)
{
	unsigned int key;
	while((key = (ctrl_read() & keyw)) != keyw)
	{
		sceKernelDelayThread(20000);
	}
	return key;
}

extern unsigned int ctrl_waitmask(unsigned int keymask)
{
	unsigned int key;
	while((key = (ctrl_read() & keymask)) == 0)
	{
		sceKernelDelayThread(20000);
	}
	return key;
}

extern unsigned int ctrl_waittime(unsigned int t)
{
	int i = 0, m = t * 50;
	unsigned int key;
	while((key = (ctrl_read() & 0xF0FFFF)) == 0 && i < m)
	{
		sceKernelDelayThread(20000);
		++ i;
	}
	return key;
}

extern unsigned int ctrl_input()
{
	ctrl_waitrelease();
	SceCtrlData ctl;
	unsigned int key, key2;
	do {
		sceCtrlPeekBufferPositive(&ctl, 1);
		key = ctl.Buttons & 0xF0FFFF;
	} while(key == 0);
	key2 = key;
	while((key2 & key) == key)
	{
		sceKernelDelayThread(20000);
		key = key2;
		sceCtrlPeekBufferPositive(&ctl, 1);
		key2 = ctl.Buttons & 0xF0FFFF;
	}
	ctrl_waitrelease();
	return key;
}
