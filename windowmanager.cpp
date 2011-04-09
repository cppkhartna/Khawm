//Khartikova
#include "khawm.hpp"
#include "windowmanager.hpp"
#include "keyboard.hpp"

windowmanager::windowmanager()
{
	display = XOpenDisplay(0);
	screen = DefaultScreen(display);
	root = RootWindow(display, screen);
	w_size = XDisplayWidth(display, screen);
	h_size = XDisplayHeight(display, screen);

	//XCreateSimpleWindow(display, root,
		//0, 0, 30, 100, 1,
		//BlackPixel(display, screen),
		//WhitePixel(display, screen));

	//MainLoop();

}

int windowmanager::MainLoop()
{
	XEvent xev;

	for (int i = 0; i < key_number; i++) 
	{
		XGrabKey(display
				, XKeysymToKeycode(display, keyboard[i].key) 
				, keyboard[i].mask, root, True, GrabModeAsync, GrabModeAsync);
	}

	for (;;)
	{
		//gettree();

    workspaces()->windows.update_focus(display);


		XNextEvent(display, &xev);
		switch (xev.type)
		{
			case KeyPress:
				handleKeyEvents(&xev);
			break;
		}
	
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

void windowmanager::Settings()
{

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
