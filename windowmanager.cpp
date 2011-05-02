//Khartikova
//
#include "khawm.hpp"
#include "windowmanager.hpp"
#include "config.hpp"

windowmanager::windowmanager()
{
	display = XOpenDisplay(0);
	screen = DefaultScreen(display);
	root = RootWindow(display, screen);
	coord = new geom(0, 0, XDisplayWidth(display, screen), XDisplayHeight(display, screen));

	workspaces = new wheel;

	for (int i = 0; i < ndesktops; i++)
	{
		*workspaces += (workspace*)(new workspace);		
	}

	current = workspaces->me()->windows();

	//Loop();

}

void windowmanager::update_focus(Display* display, Window w)
{
	XSetInputFocus(display, w, RevertToNone, CurrentTime);
}


windowmanager::~windowmanager()
{
	delete workspaces;
	delete coord;
	XCloseDisplay(display);
}

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

		current->tile(display, 1, *coord);

		XNextEvent(display, &xev);
		switch (xev.type)
		{
			case KeyPress:
				KeyEvents(&xev);
			break;
		}
	
	}
				
	return 0;
}

void windowmanager::KeyEvents(XEvent *xev)
{
	KeySym ks;
	ks = XKeycodeToKeysym(display, xev->xkey.keycode,0);

	switch (ks)
	{
		case XK_c:
		{
				current->me()->suicide();
				delete (-(*current));
		}	
		default:
		{
			//if (fork) 
				//execvp()
		}
	}

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
