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

	Loop();

}

void windowmanager::update_focus(Display* display, Window w)
{
	XSetInputFocus(display, w, RevertToNone, CurrentTime);
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


		XNextEvent(display, &xev);
		switch (xev.type)
		{
			case KeyPress:
				KeyEvents(&xev);
			break;
		}
		window* a;
		workspaces+=a;
		workspaces()->windows();
		
		group* c;
		c = (group*) workspaces()->windows();
		c->windows();

	
	}
				
}

void windowmanager::KeyEvents(XEvent *xev)
{
  //KeySym ks;
	//ks = XKeycodeToKeysym(display, xev->xkey.keycode,0);
	
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
