#include "windowmanager.hpp"

windowmanager::windowmanager()
{
	display = XOpenDisplay(0);
	screen = DefaultScreen(display);
	root = RootWindow(display, screen);

	//XCreateSimpleWindow(display, root,
		//0, 0, 30, 100, 1,
		//BlackPixel(display, screen),
		//WhitePixel(display, screen));

	//MainLoop();

}

int windowmanager::mainloop()
{
	//XEvent xev;
	//for (;;)
	//{
		//XNextEvent(display, &xev);
		//switch (xev.type)
		//{
			//case CreateNotify:
			//default:
			//XKillClient(display, xev.xcreatewindow.window);
		
		//};
	
	//}
				
}

void windowmanager::gettree()
{
	Window root_return, parent_return, *children;
	unsigned int n;
	XQueryTree(display, root, &root_return, &parent_return, &children, &n);

	//aux = workspaces->focus
  for (int i = 0; i < n ; i++)
	{
//		children
	}

}	
