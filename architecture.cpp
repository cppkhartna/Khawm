//Khartikova
#include "khawm.hpp"
#include "architecture.hpp"

// класс wheel
template <class filler>
void wheel<filler>::move(int dir)
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

template <class filler>
wheel<filler>::wheel()
{
	focus  = 0; 
	master = 0;
	count  = 0;
}

template <class filler>
wheel<filler>::~wheel()
{
	filler* aux;			
	if (!focus)
	{
    for (int i = 0; i < count; i++)
		{
		  aux = -*this;
			delete aux;
		}
	}
}


template <class filler>
void wheel<filler>::rotate(int dir)
{
	if (!focus)
	{
    for (int i = 0; i < count; i++)
		{
		  focus->move(dir);
		}
	}
}

template <class filler>
void wheel<filler>::operator+(filler* obj)
{
	arch* aux;
	aux = new arch(obj);
	
	if (!focus)
  {
		focus->next = aux;
		aux->next = focus->next;
		aux->prev = focus;
		focus->prev = aux;
	}
	else master = aux;
  focus = aux;
	count++;
}

template <class filler>
filler* wheel<filler>::operator-()
{
	count--;

	filler* aux;
	aux = focus->object;
	
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
}

template <class filler>
void wheel<filler>::operator ++()
{
	focus = focus->next;
	return focus;
}

template <class filler>
void wheel<filler>::operator --()
{
	focus = focus->prev;
}

template <class filler>
filler& wheel<filler>::operator [](unsigned int i)
{
	//отсчёт ведётся вправо
	arch* aux;
	aux = master;	
	for (int j = 0; j < i; j++) 
	{
		aux = master->next;	
	}
	focus = aux;
	return focus->object;
}

template <class filler>
filler& wheel<filler>::operator ()()
{
	return focus->object;
}

template <class filler>
wheel<filler>::operator int()
{
  int j = 0;

	arch* aux;
	aux = focus;
	
	while (!aux == master)
	{
		aux = aux->prev;
		j++;
	}	

	return j;

}

template <class filler>
void wheel<filler>::operator ++(int)
{
	focus->move(RIGHT);
}


template <class filler>
void wheel<filler>::operator --(int)
{
	focus->move(LEFT);
}

template <class filler>
void wheel<filler>::swap(unsigned int first, unsigned int second = 0)
{
	filler* aux;
	aux = *this[first];
	*this[first]   = *this[second];
	*this[second]  = aux;	
}

template <class filler>
void wheel<filler>::update_focus(Display* display)
{
	XSetInputFocus(display, focus->object->w, RevertToNone, CurrentTime);
}

//template <class filler>
//void wheel<filler>::tile(int layout, int area_h, int area_w)
//{
	
//}

//template<class filler>
//void wheel<filler>::checktree(Window* row, int n)
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
//    Notify

// класс window
void window::set(unsigned int v_x, unsigned int v_y, unsigned int v_w, unsigned int v_h)
{
  x = v_x;
	y = v_y;
	width  = v_w;
	height = v_w;	
}

//workspace
workspace::workspace()
{
	windows = new wheel<window>;
}
workspace::~workspace()
{
	delete windows;
}

wheel<window> b;
wheel<workspace> a;

