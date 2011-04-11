//Khartikova
template<class filler>
class wheel 
{
	struct arch
	{
		arch* next;
		arch* prev;
		filler* object;
		arch(filler* obj) 
		{
			next = this;
			prev = this;
			object = obj;			
		};
	};
				
	int count;
  arch* master;
  arch* focus;

  void move(int dir);

public:
	wheel ();
	~wheel ();
	void rotate(int dir); // сдвигает все окна
	void operator+(filler* obj); // добавляет объект в колесо
	filler* operator-(); // достаёт объект из колеса
	
	void operator++(); //фокусирует дугу справа
	void operator--(); //фокусирует дугу слева
	filler& operator[](unsigned int i); // фокусирует конкретную дугу, считая от мастера
	filler& operator()(); // доступ к объекту фокуса
	operator int(); //возвращает номер фокуса
	
	void operator++(int); //меняет местами фокус и правую дугу
	void operator--(int); //меняет местами фокус и левую дугу

	void swap(unsigned int first, unsigned int second);//меняет местами две дуги
	void update_focus(Display* display);
	//virtual void tile(int layout, int area_h, int area_w);
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
	window (/*Window* obj*/) {};
	~window () {};
	void make_me_your_master(wheel<window>* please);
	void set(unsigned int v_x, unsigned int v_y, unsigned int v_w, unsigned int v_h);
	void show();
	void hide();
	//virtual void tile();
};

//class group : public wheel<window>, public window
//{
	//int x;
	//int y;
	//int width;
	//int height;
	
	//int count;
  //arch* master;
  //arch* focus;
//public:
	//group ();
	//~group ();
	//приведение типов group 2 window
	//virtual void tile();
//};

class workspace  
{
	char* name;
public:
  wheel<window>* windows;	
	workspace ();
	~workspace ();
};

