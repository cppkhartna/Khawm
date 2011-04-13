#include "khawm.hpp"
struct keybind
{
	int mask;
	int key;
	const char* cmd;
};

const int key_number = 4;

keybind keyboard[key_number] = {
	  {Mod4Mask, XK_Right, ":next"}
	, {Mod4Mask, XK_Left, ":prev"}
	, {Mod4Mask, XK_Up, ":up"}
	, {Mod4Mask, XK_Down, ":down"}


};

int ndesktops = 4;
