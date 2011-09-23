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
		*workspaces += (workspace*)(new workspace(desktop_names[i],desktop_def_layouts[i]));		
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
	for (int i = 0; i < key_number; i++) 
	{
		XUngrabKey(display
				, XKeysymToKeycode(display, keyboard[i].key) 
				, keyboard[i].mask, root);
	}
	XDestroyWindow(display, root);
	XCloseDisplay(display);

	delete workspaces;
	delete coord;
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

	int x;

	switch (ks)
	{
		case XK_c:
		{
			if (current->me() != 0)
			{
				current->me()->suicide();
				delete	(-(*current));
			}
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
		case XK_t:
		{
			current->rotate(LEFT);
			break;
		}
		case XK_h:
		{
			change_focus_size(-0.05,0);
			break;
		}
		case XK_l:
		{
			change_focus_size(+0.05,0);
			break;
		}
		case XK_j:
		{
			change_focus_size(0,+0.05);
			break;
		}
		case XK_k:
		{
			change_focus_size(0,-0.05);
			break;
		}
		case XK_equal:
		{
			change_focus_size(0.05,0.05);
			break;
		}
		case XK_minus:
		{
			change_focus_size(-0.05,-0.05);
			break;
		}
		case XK_a:
		{
			move_focus(-0.05,0);
			break;
		}
		case XK_d:
		{
			move_focus(+0.05,0);
			break;
		}
		case XK_w:
		{
			move_focus(0, -0.05);
			break;
		}
		case XK_s:
		{
			move_focus(0, +0.05);
			break;
		}
		case XK_m:
		{
			if (current->me() != 0)
				current->me()->make_me_your_master(current);
			break;
		}
		case XK_Tab:
		{
			x = workspaces->me()->layout();
			x++;
			x%=(FLOAT+1);
			workspaces->me()->layout(x);
			break;
		}
		case XK_q:
		{
			exit(0);
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

	children = save_children_of_uganda;
	XFree(children);
}	

void windowmanager::change_focus_size(double x, double y)
{
	if (workspaces->me()->layout() == FLOAT && current->me() != 0)
	{
		XWindowAttributes xattr;
		XGetWindowAttributes(display, current->me()->get(), &xattr);		
		if ((xattr.width >= 20) && (xattr.height >= 20))
			current->me()->tile(display, 0, 
				geom(xattr.x, xattr.y, 
						xattr.width  + (int) (x*(double)coord->w),
						xattr.height + (int) (y*(double)coord->h)));
	}
}

void windowmanager::move_focus(double x, double y)
{
	if (workspaces->me()->layout() == FLOAT && current->me() != 0)
	{	
		XWindowAttributes xattr;
		XGetWindowAttributes(display, current->me()->get(), &xattr);		
		current->me()->tile(display, 0, 
		geom(xattr.x + (int) (x*(double)coord->w), 
					xattr.y + (int) (y*(double)coord->h), 
					xattr.width,
					xattr.height));
	}
}

