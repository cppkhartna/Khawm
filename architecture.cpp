//Khartikova
#include "khawm.hpp"
#include "architecture.hpp"
#include "bar.hpp"
#include <cstring>

const int max_node = 20;
unsigned long arr[max_node]; 
int node_num = 0;

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
		focus->next->prev = aux;
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
	
	if (!count)
		return 0;
	arch* aux;
	aux = master;	

	for (unsigned int j = 0; j < i; j++) 
	{
		aux = master->next;	
	}
	//focus = aux;
	return aux->object;
}

filler* wheel::be(int i)
{
	return (i == 1 ? master->object: master->next->object);
}

filler* wheel::me()
{
	if (count != 0)
		return focus->object;
	else return 0;
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
	int h = coord.h;
	int w = coord.w;
	int x = coord.x;
	int y = coord.y;

	arch* aux = master;

	if (count >= 5)
	{
		master->object->tile(display, layout, 
					geom(x, y, (int)(0.5*w), h));	
		
		for (i = 0; i < count - 1; i++) 
		{
				aux = aux->next;
				aux->object->tile(display, layout,
					geom((int) ((double) x + w*0.5), 
									y + (int) (i * ( h * ((double) 1/(count-1) ))), 
									(int) ((double) 0.5*w), 
								(int) ((double) ((double) h/(count-1) ))));
		}
	}	
	else
	{
		for (i = 0; i < count; i++)
		{
			aux->object->tile(display, layout,
						geom((int) (x + w*bar[count][layout][i][0]), 
								 (int) (y + h*bar[count][layout][i][1]),
								 (int) (w*bar[count][layout][i][2]),
								 (int) (h*bar[count][layout][i][3])	));

			aux = aux->next;
		}
	}	
		//if (count > 0)
						//aux->object->tile(display, layout,
										//geom(0,0,200,200)
										//);
		//if (count > 1)
		//{
		//aux = aux->next;
		//aux->object->tile(display, layout,
										//geom(250,0,100,100)
										//);
		//}
		//if (count > 2)
		//{
		//aux = aux->next;
		//aux->object->tile(display, layout,
										//geom(400,0,100,100)
										//);
		//}
	//}
}

void wheel::suicide()
{
	for (int i = 0; i < count; i++)
	{
					me()->suicide();
					delete (-(*this));
	}
}

//базовый класс filler
void filler::make_me_your_master(wheel* please)
{
	please->swap(*please);
}

//класс window
window::window(Display* disp, Window win)
{
	using namespace std; //memcpy problem
	
	char* returned;
	w = win;
	display = disp;
	if (XFetchName(display, win, &returned))
	{
		name = new char[strlen(returned)+1];
		strcpy(name, returned);
		XFree(returned);
	}
	else 
	{
		name = new char[8];
	  strcpy(name, "NO_NAME");
	}
}

window::~window()
{
	w = 0;
	delete[] name;
}

void window::tile(Display* display, int layout, geom coord) 
{
	XMoveResizeWindow(display, w, coord.x, coord.y, coord.w, coord.h);	
}

void window::hide()
{
	XUnmapWindow(display, w);
}

void window::show()
{
	XMapWindow(display, w);
}

void window::suicide()
{
	XKillClient(display, w);
}

void window::update_focus()
{
	XSetInputFocus(display, w, RevertToPointerRoot, CurrentTime);
//RevertToNone
}

bool window::find(Window win)
{
	return (w == win);
}

bool wheel::find(Window win)
{
	arch* aux = master;
	bool q = false;
	do
		if (aux != 0)
		{
			if ((q = aux->object->find(win)) == true) 
			{
				aux->found = true;
				break;
			}
			aux = aux->next;
		}	
	while (aux != master);	
	return q;
}

void wheel::clean()
{
	arch* aux = this->master;
	arch* next;
	int save_count(count);

	for (int i = 0; i < save_count; i++)
	{ 
		next = aux->next;
		if (aux->found == false)		
		{
				focus = aux;
				//me()->suicide();
				delete (-(*this));
		}
		aux = next;
	}

}

void wheel::fake()
{
	arch* aux = master;
	if (master != 0)
	do
	{
		aux->found = false;
		aux = aux->next;
	}
	while (aux != master);
}

void wheel::show()
{
	for (int i = 0; i < count; i++)
	{
		me()->show();
		focus = focus->next;
	}	
}
void wheel::hide()
{
	for (int i = 0; i < count; i++)
	{
		me()->hide();
		focus = focus->next;
	}	
}

void wheel::node()
{
	arch* aux = master;
	node_num = 0;
	do
		if (aux != 0)
		{
			arr[node_num] = aux->object->get();
			node_num++;
			if (node_num >= max_node)
				break;
			aux = aux->next;
		}	
	while (aux != master);	

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
