//Khartikova
#include "khawm.hpp"
#include "windowmanager.hpp"
#include "config.hpp"

windowmanager::windowmanager()
{
	display = XOpenDisplay(0);
	screen = DefaultScreen(display);
	root = RootWindow(display, screen);
	w_size = XDisplayWidth(display, screen);
	h_size = XDisplayHeight(display, screen);
	//workspaces = new wheel<workspace>;

	//XCreateSimpleWindow(display, root,
		//0, 0, 30, 100, 1,
		//BlackPixel(display, screen),
		//WhitePixel(display, screen));

	//Loop();

}

//windowmanager::~windowmanager()
//{
//}

int windowmanager::Loop()
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

    //workspaces()->windows.update_focus(display);
		//((*workspaces)()).windows->update_focus(display);
						//.windows.update_focus(display);

		workspaces.rotate(2);
		workspaces[workspaces].windows->update_focus(display);
		XNextEvent(display, &xev);
		switch (xev.type)
		{
			case KeyPress:
				KeyEvents(&xev);
			break;
		}
	
	}
				
}

void windowmanager::KeyEvents(XEvent *xev)
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
