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
		*workspaces += (workspace*)(new workspace(i));		
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
		current->fake();

		gettree();

		current->clean();

		current->tile(display, workspaces->me()->layout(), *coord);

		update_focus();

		//whole lotta dirty hacks
		//though have to press smthing to make it work every time
	
		do
		{
			XNextEvent(display, &xev);
			if (xev.type == KeyPress) 
							XPutBackEvent(display, &xev);
		  while (XCheckTypedEvent(display, KeyPress, &xev))
			{
				KeyEvents(&xev); 
			}

		}
		while (XPending(display));

	}
				
	return 0;
}

void windowmanager::KeyEvents(XEvent *xev)
{
	KeySym ks;
	ks = XKeycodeToKeysym(display, xev->xkey.keycode,0);
	XWindowAttributes xattr;

	switch (ks)
	{
		case XK_c:
		{
			current->me()->suicide();
			delete	(-(*current));
			break;
		}	
		case XK_Right:
		{
			++(*current);
			break;
		}
		case XK_Left:
		{
			--(*current);
			break;
		}
		case XK_Up:
		{
			current->hide();

			++(*workspaces);
			current = workspaces->me()->windows();

			current->show();
			break;
		}
		case XK_Down:
		{
			current->hide();

			--(*workspaces);
			current = workspaces->me()->windows();

			current->show();
			break;
		}
		case XK_Home:
		{
			(*current)++;
			break;
		}
		case XK_End:
		{
			(*current)--;
			break;
		}
		case XK_r:
		{
			current->rotate(RIGHT);
			break;
		}
		case XK_l:
		{
			current->rotate(LEFT);
			break;
		}
		case XK_equal:
		{
			XGetWindowAttributes(display, current->me()->get(), &xattr);		
			current->me()->tile(display, 0, 
				geom(xattr.x, xattr.y, xattr.width + 5,xattr.height+5));
			break;
		}
		case XK_minus:
		{
			XGetWindowAttributes(display, current->me()->get(), &xattr);		
			current->me()->tile(display, 0, 
				geom(xattr.x, xattr.y, xattr.width - 5,xattr.height-5));
			break;
		}
		default:
		{
			for (int j = 0; j < key_number; j++)
			{
				if (ks == keyboard[j].key)
				{
					if (*(keyboard[j].cmd) != ':') 
						if (!fork())
							execlp(keyboard[j].cmd, keyboard[j].cmd, (char*) 0);
						else break; 
					else break;
				}
			}
		}
	}

}

void windowmanager::gettree()
{
	using namespace std;
	Window root_return, parent_return, *children, *save_children_of_uganda;
	unsigned int n;
	unsigned int i;
	XWindowAttributes xattr;

	XQueryTree(display, root, &root_return, &parent_return, &children, &n);
	save_children_of_uganda = children;
	for (i = 0; i < n ; i++)
	{
		if (XGetWindowAttributes(display, children[i], &xattr) != 0) 
			if (!xattr.override_redirect && xattr.map_state == IsViewable)
				if (!current->find(children[i]))
					current->operator+=((window*)(new window(display, children[i])));
	}

	current->node();
	children = save_children_of_uganda;
	XFree(children);
}	
