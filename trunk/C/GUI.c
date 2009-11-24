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


/*
extern void Tabs_main_Header()
{
 	BackGround(config.bgcolor);
    TextColor(config.textcolor01);Text(left);TextColor(tabSelected == 0? config.textcolor01: config.textcolor02); if (tabSelected == 0) {Text("      ");Text(left);Text("Hacks");Text(left);Text(" ");} else {Text("      Hacks ");}
    TextColor(tabSelected == 1? config.textcolor01: config.textcolor02); if (tabSelected == 1) {Text(left);Text("Search");Text(left);Text(" ");} else {Text("Search ");}
    TextColor(tabSelected == 2? config.textcolor01: config.textcolor02); if (tabSelected == 2) {Text(left);Text("PRX");Text(left);Text(" ");} else {Text("PRX ");}
    TextColor(tabSelected == 3? config.textcolor01: config.textcolor02); if (tabSelected == 3) {Text(left);Text("Browser");Text(left);Text(" ");} else {Text("Browser ");}
    TextColor(tabSelected == 4? config.textcolor01: config.textcolor02); if (tabSelected == 4) {Text(left);Text("Decoder");Text(left);Text(" ");} else {Text("Decoder ");}
    TextColor(tabSelected == 5? config.textcolor01: config.textcolor02); if (tabSelected == 5) {Text(left);Text("Logger");Text(left);Text(" ");} else {Text("Logger ");}
	TextColor(tabSelected == 6? config.textcolor01: config.textcolor02); if (tabSelected == 6) {Text(left);Text("Extra Options");Text(left);Text("     ");} else {Text("Extra Options     ");}TextColor(config.textcolor01);Text(left);
}

extern void Tabs_main_Header_Effects()
{
	if (tabSelected == 0)
		{
			TextColor(config.textcolor01);Text(Hline);
		}
	else if (tabSelected == 1)
		{
			TextColor(config.textcolor01);Text(Sline);
		} 
	else if (tabSelected == 2)
		{
			TextColor(config.textcolor01);Text(Pline);
		} 
	else if (tabSelected == 3)
		{
			TextColor(config.textcolor01);Text(Bline);
		} 
	else if (tabSelected == 4)
		{
			TextColor(config.textcolor01);Text(Dline);
		} 
	else if (tabSelected == 5)
		{
			TextColor(config.textcolor01);Text(Lline);
		} 
	else if (tabSelected == 6)
		{
			TextColor(config.textcolor01);Text(Eline);
		}
}
*/
		
		
		
		
		
		
		
		
		