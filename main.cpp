//Khartikova
//khawm is Khana Window Manager
//It should be very-very simple due to my lack of Xlib knowledge :(
#include <X11/cursorfont.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xmd.h>
//#ifdef SHAPE
//#include <X11/extensions/shape.h>
//#endif

#include <iostream>
#include"windowmanager.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  windowmanager wm;
	cout << wm.MainLoop();
	return 0;
}

