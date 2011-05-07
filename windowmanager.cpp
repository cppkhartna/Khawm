//Khartikova
//
#include "khawm.hpp"
#include "windowmanager.hpp"
#include "config.hpp"
#include <iostream>

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

	Loop();

}

void windowmanager::update_focus()
{
		if (current->me() != 0)
			current->me()->update_focus();
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
		gettree();
		//current->tile(display, 1, *coord);


		XNextEvent(display, &xev);
		cout << 3;
		switch (xev.type)
		{
			case KeyPress:
				KeyEvents(&xev);
			break;
		}

		update_focus();
	
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
				break;
		}	
		case XK_Right:
		{
			current++;
			break;
		}
		case XK_Left:
		{
			current--;
			break;
		}
		case XK_Page_Up:
		{
			workspaces++;
			current = workspaces->me()->windows();
			break;
		}
		case XK_Page_Down:
		{
			workspaces--;
			current = workspaces->me()->windows();
			break;
		}
		case XK_Home:
		{
			--current;
			break;
		}
		case XK_End:
		{
			++current;
			break;
		}
		default:
		{
			for (int j = 0; j < key_number; j++)
			{
				if (ks == keyboard[j].key)
				{
					if (!fork())
							execlp(keyboard[j].cmd, keyboard[j].cmd, (char*) 0);
					else break;
				}
			}
		}
	}

}

void windowmanager::gettree()
{
	Window root_return, parent_return, *children, *save_children_of_uganda;
	unsigned int n;
	unsigned int i;
	//int j;
	//bool flag;
	XQueryTree(display, root, &root_return, &parent_return, &children, &n);
	save_children_of_uganda = children;
	for (i = 0; i < n ; i++)
	{
		//flag = false;
		//for (j = 0; j < ndesktops; j++)
		//{
			//if (workspaces[j].find(children))
					//flag = true;
		//}
		//if (!flag)
			current += (*children);
		children--;
	}
	children = save_children_of_uganda;
	XFree(children);
}	
