#include "khawm.hpp"
struct keybind
{
	int mask;
	int key;
	const char* cmd;
};

const int key_number = 2;

keybind keyboard[key_number] = {
	  {Mod4Mask, XK_Right, ":next"}
	, {Mod4Mask, XK_Left, ":prev"}


};

int ndesktops = 4;
