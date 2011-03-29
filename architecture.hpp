//Khartikova
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
	arch<filler>* move(int dir); // сдвигает объект в колесе
	void rotate(int dir); // сдвигает все окна
	void destruct(); // удаляет арку из колеса 
private:
  arch();// запрещено создавать пустые арки
};

template<class filler>
class wheel 
{
  arch<filler>* master;
  arch<filler>* focus;
public:
	wheel ();
	~wheel ();
};

class window 
{
public:
	window ();
	~window ();
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

class cube 
{
	wheel<workspace> workspaces;
public:
	cube ();
	~cube ();
};
