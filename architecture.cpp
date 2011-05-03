//Khartikova
#include "khawm.hpp"
#include "architecture.hpp"
#include "bar.hpp"
#include <cstring>

// класс wheel
//
void wheel::move(int dir)
{
	filler* aux;
	if (dir == RIGHT)
	{
			aux = focus->next->object;
			focus->next->object = focus->object;
			focus->object = aux;
     	focus = focus->next;
  } 
	else if (dir == LEFT)
	{
			aux = focus->prev->object;
			focus->prev->object = focus->object;
  		focus->object = aux;
			focus = focus->prev;
	}
}

wheel::wheel()
{
	focus  = 0; 
	master = 0;
	count  = 0;
	shown  = 0;
}

wheel::~wheel()
{
	if (focus)
	{
		int save_count(count);
		for (int i = 0; i < save_count; i++)
		{
			delete (-(*this));
		}
	}
}

void wheel::rotate(int dir)
{
	if (focus)
	{
		for (int i = 0; i < count; i++)
		{
			move(dir);
		}
	}
}

wheel* wheel::operator+=(filler* obj)
{
	arch* aux;
	aux = new arch(obj);
	
	if (count)
	{
		aux->next = focus->next;
		focus->next = aux;
		aux->prev = focus;
	}
	else master = aux;
	focus = aux;
	count++;
	return this;
}

filler* wheel::operator-()
{
	count--;

	filler* aux;
	aux = focus->object;

	arch* arch_aux;
	arch_aux = focus;
	
	if (focus == master)
		master = master->next;

	if (count > 0)
	{
		focus->prev->next = focus->next;
		focus->next->prev = focus->prev;
		focus = focus->next;
	}
	else 
	{
		focus  = 0;
		master = 0;
		count  = 0;
	}
	delete arch_aux;
	return aux;
}

void wheel::operator-(int x)
{
	shown -= x;
}

void wheel::operator+(int x)
{
	shown += x;
}

void wheel::operator ++()
{
	focus = focus->next;
}

void wheel::operator --()
{
	focus = focus->prev;
}

filler* wheel::operator [](unsigned int i)
{
//	отсчёт ведётся вправо
	arch* aux;
	aux = master;	
	for (unsigned int j = 0; j < i; j++) 
	{
		aux = master->next;	
	}
	focus = aux;
	return focus->object;
}

filler* wheel::me()
{
	return focus->object;
}

wheel::operator int()
{
	int j = 0;

	arch* aux;
	aux = focus;
	
	while (aux != master)
	{
		aux = aux->prev;
		j++;
	}	

	return j;

}

void wheel::operator ++(int)
{
	move(RIGHT);
}

void wheel::operator --(int)
{
	move(LEFT);
}

void wheel::swap(unsigned int first, unsigned int second = 0)
{
	filler* aux;
	aux = (*this)[first];
	*(*this)[first]   = *(*this)[second];
	*(*this)[second]  = *aux;	
}//Was ist das? Check it later!

void wheel::tile(Display* display, int layout, geom coord) 
{
	int i;
	int h = coord.y2 - coord.y1;
	int w = coord.x2 - coord.x1;

	arch* aux = master;
	if (!master->object->is_shown)
					master->object->show();

	if (shown >= 5)
	{
		master->object->tile(display, layout, 
					geom(coord.x1,coord.y1, (int)(0.5*coord.x2), (int)(coord.y2)));	
		
		for (i = 0; i < shown - 1; i++) 
		{
				aux = aux->next;
				aux->object->tile(display, layout,
					geom((int) i*((double) coord.x1 + w*0.5), 
									coord.y1, 
									coord.x2, 
								(int) (i+1)*((double) coord.y1 + h*(1/(shown-1)))));
		}
	}	
	else
	{
		for (i = 0; i < shown; i++)
		{
			aux->object->tile(display, layout,
						geom((int) coord.x1 + w*bar[shown][layout][i][1], 
								 (int) coord.y1 + h*bar[shown][layout][i][2],
								 (int) coord.x1 + w*bar[shown][layout][i][3],
								 (int) coord.y1 + h*bar[shown][layout][i][4]	));

			aux = aux->next;
		}
	}
}

void wheel::suicide()
{
	for (int i = 0; i < count; i++)
	{
					me()->suicide();
					delete (-(*this));
	}
}

//template<class filler>
//void wheel::checktree(Window* row, int n)
//{		
	//for (int i = 0; i < count; i++)
	//{
		//for (int j = 0; j < n; j++)
		//{
				//u
		//}
		//`<...>`
		//this[i] = 0;	
	//}
	
//}   посмотри потом, может, сделать для перезагрузки, а пока попробуй
	 //Notify

//базовый класс filler
void filler::make_me_your_master(wheel* please)
{
	please->swap(*please);
}

//класс window
window::window(Display* disp, Window* win)
{
	char** returned = 0;
	w = win;
	display = disp;
	if (XFetchName(display, *win, returned))
	{
		name = new char[strlen(*returned)+1];
		strcpy(name, *returned);
	}
	else 
	{
		name = new char[8];
	  strcpy(name, "NO_NAME");
	}
	is_shown = true;
}

window::~window()
{
	w = 0;
	delete[] name;
}

void window::tile(Display* display, int layout, geom coord) 
{
	XMoveResizeWindow(display, *w, coord.x1, coord.y1, coord.x2, coord.y2);		
}

void window::hide()
{
  is_shown = false;
	XUnmapWindow(display, *w);
}

void window::show()
{
	is_shown = true;
	XMapWindow(display, *w);
}

void window::suicide()
{
	XKillClient(display, *w);
}

void window::update_focus()
{
	XSetInputFocus(display, *w, RevertToNone, CurrentTime);
}

bool window::find(Window* win)
{
	return (w == win);
}

bool group::find(Window* win)
{
	return wheel_of_windows->find(win);
}

bool wheel::find(Window* win)
{
	for (int i = 0; i < count; i++)
	{
		if ((*this)[i]->find(win))
			return true;
	}
	return false;
}


void group::suicide()
{
	wheel_of_windows->suicide();
}

void group::update_focus()
{
	//ничего не делать
}


workspace::workspace()
{
	wheel_of_windows = new wheel; 
}

workspace::~workspace()
{
	delete wheel_of_windows; 
}

wheel* workspace::windows() 
{
	return wheel_of_windows;
}
