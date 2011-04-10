//Khartikova
#include "khawm.hpp"
#include "architecture.hpp"

// класс arch
template <class filler>
arch<filler>::arch(const filler* stuff)
{
	object = stuff;
	right = this;
	left = this;
};

template <class filler>
arch<filler>* arch<filler>::next()
{
	return this->right;
}

template <class filler>
arch<filler>* arch<filler>::prev()
{
	return this->left;
}

template <class filler>
arch<filler>* arch<filler>::move(int dir)
{
	filler* aux;
	if (dir == RIGHT)
	{
			aux = this->next()->object;
			this->next()->object = this->object;
			this->object = aux;
     	return this->next();
  } 
	else if (dir == LEFT)
	{
			aux = this->prev()->object;
			this->prev()->object = this->object;
  		this->object = aux;
			return this->prev();
	}
}

// класс wheel
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
}


template <class filler>
void wheel<filler>::rotate(int dir)
{
	if (!focus)
	{
		arch<filler>* aux;
  	aux = focus;
    do
		  aux = focus->move(dir);
  	while (aux != focus);
	}
}

template <class filler>
void wheel<filler>::operator+(arch<filler>* obj)
{
	if (!focus)
  {
		focus->next() = obj;
		obj->next() = focus->next();
		obj->prev() = focus;
		focus->prev() = obj;
	}
	else master = obj;
  focus = obj;
	count++;
}

template <class filler>
void wheel<filler>::operator-(arch<filler>* obj)
{
	count--;

	if (obj == focus)
		focus = focus->next();
	
	if (obj == master)
		master = master->next();

	if (count > 0)
  {
		obj->prev()->next() = obj->next();
		obj->next()->prev() = obj->prev();
	}
	else 
	{
		focus  = 0;
		master = 0;
		count  = 0;
	}
	//разобраться с удалением арча
}

template <class filler>
arch<filler>& wheel<filler>::operator ++()
{
	focus = focus->next();
	return focus;
}

template <class filler>
arch<filler>& wheel<filler>::operator --()
{
	focus = focus->prev();
	return focus;
}

template <class filler>
arch<filler>& wheel<filler>::operator [](unsigned int i)
{
	//отсчёт ведётся вправо
	arch<filler>* aux;
	aux = master;	
	for (int j = 0; j < i; j++) 
	{
		aux = master->next();	
	}
	return aux;
}

template <class filler>
filler* wheel<filler>::operator()()
{
	return focus->object;
}

template <class filler>
arch<filler>& wheel<filler>::operator ++(int)
{
	return focus->move(RIGHT);
}


template <class filler>
arch<filler>& wheel<filler>::operator --(int)
{
	return focus->move(LEFT);
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

wheel<workspace> a;
wheel<window> b;
