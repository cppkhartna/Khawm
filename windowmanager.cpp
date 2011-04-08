//Khartikova
#include "khawm.hpp"
#include "windowmanager.hpp"

windowmanager::windowmanager()
{
	display = XOpenDisplay(0);
	screen = DefaultScreen(display);
	root = RootWindow(display, screen);
	XDisplayWidth(display, w_size);
	XDisplayHeight(display, h_size);

	//XCreateSimpleWindow(display, root,
		//0, 0, 30, 100, 1,
		//BlackPixel(display, screen),
		//WhitePixel(display, screen));

	//MainLoop();

}

int windowmanager::mainloop()
{
	XEvent xev;
	for (;;)
	{
		//gettree();


		XGrabKey(display
						, XKeysymToKeycode(display, XStringToKeysym("C"))
						, Mod4Mask, root, True, GrabModeAsync, GrabModeAsync);


		XNextEvent(display, &xev);
		switch (xev.type)
		{
			case KeyPress:
				handleKeyEvents(&xev);
			break;
			default:
			XKillClient(display, xev.xcreatewindow.window);
		
		};
	
	}
				
}

void windowmanager::handleKeyEvents(XEvent *xev)
{
  KeySym ks;
	ks = XKeycodeToKeysym(display, xev->xkey.keycode,0);
	
	//switch (ks)
	//{
		//case 
	//}

}



//void windowmanager::gettree()
//{
	//Window root_return, parent_return, *children;
	//unsigned int n;
	//XQueryTree(display, root, &root_return, &parent_return, &children, &n);

	//aux = workspaces->focus
  //for (int i = 0; i < n ; i++)
	//{
		//children
	//}

//}	
