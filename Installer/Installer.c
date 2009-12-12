//Includes
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
#include "Files/DAYPR.h" //files to be installed
#include "Files/DAYPR371.h" // files to be installed

PSP_MODULE_INFO("DayPR Installer", 0, 1, 1); //name of the module or PRX

// Some of my defines i use to help me  out  to code faster
#define printf pspDebugScreenPrintf
#define lineClear(a_line) pspDebugScreenSetXY(0, a_line); pspDebugScreenPuts("                                                                   "); pspDebugScreenSetXY(0, a_line);
#define Text pspDebugScreenPuts
#define TextColor pspDebugScreenSetTextColor
#define SetXY pspDebugScreenSetXY
#define Install_Version " DayPR Rev.6 -- Beta Installer\n"

// global defines for menus and such
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

//some lib stuff i decited to make for this to help print text  faster and set its color
void PrintTextColor(int color, const char *txt)
	{
		TextColor(color); //color of the text (shold always before the text to color it)
		Text(txt); //the text to be written 
	}

//Prints the text in a color and in a certin positon on the screen
void PrintTextColorXY(int x, int y, int color, const char *txt)
	{
		SetXY(x, y); //locaton on the X axis and Y axis
		TextColor(color); //color
		Text(txt); // text
	}

// this clears a line so you can print somthing new in its place  and then puts a color to it
void ClearLineTextColorY(int y, int color, const char *txt)
	{
		lineClear(y); // clears the line on the Y axis
		TextColor(color); //color
		Text(txt); //text
	}

//Prints  a title
void print_title()
{
        PrintTextColorXY(0, 1, 0xFF0000FF, Install_Version);
		SetXY(0, 3);
        return;
}

void Install_Init() //installs files for the install
{ 	
	pspDebugScreenClear();
	print_title();
	PrintTextColorXY(0, 3, 0xFF0000FF, "     Creating folders: ");
	PrintTextColorXY(0, 4, 0xFF0000FF, "     Creating folders ms0:/seplugins/DayPR ");
	sceIoMkdir("ms0:/seplugins/DayPR", 0777); // creates the DayPR folder
	sceKernelDelayThread(1000000); //microsecont delay for 1 secont
	PrintTextColor(0xFF0000FF, "  DONE!!");
	sceKernelDelayThread(500000); //microsecont delay for .5 secont
	PrintTextColorXY(0, 5, 0xFF0000FF, "     Creating folders ms0:/seplugins/DayPR/dumps ");
	sceIoMkdir("ms0:/seplugins/DayPR/dumps", 0777); //Creates the folder "dumps" in the DayPR folder for RAM dumps
	sceKernelDelayThread(1000000); //microsecont delay for 1 secont
	PrintTextColor(0xFF0000FF, "  DONE!!");
	sceKernelDelayThread(500000); //microsecont delay for .5 secont
	PrintTextColorXY(0, 6, 0xFF0000FF, "     Creating folders ms0:/seplugins/DayPR/search ");
	sceIoMkdir("ms0:/seplugins/DayPR/search", 0777); //Creates the folder "search" in the DayPR folder for searches
	sceKernelDelayThread(1000000);//microsecont delay for 1 secont
	PrintTextColor(0xFF0000FF, "  DONE!!");
	sceKernelDelayThread(1000000);//microsecont delay for 1 secont
}

/*
this part of the source was given to me from Demon_Child/RedHate
Well this writes a file from a file that has been BIN2C 
*/
int writeFile(char path[], unsigned char buffer[], unsigned int size_buffer)
{
	signed int fd;
	
	fd = sceIoOpen(path, PSP_O_CREAT | PSP_O_WRONLY | PSP_O_TRUNC, 0777);
	sceIoWrite(fd, buffer, size_buffer); //this can be found in the /Files/ directory in files named DAYPR.h and DAYPR371.h
	sceIoClose(fd);
	
	//checks to see if the files have been writen out or not
	fd=sceIoOpen(path, PSP_O_RDONLY, 0777);
	if(fd > 0)
	{
		sceIoClose(fd);
		sceKernelDelayThread(1500000); //its been writen
		return 1;
	}
	else
	{
		sceIoClose(fd);
		sceKernelDelayThread(1500000); //ERROR IT HAS FAILED!
		return 0;
	}
	
}

//this just exits the Installer in 10 seconds
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
			sceKernelExitGame(); // exits the game
	}

//Writes to the GAME.TXT as Enabled
void gametxt_enabled()
{
	char *txtline = "ms0:/seplugins/%s.prx 1\n"; // text to be writen
	char txtdata[100];
	sprintf(txtdata, txtline, "DayPR");
	signed int fd0 = sceIoOpen("ms0:/seplugins/game.txt", PSP_O_WRONLY | PSP_O_CREAT, 0777);
	sceIoLseek(fd0, 0, 2);
	PrintTextColorXY(0, 9, 0xFF0000FF, "     Writing DayPR enabled to Game.txt...\n"); //Telling you what its doing what its doing
	sceIoWrite(fd0, txtdata, strlen(txtdata));
	sceIoClose(fd0);
	sceKernelDelayThread(2000000); //Waits 2 seconds for it to finish
	ClearLineTextColorY(9, 0xFF0000FF, "     Done!\n"); //Tells you its done
	sceKernelDelayThread(2000000); //Waits 2 seconds
	return;
}

//Writes the the GAME.TXT as Disabled
void gametxt_disabled()
{
	char *txtline = "\nms0:/seplugins/%s.prx 0\n"; //Text to be writen
	char txtdata[100];
	sprintf(txtdata, txtline, "DayPR");
	signed int fd0 = sceIoOpen("ms0:/seplugins/game.txt", PSP_O_WRONLY | PSP_O_CREAT, 0777);
	sceIoLseek(fd0, 0, 2);
	PrintTextColorXY(0, 9, 0xFF0000FF, "     Writing DayPR disabled to Game.txt...\n"); //Telling you what its doing what its doing
	sceIoWrite(fd0, txtdata, strlen(txtdata)); //Actually writes to the file
	sceIoClose(fd0);
	sceKernelDelayThread(200000); //waits 2 seconds
	ClearLineTextColorY(9, 0xFF0000FF, "     Done!\n"); //tells you its done
	sceKernelDelayThread(200000); //waits two seconds
	return;
}

/* 

This is to buggy for it to be left in so i took it out it started to piss me off so eh what ever fuck it I'll do it live!

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


//Installs thes normal DayPR 
void Install_DayPR()
	{
		print_title(); // prints the title
		PrintTextColorXY(0, 7, 0xFF0000FF, "     Installing DayPR.prx to ms0:/seplugins/..."); //Tells you what its doing
		writeFile("ms0:/seplugins/DayPR.prx", DayPR, size_DayPR); //can be found in DAYPR.H
		ClearLineTextColorY(7, 0xFF0000FF, "     Done!\n"); //Tells you its done
		sceKernelDelayThread(1500000); //waits 1.5 seconds
		//Yes_No();   eh dont worry about this
	}

//Installs the 3.71 version of DayPR
void Install_DayPR371()
	{
		print_title(); // prints the title
		PrintTextColorXY(0, 7, 0xFF0000FF, "     Installing DayPR.prx to ms0:/seplugins/..."); //Tells you what its doing
		writeFile("ms0:/seplugins/DayPR.prx", DayPR371, size_DayPR371); //can be found at DAYPR371.h
		ClearLineTextColorY(7, 0xFF0000FF, "     Done!\n"); //Tells you its done
		sceKernelDelayThread(1500000); //waits 1.5 seconds
		//Yes_No();	 menu is buggy to lazy to fix it right now =P
	}

//Main menu
void Install()
{ 
  while(1)
    {
		sceCtrlReadBufferPositive(&pad, 1);
		print_title(); // prints the title
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
          { //list of options
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
        { //Discriptions
          case 0: PrintTextColor(0xFF0000FF, "  Install Normal DayPR Enabled In the Game.txt"); break;
		  case 1: PrintTextColor(0xFF0000FF, "  Install Normal DayPR Disabled In the Game.txt"); break;
          case 2: PrintTextColor(0xFF0000FF, "  Install 3.71 DayPR Enabled In the Game.txt"); break;
		  case 3: PrintTextColor(0xFF0000FF, "  Install 3.71 DayPR Disabled In the Game.txt"); break;
		  case 4: PrintTextColor(0xFF0000FF, "  Exit Installer"); break;
		}
		
		//control inputs and functions
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

//main
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

// Have Fun!! =D