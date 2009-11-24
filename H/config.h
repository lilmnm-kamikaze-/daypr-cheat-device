#ifndef _CONFIG_H
#define _CONFIG_H

static const char * menu_yesno[] =
{
	"Yes",
	"No"
};

static const char * menu_conf[] =
{
	"Shortcut: VOLUP+VOLDOWN",
	"Activate ScreenShot:    ",
	"Screenshot Key Combo: Square+Down"
};

typedef struct _conf {
	unsigned int menuKey;	 // Shortcut key
	int enabless;		     // If screenshot is enabled
	int screenKey;			 // Screenshot shortcut key
//unsigned int triggerKey; //Button to Activat your Codes
	unsigned int Theme;		 //Theme thats selected
	unsigned int textcolor01; //The colors for the theme this is the main color and the highlighted color
	unsigned int textcolor02; //This color is the inactive or unhighlighted color. Secondary color.
	unsigned int bgcolor; //The  Background color of the theme.
} t_conf, * p_conf;

extern t_conf config;

extern void conf_get_keyname(unsigned int key, char * res);
extern void conf_load();
extern void conf_save();

#endif
