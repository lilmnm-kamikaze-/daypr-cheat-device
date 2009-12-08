#include <pspkernel.h>
#include <pspiofilemgr.h>
#include <stdio.h>
#include <stdlib.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>
#include <pspdisplay.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Files/DAYPR.h"
#include "Files/DAYPR371.h"

PSP_MODULE_INFO("DayPR Installer", 0, 1, 1);

#define printf pspDebugScreenPrintf
#define lineClear(a_line) pspDebugScreenSetXY(0, a_line); pspDebugScreenPuts("                                                                   "); pspDebugScreenSetXY(0, a_line);
#define Text pspDebugScreenPuts
#define TextColor pspDebugScreenSetTextColor
#define SetXY pspDebugScreenSetXY
#define Install_Version " DayPR Rev.6 -- Beta Installer\n"

SceCtrlData pad;
unsigned int counter;
unsigned int YesNo_Choice;
unsigned char cheatButtonY=0;
unsigned int Install_Choice=0;


/* Exit callback */
int exit_callback(int arg1, int arg2, void *common) {
          sceKernelExitGame();
          return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp) {
          int cbid;

          cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
          sceKernelRegisterExitCallback(cbid);

          sceKernelSleepThreadCB();

          return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void) {
          int thid = 0;

          thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
          if(thid >= 0) {
                    sceKernelStartThread(thid, 0, 0);
          }

          return thid;
} 

void PrintTextColor(int color, const char *txt)
	{
		TextColor(color);
		Text(txt);
	}

void PrintTextColorXY(int x, int y, int color, const char *txt)
	{
		SetXY(x, y);
		TextColor(color);
		Text(txt);
	}

void ClearLineTextColorY(int y, int color, const char *txt)
	{
		lineClear(y);
		TextColor(color);
		Text(txt);
	}

void print_title()
{
        PrintTextColorXY(0, 1, 0xFF0000FF, Install_Version);
		SetXY(0, 3);
        return;
}

void Install_Init()
{ 	
	pspDebugScreenClear();
	print_title();
	PrintTextColorXY(0, 3, 0xFF0000FF, "     Creating folders: ");
	PrintTextColorXY(0, 4, 0xFF0000FF, "     Creating folders ms0:/seplugins/DayPR ");
	sceIoMkdir("ms0:/seplugins/DayPR", 0777);
	sceKernelDelayThread(1000000);
	PrintTextColor(0xFF0000FF, "  DONE!!");
	sceKernelDelayThread(500000);
	PrintTextColorXY(0, 5, 0xFF0000FF, "     Creating folders ms0:/seplugins/DayPR/dumps ");
	sceIoMkdir("ms0:/seplugins/DayPR/dumps", 0777);
	sceKernelDelayThread(1000000);
	PrintTextColor(0xFF0000FF, "  DONE!!");
	sceKernelDelayThread(500000);
	PrintTextColorXY(0, 6, 0xFF0000FF, "     Creating folders ms0:/seplugins/DayPR/search ");
	sceIoMkdir("ms0:/seplugins/DayPR/search", 0777);
	sceKernelDelayThread(1000000);
	PrintTextColor(0xFF0000FF, "  DONE!!");
	sceKernelDelayThread(1000000);
}

int writeFile(char path[], unsigned char buffer[], unsigned int size_buffer)
{
	signed int fd;
	
	fd = sceIoOpen(path, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777);
	sceIoWrite(fd, buffer, size_buffer);
	sceIoClose(fd);
	
	fd=sceIoOpen(path, PSP_O_RDONLY, 0777);
	if(fd > 0)
	{
		sceIoClose(fd);
		sceKernelDelayThread(1500000);
		return 1;
	}
	else
	{
		sceIoClose(fd);
		sceKernelDelayThread(1500000);
		return 0;
	}
	
}

void ExitIn10()
	{
		pspDebugScreenClear();
		print_title();
		int counter; 
			for(counter = 10; counter > 0; counter--)
				{	
					print_title();
					printf("  Thank you, exiting in %d", counter);
					sceKernelDelayThread(200000);
				}
			sceKernelExitGame();
	}


void gametxt_enabled()
{
	char *txtline = "ms0:/seplugins/%s.prx 1\n";
	char txtdata[100];
	sprintf(txtdata, txtline, "DayPR");
	signed int fd0 = sceIoOpen("ms0:/seplugins/game.txt", PSP_O_WRONLY | PSP_O_CREAT, 0777);
	sceIoLseek(fd0, 0, 2);
	sceIoWrite(fd0, txtdata, strlen(txtdata));
	sceIoClose(fd0);
	PrintTextColorXY(0, 9, 0xFF0000FF, "  Writing DayPR enabled to Game.txt...\n");
	sceKernelDelayThread(200000);
	ClearLineTextColorY(9, 0xFF0000FF, "  Done!\n");
	return;
}

void gametxt_disabled()
{
	char *txtline = "\nms0:/seplugins/%s.prx 0\n";
	char txtdata[100];
	sprintf(txtdata, txtline, "DayPR");
	signed int fd0 = sceIoOpen("ms0:/seplugins/game.txt", PSP_O_WRONLY | PSP_O_CREAT, 0777);
	sceIoLseek(fd0, 0, 2);
	sceIoWrite(fd0, txtdata, strlen(txtdata));
	sceIoClose(fd0);
	PrintTextColorXY(0, 9, 0xFF0000FF, "  Writing DayPR disabled to Game.txt...\n");
	sceKernelDelayThread(200000);
	ClearLineTextColorY(9, 0xFF0000FF, "  Done!\n");
	return;
}

/*
void Yes_No()
	{
		PrintTextColorXY(0, 5, 0xFF0000FF, "  Would you like to write DayPR to GAME.txt?\n\n");
		counter=0;
        while(counter < 3)
        {
          if(YesNo_Choice == counter)
          {
            //Highlight the selection
          	TextColor(0xFF0000FF);
          }
          else
          {
            //Don't highlight the selection
            TextColor(0xFFA9A9A9);
          }
          switch(counter)
          {
            case 0: Text("     Yes Enabled\n");break;
			case 1: Text("     Yes Disabled\n");break;
			case 2: Text("     No, Exit\n");break;
		  }
          counter++;
        }
		
		lineClear(31);
        switch(YesNo_Choice)
        {
          case 0: PrintTextColor(0xFF0000FF, " Yes and have it as Enabled"); break;
          case 1: PrintTextColor(0xFF0000FF, " Yes and have it as Disabled"); break;
		  case 2: PrintTextColor(0xFF0000FF, " No And exits the installer"); break;
		}
		
		if(pad.Buttons & PSP_CTRL_UP)
			{
				if(YesNo_Choice > 0)
					{
						YesNo_Choice--;
					}
				else if(YesNo_Choice == 0)
					{
						YesNo_Choice=2;
                    }
				if(cheatButtonY < 12) cheatButtonY++; sceKernelDelayThread(150000-(10000*cheatButtonY));
			}
        else if(pad.Buttons & PSP_CTRL_DOWN)
            {
				if(YesNo_Choice < 2)
					{
						YesNo_Choice++;
					}
				else if(YesNo_Choice == 2)
					{
						YesNo_Choice=0;
					}
					if(cheatButtonY < 12) cheatButtonY++; sceKernelDelayThread(150000-(10000*cheatButtonY));
			}
        else
            {
				cheatButtonY=0;
            }
			
		if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(YesNo_Choice == 0)
					{
						gametxt_enabled();
					}
		
				else if(YesNo_Choice == 1)
					{
						gametxt_disabled();
					}
		
				else if(YesNo_Choice == 2)
					{
						ExitIn10();
					}
			}
	}
*/
	
void Install_DayPR()
	{
		pspDebugScreenClear();
		print_title();
		PrintTextColorXY(0, 7, 0xFF0000FF, "  Installing DayPR.prx to ms0:/seplugins/...");
		writeFile("ms0:/seplugins/DayPR.prx", DayPR, size_DayPR);
		ClearLineTextColorY(7, 0xFF0000FF, " Done!\n");
		sceKernelDelayThread(1500000);
		//Yes_No();
	}

void Install_DayPR371()
	{
		pspDebugScreenClear();
		print_title();
		PrintTextColorXY(0, 7, 0xFF0000FF, "  Installing DayPR.prx to ms0:/seplugins/...");
		writeFile("ms0:/seplugins/DayPR.prx", DayPR371, size_DayPR371);
		ClearLineTextColorY(7, 0xFF0000FF, " Done!\n");
		sceKernelDelayThread(1500000);
		//Yes_No();	 menu is buggy to lazy to fix it right now =P
	}
	
void Install()
{ 
  while(1)
    {
		sceCtrlReadBufferPositive(&pad, 1);
		pspDebugScreenClear();
		print_title();
		counter=0;
        while(counter < 5)
        {
          if(Install_Choice == counter)
          {
            //Highlight the selection
          	TextColor(0xFF0000FF);
          }
          else
          {
            //Don't highlight the selection
            TextColor(0xFFA9A9A9);
          }
          switch(counter)
          {
            case 0: Text("     Install Enabled\n");break;
			case 1: Text("     Install Disabled\n");break;
			case 2: Text("     Install 3.71 version Enabled\n");break;
			case 3: Text("     Install 3.71 version Disabled\n");break;
			case 4: Text("     Exit\n");break;
		  }
          counter++;
        }
		
		lineClear(30);
        switch(Install_Choice)
        {
          case 0: PrintTextColor(0xFF0000FF, "  Install Normal DayPR Enabled In the Game.txt"); break;
		  case 1: PrintTextColor(0xFF0000FF, "  Install Normal DayPR Disabled In the Game.txt"); break;
          case 2: PrintTextColor(0xFF0000FF, "  Install 3.71 DayPR Enabled In the Game.txt"); break;
		  case 3: PrintTextColor(0xFF0000FF, "  Install 3.71 DayPR Disabled In the Game.txt"); break;
		  case 4: PrintTextColor(0xFF0000FF, "  Exit Installer"); break;
		}

		if(pad.Buttons & PSP_CTRL_UP)
			{
				if(Install_Choice > 0)
					{
						Install_Choice--;
					}
				else if(Install_Choice == 0)
					{
						Install_Choice=4;
                    }
				if(cheatButtonY < 12) cheatButtonY++; sceKernelDelayThread(150000-(10000*cheatButtonY));
			}
        else if(pad.Buttons & PSP_CTRL_DOWN)
            {
				if(Install_Choice < 4)
					{
						Install_Choice++;
					}
				else if(Install_Choice == 4)
					{
						Install_Choice=0;
					}
					if(cheatButtonY < 12) cheatButtonY++; sceKernelDelayThread(150000-(10000*cheatButtonY));
			}
        else
            {
				cheatButtonY=0;
            }
			
		if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if(Install_Choice == 0)
					{	
						Install_Init();
						Install_DayPR();
						sceKernelDelayThread(100000);
						gametxt_enabled();
					}
				
				else if(Install_Choice == 1)
					{	
						Install_Init();
						Install_DayPR();
						sceKernelDelayThread(100000);
						gametxt_disabled();
					}
					
				else if(Install_Choice == 2)
					{	
						Install_Init();
						Install_DayPR371();
						sceKernelDelayThread(100000);
						gametxt_enabled();
					}
					
				else if(Install_Choice == 3)
					{
						Install_Init();
						Install_DayPR371();
						sceKernelDelayThread(100000);
						gametxt_disabled();
					}

				else if(Install_Choice == 4)
					{
						ExitIn10();
					}	
			}
    }
}


int main(int argc, char *argv[])
{
        SetupCallbacks();
        sceKernelDelayThread(1000000);
        pspDebugScreenInit();
		
		SetXY(0, 0);
        Install();
        ExitIn10();
        return 0;
}