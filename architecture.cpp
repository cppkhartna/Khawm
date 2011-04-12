//Khartikova
#include "khawm.hpp"
#include "architecture.hpp"

// класс wheel

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



void wheel::rotate(int dir)
{
	if (!focus)
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


filler* wheel::operator-()
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
	return aux;
}


//filler* wheel::operator-(unsigned int num)
//{
	//count--;
	//arch* aux;
	//filler* filler_aux;

	//aux = (*this)[num];
	//filler_aux = aux->object;
	
	//if (aux == master)
		//master = master->next;


	//if (count > 0)
	//{
		//aux->prev->next = aux->next;
		//aux->next->prev = aux->prev;
		//aux = aux->next;
	//}
	//else 
	//{
		//focus  = 0;
		//master = 0;
		//count  = 0;
	//}
	//return filler_aux;
//}



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
	for (int j = 0; j < i; j++) 
	{
		aux = master->next;	
	}
	focus = aux;
	return focus->object;
}


filler* wheel::operator ()()
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


void wheel::tile(int layout, unsigned int v_x, unsigned int v_y, unsigned int v_w, unsigned int v_h)
{
	
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

//класс window
void window::tile(int layout, unsigned int v_x, unsigned int v_y, unsigned int v_w, unsigned int v_h)
{
	//x = v_x;
	//y = v_y;
	//width  = v_w;
	//height = v_w;	
}
