//Khartikova
#include <X11/cursorfont.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xmd.h>

#define RIGHT 1
#define LEFT 2
#define clockwise 2
#define counterclockwise 1

template <class filler>
class arch
{
	arch* right;
	arch* left;
	filler* object;
public:
	arch(const filler* stuff);
	~arch();
	arch<filler>* next();
	arch<filler>* prev();
	arch<filler>* move(int dir); // сдвигает объект в колесе
private:
  arch();// запрещено создавать пустые арки
};

template<class filler>
class wheel 
{
	int count;
  arch<filler>* focus;
public:
	wheel ();
	~wheel ();
	void rotate(int dir); // сдвигает все окна
	void operator+(arch<filler>* obj);
	void operator-(arch<filler>* obj);
	arch<filler>* ch_focus(int dir);
};

class window 
{
  Window w;
	char *name;
	int x;
	int y;
	int width;
	int height;
public:
	window ();
	~window ();
};

template<>
class wheel<window>
{
	public:
		void checktree(Window* row);
};


class group : public wheel<window>, public window
{
public:
	group ();
	~group ();
	//приведение типов group 2 window
};

class workspace  
{
  wheel<window> windows;	
public:
	workspace ();
	~workspace ();
};
