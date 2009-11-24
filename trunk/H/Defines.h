/*
I Decided to put ALL! the defined things in one file and also added a few new things into this to help organize the code a little better. 
They are also commented about what they are.
I consider this the first step to optimising the whole source .
6:39 P.M. 9/17/09
*/


#ifndef DEFINES_H
#define DEFINES_H

//************
//***Header***
//************
#define AUTHOR_S "lilmnm's "
#define NAME_PR "DayPR "
#define VER_STR "Rev.6 -- "
#define VER_SFX "Beta!"
#define Playing_Game "Your Playing: "
#define Home_Site "www.havoc-forums.com/"
#define HAX_ON "HAX ARE ON            "
#define ALL_HAX_ON "ALL HAX ARE OFF      "
#define HAX_OFF "HAX ARE OFF          "

//************
//**Initiation**
//************
#define INITIATION "Initiation                                                        "
#define PRESS_START "                           [PRESS START]\n\n"

//***********
//***Menu***
//***********

#define Theme_Menu_Title "Select A Theme                                                    "
#define Theme_Menu_Helper "Made By lilmnm                                                    "
#define Theme_Menu_Helper1 ">< = Select; () = Cancel                                          "
#define Config_Header "DayPR Configuration Menu                                          "
#define EasterEgg_Title "EASTEREGG!!!!!                                                    "
#define EasterEgg_Helper "() = Cancel/Return to DayPR menu                                  "

//**************
//**Block flags**
//**************
#define FLAG_DMA  	(1<<4)
#define FLAG_FREEZE (1<<5)
#define FLAG_DWORD	(3<<6)
#define FLAG_UWORD	(2<<6)
#define FLAG_WORD		(1<<6)
#define FLAG_BYTE		(0<<6)

//**************
//**Cheat flags**
//**************
#define FLAG_SELECTED (1<<0)	//If selected, will be disabled/enabled by music button
#define FLAG_CONSTANT	(1<<1)  //If 1, cheat is constantly on regardless of music button
#define FLAG_FRESH    (1<<2)  //Cheat was just recently enabled/disabled
#define BLOCK_MAX 2048

//***************
//**Config Menu**
//***************
#define LANG_CONF1 " Shortcut: "
#define LANG_CONF5 " Activate ScreenShot: "
#define LANG_CONF6 " ScreenShot Key Combo: "
//#define LANG_CONF7 "Code Activation Button: "
#define LANG_PRESSSKEY "Press A new key..."

//*************
//**Universal**
//*************
#define fileBufferPeek(a_out, a_ahead) if((fileBufferOffset + a_ahead) >= 1024) { fileBufferBackup=sceIoLseek(fd, 0, SEEK_CUR); sceIoLseek(fd, a_ahead, SEEK_CUR); sceIoRead(fd, &a_out, 1); sceIoLseek(fd, fileBufferBackup, SEEK_SET); } else { a_out=fileBuffer[fileBufferOffset + a_ahead]; }
#define fileBufferRead(a_out, a_size) if(fileBufferOffset == 1024) { fileBufferSize=sceIoRead(fd, fileBuffer, 1024); fileBufferOffset=0; } memcpy(a_out, &fileBuffer[fileBufferOffset], a_size); fileBufferOffset+=a_size; fileBufferFileOffset+=a_size;
#define lineClear(a_line) pspDebugScreenSetXY(0, a_line); pspDebugScreenPuts("                                                                   "); pspDebugScreenSetXY(0, a_line);
#define NEWLINE "\n"
#define UMD_DATA "disc0:/UMD_DATA.BIN"
#define PARAM_SFO "disc0:/PSP_GAME/PARAM.SFO"
#define GAME_TXT "ms0:/seplugins/DayPR/__________.txt"
#define MAX_THREAD 64
#define DayPRimportant_bin "ms0:/seplugins/DayPR/DayPRimportant.bin"
#define TEMP_TXT "ms0:/seplugins/DayPR/temp.txt"
#define BackGround pspDebugScreenSetBackColor
#define Text pspDebugScreenPuts
#define TextColor pspDebugScreenSetTextColor
#define SetXY pspDebugScreenSetXY

//***********
//**Control**
//***********
#define CTRL_REPEAT_TIME 0x40000
#define CTRL_REPEAT_INTERVAL 0x8000

//************
//***Colors***
//************
#define AliceBlue 0xFFFFF80F
#define AntiqueWhite 0xFFD7EBFA
#define Aqua 0xFFFFFF00
#define Aquamarine 0xFFD4FF7F
#define SandyBrown 0xFF604AF4
#define SeaGreen 0xFF578B2B
#define SeaShell 0xFFEEF5FF
#define Sienna 0xFF2D52A0 
#define Silver 0xFFC0C0C0 
#define SkyBlue 0xFFEBCE87
#define SlateBlue 0xFFCEEB87
#define SlateGray 0xFF908070 
#define Snow 0xFFFAFAFF 
#define SpringGreen 0xFF7FFF00 
#define SteelBlue 0xFFB48246 
#define Tan 0xFF8CB4D2
#define Teal 0xFF808000 
#define Thistle 0xFFD8BFD8
#define Tomato 0xFF4763FF 
#define Turquoise 0xFFD0E040 
#define Violet 0xFFEE82EE 
#define Wheat 0xFFB3DEF5 
#define White 0xFFFFFFFF 
#define WhiteSmoke 0xFFF5F5F5
#define Yellow 0xFF00FFFF
#define YellowGreen 0xFF32CD9A
#define Azure 0xFFFFFFF0 
#define Beige 0xFFDCF5F5
#define Bisque 0xFFC4E4FF 
#define Black 0x00000000
#define BlanchedAlmond 0xFFCDEBFF
#define Blue 0xFFFF0000
#define BlueViolet 0xFFE22B8A
#define Brown 0xFF2A2AA5
#define BurlyWood 0xFF87B8DE
#define CadetBlue 0xFFA09ES7
#define Chartreuse 0xFF00FF7F
#define Chocolate 0xFF1E69D2
#define Coral 0xFF507FFF
#define CornflowerBlue 0xFFED9564
#define Cornsilk 0xFFDCF8FF
#define Crimson 0xFF3C14DC
#define Cyan 0xFFFFFF00
#define DarkBlue 0xFF8B0000
#define DarkCyan 0xFF8B8B00
#define DarkGoldenRod 0xFF0B86B8
#define DarkGray 0xFFA9A9A9
#define DarkGreen 0xFF006400
#define DarkKhaki 0xFF6BB7BD
#define DarkMagenta 0xFF8B008B
#define DarkOliveGreen 0xFF2F6B55
#define Darkorange 0xFF008CFF
#define DarkOrchid 0xFFCC3299
#define DarkRed 0xFF00008B
#define DarkSalmon 0xFF7A96E9
#define DarkSeaGreen 0xFF8FBC8F
#define DarkSlateBlue 0xFF8B3D48
#define DarkSlateGray 0xFF4F4F2F
#define DarkTurquoise 0xFFD1CE00
#define DarkViolet 0xFFD30094
#define DeepPink 0xFF9314FF
#define DeepSkyBlue 0xFFFFBF00
#define DimGray 0xFF696969
#define DodgerBlue 0xFFFF901E
#define FireBrick 0xFF2222B2
#define FloralWhite 0xFFF0FAFF
#define ForestGreen 0xFF228B22
#define Fuchsia 0xFFFF00FF
#define Gainsboro 0xFFDCDCDC
#define GhostWhite 0xFFFFF8F8
#define Gold 0xFF00D7FF
#define GoldenRod 0xFF20A5DA
#define Gray 0xFF808080
#define Green 0xFF008000
#define GreenYellow 0xFF2FFFAD
#define HoneyDew 0xFFF0FFF0
#define HotPink 0xFFB469FF
#define IndianRed  0xFF5C5CCD
#define Indigo  0xFF82004B
#define Ivory 0xFFF0FFFF
#define Khaki 0xFF8CE6F0
#define Lavender 0xFFFAE6E6
#define LavenderBlush 0xFFF5F0FF
#define LawnGreen 0xFF00FC7C
#define LemonChiffon 0xFFCDFAFF
#define LightBlue 0xFFE6D8AD
#define LightCoral 0xFF8080F0
#define LightCyan 0xFFFFFFE0
#define LightGoldenRodYellow 0xFFD2FAFA
#define LightGray 0xFFD3D3D3
#define LightGreen 0xFF90EE90
#define LightPink 0xFFC1B6FF
#define LightSalmon 0xFF7AA0FF
#define LightSeaGreen 0xFFAAB220
#define LightSkyBlue 0xFFFACE87
#define LightSlateGray 0xFF998877
#define LightSteelBlue 0xFFDEC4B0
#define LightYellow 0xFFE0FFFF
#define Lime 0xFF00FF00
#define LimeGreen 0xFF32CD32
#define Linen 0xFFE6F0FA
#define Magenta 0xFFFF00FF
#define Maroon 0xFF000080
#define MediumAquaMarine 0xFFAACD66
#define MediumBlue 0xFFCD0000
#define MediumOrchid 0xFFD355BA
#define MediumPurple 0xFFD87093
#define MediumSeaGreen 0xFF71B33C
#define MediumSlateBlue 0xFFFF687B
#define MediumSpringGreen 0xFF9AFA00
#define MediumTurquoise 0xFFCCD148
#define MediumVioletRed 0xFF8515C7
#define MidnightBlue 0xFF701919
#define MintCream 0xFFFAFFF5
#define MistyRose 0xFFE1E4FF
#define Moccasin 0xFFB5E4FF
#define NavajoWhite 0xFFADDEFF
#define Navy 0xFF800000
#define OldLace 0xFFE6F5FD
#define Olive 0xFF008080
#define OliveDrab 0xFF238E6B
#define Orange 0xFF00A5FF
#define OrangeRed 0xFF0045FF
#define Orchid 0xFFD670DA
#define PaleGoldenRod 0xFFAAE8EE
#define PaleGreen 0xFF98FB98
#define PaleTurquoise 0xFFEEEEAF
#define PaleVioletRed 0xFF9370D8
#define PapayaWhip 0xFFD5EFFF
#define PeachPuff 0xFFB9DAFF
#define Peru 0xFF3F85CD
#define Pink 0xFFCBC0FF
#define Plum 0xFFDDA0DD
#define PowderBlue 0xFFE6E0B0
#define Purple 0xFF800080
#define Red 0xFF0000FF
#define RosyBrown 0xFF8F8FBC
#define RoyalBlue 0xFFE16941
#define SaddleBrown 0xFF13458B
#define Salmon 0xFF7280FA

#endif