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
		current->fake();

		gettree();

		current->clean();

		current->tile(display, 0, *coord);

		update_focus();

		if (XCheckTypedEvent(display, KeyPress, &xev))
						KeyEvents(&xev);

	}
				
	return 0;
}

void windowmanager::KeyEvents(XEvent *xev)
{
	KeySym ks;
	ks = XKeycodeToKeysym(display, xev->xkey.keycode,0);
	static int x = 0;

	switch (ks)
	{
		case XK_c:
		{
			//current->node();
			current->me()->suicide();
			delete	(-(*current));

			//current->node();
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

			workspaces++;
			current = workspaces->me()->windows();

			current->show();
			break;
		}
		case XK_Down:
		{
			current->hide();

			workspaces--;
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
			x+=5;
			//(*current)++;
			current->be(2)->tile(display, 0, geom(0, 0, 100+x, 100+x));
			break;
		}
		case XK_minus:
		{
			x+=5;
			//(*current)--;
			current->be(1)->tile(display, 0, geom(0, 0, 200+x, 200+x));
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
