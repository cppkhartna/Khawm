#include "khawm.hpp"
struct keybind
{
	int mask;
	int key;
	const char* cmd;
};

const int key_number = 10;

keybind keyboard[key_number] = {
	  {Mod4Mask, XK_Right, ":next"}
	, {Mod4Mask, XK_Left, ":prev"}
	, {Mod4Mask, XK_Up, ":up"}
	, {Mod4Mask, XK_Down, ":down"}
	, {Mod4Mask, XK_c, ":kill"}
	, {Mod4Mask, XK_o, "opera"}
	, {Mod4Mask, XK_i, "iceweasel"}
	, {Mod4Mask, XK_g, "chromium-brouser"}
	, {Mod4Mask, XK_f, "thunar"}
	, {Mod4Mask, XK_q, ":quit"}

};

int ndesktops = 4;
