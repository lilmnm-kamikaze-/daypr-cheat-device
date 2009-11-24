//GUI 

#define PSP_FW_VERSION 150
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspumd.h>
#include <stdio.h>
#include <stdlib.h>
#include "H/DayPR.h"
#include "H/config.h"
#include "H/GUI.h"
#include "H/Defines.h"

extern void Header1()
 { 
	SetXY(0, 0);
    Text(top_line);
	SetXY(0, 2);
 }  
 
extern void Footer1()
 { 
   SetXY(0, 33);
   TextColor(config.textcolor01);
   Text(bottom_line);
 }
 
extern void INITIATION_SCREEN()
{ 
    BackGround(config.bgcolor);
    TextColor(config.textcolor01);Text(left);Text(INITIATION);Text(left);
	TextColor(config.textcolor01);Text(bottom_line);
    TextColor(config.textcolor01);Text(" Please tell DayPR when to generate OFF codes by pressing\n the MUSICAL NOTE button while inside the game at least once\n and NOT when the cheat menu is showing!!!\n" NEWLINE);
    TextColor(0xFF00FF00);Text(" INFO!:\n - It's Beta for now, new theme and stuff from Demon_child\n - Please go to http://havoc-forums.com/ for more info and updates\n\n" NEWLINE);
    TextColor(config.textcolor01);Text(PRESS_START);
	Footer1();
}


