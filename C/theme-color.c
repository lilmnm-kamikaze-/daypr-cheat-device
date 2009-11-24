/*
Decited to take most of the core Theme code from the main .c file to cut down on its size.
this is also a second step to further optimising the code and to organize it.
3:55 P.M. 9/18/09
*/

#define PSP_FW_VERSION 150
#include <pspkernel.h>
#include <pspdisplay.h>
#include <pspctrl.h>
#include <pspumd.h>
#include <stdio.h>
#include <stdlib.h>
#include "H/Theme-color.h"
#include "H/Defines.h"

unsigned int counter;
unsigned char cheatButtonYAge=0;
SceCtrlData pad;

void DayPR_Theme() // Themes only have 3 variations of colors (just for now)
{
	config.textcolor01=White;
	config.textcolor02=Gray;
	config.bgcolor=0xFF000055;
	conf_save();
}

void Classic_Theme()
{
	config.textcolor01=White;
	config.textcolor02=Gray;
	config.bgcolor=Black;
	conf_save();
}

void Hacker_Theme()
{
	config.textcolor01=Lime;
	config.textcolor02=Gray;
	config.bgcolor=Black;
	conf_save();
}

void Sneaky_Theme()
{
	config.textcolor01=Black;
	config.textcolor02=DarkGray;
	config.bgcolor=LightGray;
	conf_save();
}

void EMO_Theme()
{
	config.textcolor01=Purple;
	config.textcolor02=Gray;
	config.bgcolor=Black;
	conf_save();
}

void Girls_Theme()
{
	config.textcolor01=HotPink;
	config.textcolor02=SkyBlue;
	config.bgcolor=DarkViolet;
	conf_save();
}

void CodeRed_Theme()
{
	config.textcolor01=Red;
	config.textcolor02=DarkGray;
	config.bgcolor=Black;
	conf_save();
}

extern void Theme_Menu_Header()
	{
		BackGround(config.bgcolor);
		TextColor(config.textcolor01); Text(left);Text(Theme_Menu_Title);Text(left);
		TextColor(config.textcolor01); Text(bottom_line);
		TextColor(config.textcolor01); Text("\n  Well after many complants about the color scheme i decited  to\n  add selectable Themes with diffrent color combos!\n" NEWLINE);
		TextColor(config.textcolor01); Text("  Themes:" NEWLINE);
	    BackGround(config.bgcolor);
	}
	
extern void Theme_Menu_Body()
	{
        counter=0;
        while(counter < 7)
          {
          switch(counter)
			{
				case 0: if (config.Theme == 0){TextColor(White);  Text("  Default" NEWLINE);} else {TextColor(config.textcolor02);Text("  Default" NEWLINE);} break;
				case 1: if (config.Theme == 1){TextColor(White); Text("  Classic" NEWLINE);} else {TextColor(config.textcolor02);Text("  Classic" NEWLINE);} break;
				case 2: if (config.Theme == 2){TextColor(Lime); Text("  Hacker" NEWLINE);} else {TextColor(config.textcolor02);Text("  Hacker" NEWLINE);} break;
				case 3: if (config.Theme == 3){TextColor(Black); Text("  Sneaky Student" NEWLINE);} else {TextColor(config.textcolor02);Text("  Sneaky Student" NEWLINE);} break;
				case 4: if (config.Theme == 4){TextColor(Purple);  Text("  Emo" NEWLINE);} else {TextColor(config.textcolor02);Text("  Emo" NEWLINE);} break;
				case 5: if (config.Theme == 5){TextColor(HotPink); Text("  Laydies Only" NEWLINE);} else {TextColor(config.textcolor02);Text("  Laydies Only" NEWLINE);} break;
				case 6: if (config.Theme == 6){TextColor(Red); Text("  Code Red" NEWLINE);} else {TextColor(config.textcolor02);Text("  Code Red" NEWLINE);} break;
			}
          counter++;
          }
	}
	
extern void Theme_Menu_Footer()
	{
		  //Helper
		TextColor(config.textcolor01);
		SetXY(0, 30);Text(top_line);
        lineClear(31);
		
			switch(config.Theme)
				{
					case 0: TextColor(config.textcolor01);Text(left);TextColor(0xFFFF8000);Text(Theme_Menu_Helper); TextColor(config.textcolor01); Text(left); break;
					case 1: TextColor(config.textcolor01);Text(left);TextColor(0xFFFF8000);Text(Theme_Menu_Helper); TextColor(config.textcolor01); Text(left); break;
					case 2: TextColor(config.textcolor01);Text(left);TextColor(0xFFFF8000);Text(Theme_Menu_Helper); TextColor(config.textcolor01); Text(left); break;
					case 3: TextColor(config.textcolor01);Text(left);TextColor(0xFFFF8000);Text(Theme_Menu_Helper); TextColor(config.textcolor01); Text(left); break;
					case 4: TextColor(config.textcolor01);Text(left);TextColor(0xFFFF8000);Text(Theme_Menu_Helper); TextColor(config.textcolor01); Text(left); break;
					case 5: TextColor(config.textcolor01);Text(left);TextColor(0xFFFF8000);Text(Theme_Menu_Helper); TextColor(config.textcolor01); Text(left); break;
					case 6: TextColor(config.textcolor01);Text(left);TextColor(0xFFFF8000);Text(Theme_Menu_Helper); TextColor(config.textcolor01); Text(left); break;
				}
		SetXY(0, 32);
		TextColor(config.textcolor01);Text(left);TextColor(0xFFFF8000);Text(Theme_Menu_Helper1); TextColor(config.textcolor01); Text(left); 
		Footer1();
	}



extern void Input_Theme_Menu()
	{
		if(pad.Buttons & PSP_CTRL_UP)
			{
				if(config.Theme > 0)
					{
						config.Theme--;
					}
				else if(config.Theme == 0)
					{
						config.Theme=6;
					}
					menuDraw();
					if(cheatButtonYAge < 12) cheatButtonYAge++; sceKernelDelayThread(150000-(10000*cheatButtonYAge));
			}
		else if(pad.Buttons & PSP_CTRL_DOWN)
			{
				if(config.Theme < 6)
					{
						config.Theme++;
					}
				else if(config.Theme == 6)
					{
						config.Theme=0;
					}
					menuDraw();
					if(cheatButtonYAge < 12) cheatButtonYAge++; sceKernelDelayThread(150000-(10000*cheatButtonYAge));
			}
		else
			{
				cheatButtonYAge=0;
			}
			
		if(pad.Buttons & PSP_CTRL_CROSS)
			{
				if (config.Theme == 0)
					{ //defult
						DayPR_Theme();
						conf_save();
						menuDraw();
					}

				else if (config.Theme == 1)
					{  //classic theme
						Classic_Theme();
						conf_save();
						menuDraw();
					}

				else if (config.Theme == 2)
					{  //Hacker theme
						Hacker_Theme();
						conf_save();
						menuDraw();
					}

				else if (config.Theme == 3)
					{  //Sneaky student theme 
						Sneaky_Theme();          //Needs work on it......
						conf_save();
						menuDraw();
					}

				else if (config.Theme == 4)
					{  //EMO theme
						EMO_Theme();
						conf_save();
						menuDraw();
					}

				else if (config.Theme == 5)
					{  //Girls Theme
						Girls_Theme();
						conf_save();
						menuDraw();
					}
					
				else if (config.Theme == 6)
					{  //Girls Theme
						CodeRed_Theme();
						conf_save();
						menuDraw();
					}
			}
	}




