//Khartikova

#include"architecture.hpp"

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
	count  = 0;
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
  focus = obj;
	count++;
}

template <class filler>
void wheel<filler>::operator-(arch<filler>* obj)
{
	count--;

	if (obj == focus)
		focus = focus->next();

	if (count > 0)
  {
		obj->prev()->next() = obj->next();
		obj->next()->prev() = obj->prev();
	}
	else 
	{
		focus = 0;
		count = 0;
	}
	//разобраться с удалением арча
}

