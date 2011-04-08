//Khartikova
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
  arch<filler>* master;
  arch<filler>* focus;
public:
	wheel ();
	~wheel ();
	void rotate(int dir); // сдвигает все окна
	void operator+(arch<filler>* obj); // добавляет дугу в колесо
	void operator-(arch<filler>* obj); // удаляет дугу из колеса
	
	arch<filler>& operator++(); //фокусирует окно справа
	arch<filler>& operator--(); //фокусирует окно слева
	arch<filler>& operator[](unsigned int i); // фокусирует конкретное окно, считая от мастера
	arch<filler>& operator$(); // доступ к фокусу
	
	arch<filler>& operator++(int); //меняет местами фокус и правую дугу
	arch<filler>& operator--(int); //меняет местами фокус и левую дугу

	virtual void tile(int layout, int area_h, int area_w);
	//void checktree(Window* row, int n);
};

class window 
{
  Window* w;
	char *name;
	int x;
	int y;
	int width;
	int height;
public:
	window (Window* obj);
	~window ();
	void make_me_your_master(wheel<window>* please);
	void set(unsigned int v_x, unsigned int v_y, unsigned int v_w, unsigned int v_h);
	void show();
	void hide();
	virtual void tile();
};

class group : public wheel<window>, public window
{
	int x;
	int y;
	int width;
	int height;
	
	int count;
  arch<window>* master;
  arch<window>* focus;
public:
	group ();
	~group ();
	//приведение типов group 2 window
	virtual void tile();
};

class workspace  
{
  wheel<window>* windows;	
	char* name;
public:
	workspace ();
	~workspace ();
};
