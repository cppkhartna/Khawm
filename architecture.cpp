//Khartikova

#include"architecture.hpp"

template<class filler>
wheel<filler>::wheel()
{
	master = 0; 
	focus  = 0; 
}

template <class filler>
arch<filler>::arch(const filler* stuff)
{
	object = stuff;
	right = 0;
	left = 0;
};
template <class filler>
void arch<filler>::destruct()
{
  try		
	{
	  if (!object)
		{
		 	object->ptr_count--;
			if (object->ptr_count == 0) throw 1; //обработчик
		}
		object = 0;
	}
	catch(...)
	{
		//обработчик
	}			
		
	if (!right)
	{
		this->right->left = this->left;
	}
	if (!left)
	{
		this->left->right = this->right;
	}
	
	right = 0;
	left = 0;
};

template<class filler>
arch<filler>* arch<filler>::move(int dir)
{
	if (dir == RIGHT)
		if (!right)
			{
				filler* aux = this->object;
			  this->object = this->right->object;
				this->right->object = aux;		
				return this->right;
			}
  if (dir == LEFT)
		if (!left)
			{
				filler* aux = this->object;
			  this->object = this->left->object;
				this->left->object = aux;		
				return this->right;
			}
	return this;
}
template<class filler>
void arch<filler>::rotate(int dir)
{
	arch<filler>* aux;
	aux = this;
	do
		aux = move(dir);
	while (aux != this);
}	
