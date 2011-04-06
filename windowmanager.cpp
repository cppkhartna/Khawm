#include "windowmanager.hpp"

windowmanager::windowmanager()
{
	display = XOpenDisplay(0);

  int screen, root;
	screen = DefaultScreen(display);
	root = RootWindow(display, screen);
  XCreateSimpleWindow(display, root,
	  0, 0, 30, 100, 1,
	  BlackPixel(display, screen),
	  WhitePixel(display, screen));

	//MainLoop();

}

int windowmanager::MainLoop()
{

	XEvent xev;
	for (;;)
	{
		XNextEvent(display, &xev);
		switch (xev.type)
		{
		  case CreateNotify:
			return xev.xcreatewindow.window;
		
		};
	
	}
				
}
