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
#include"architecture.hpp"

using namespace std;

int main(int argc, char *argv[])
{
				Display* display;
				display = XOpenDisplay(0);

				if (!display) cout<< "Error!";
				else cout << "o_O";
				
  			int screen, root;
				screen = DefaultScreen(display);
				root = RootWindow(display, screen);
				if (true) cout << "%)" << endl;
   XCreateSimpleWindow(display, root,
			      0, 0, 30, 100, 1,
			      BlackPixel(display, screen),
			      WhitePixel(display, screen));



	return 0;
}

