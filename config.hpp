#include "khawm.hpp"
struct keybind
{
	int mask;
	unsigned int key;
	const char* cmd;
};

const int key_number = 16;

keybind keyboard[key_number] = {
	  {Mod4Mask, XK_Right, ":next"}
	, {Mod4Mask, XK_Left, ":prev"}
	, {Mod4Mask, XK_Up, ":up"}
	, {Mod4Mask, XK_Down, ":down"}
	, {Mod4Mask, XK_Page_Up, ":deskn"}
	, {Mod4Mask, XK_Page_Down, ":deskp"}
	, {Mod4Mask, XK_Home, ":swapp"}
	, {Mod4Mask, XK_End, ":swapn"}
	, {Mod4Mask, XK_c, ":kill"}
	, {Mod4Mask, XK_o, "opera"}
	, {Mod4Mask, XK_i, "iceweasel"}
	, {Mod4Mask, XK_g, "chromium-brouser"}
	, {Mod4Mask, XK_f, "thunar"}
	, {Mod4Mask, XK_q, ":quit"}
	, {Mod4Mask, XK_Return, "xfce4-terminal"}
	, {Mod4Mask, XK_x, "xclock"}

};

int ndesktops = 4;
