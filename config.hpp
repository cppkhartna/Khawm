#include "khawm.hpp"

struct keybind
{
	int mask;
	unsigned int key;
	const char* cmd;
};

const int key_number = 19;

keybind keyboard[key_number] = {
	  {Mod4Mask, XK_Right, ":next"}
	, {Mod4Mask, XK_Left, ":prev"}
	, {Mod4Mask, XK_Up, ":deskn"}
	, {Mod4Mask, XK_Down, ":deskp"}
	, {Mod4Mask, XK_Home, ":swapp"}
	, {Mod4Mask, XK_End, ":swapn"}
	, {Mod4Mask, XK_c, ":kill"}
	, {Mod4Mask, XK_o, "opera"}
	, {Mod4Mask, XK_i, "iceweasel"}
	, {Mod4Mask, XK_g, "chromium-brouser"}
	, {Mod4Mask, XK_f, "thunar"}
	, {Mod4Mask, XK_q, ":quit"}
	, {Mod4Mask, XK_Return, "xfce4-terminal"}
	, {Mod4Mask, XK_r, ":rotate RIGHT"}
	, {Mod4Mask, XK_l, ":rotate LEFT"}
	, {Mod4Mask, XK_x, "xclock"}
	, {Mod4Mask, XK_equal, ":resize +"}
	, {Mod4Mask, XK_minus, ":resize -"}
	, {Mod4Mask, XK_Delete, ":dirty hack"}


};

const int ndesktops = 5;

const char* desktop_names[ndesktops] = {
		"1:com",
		"2:web",
		"3:jab",
		"4:dev",
		"5:float"
};

int desktop_def_layouts[ndesktops] = {
		0,
		0,
		0,
		0,
		FLOAT
};

