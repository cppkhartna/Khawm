//Khartikova

struct geom
{
	geom(unsigned v_x, unsigned v_y, unsigned v_w, unsigned v_h)
	{
		x = v_x;
		y = v_y;
		w = v_w;
		h = v_h;
	}
	unsigned int x;
	unsigned int y;
	unsigned int w;
	unsigned int h;
};

class layout 
{
public:
	layout ();
	~layout ();
};

class wheel;

class filler 
{
public:
	filler () {};
	virtual ~filler () {};
	void make_me_your_master(wheel* please);
	
	virtual wheel* windows() = 0;
  virtual	void tile(Display* display, int layout, geom coord) = 0;
	virtual void show() = 0;
	virtual void hide() = 0;
};

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
    
	void move(int dir);
				
	int count;
	int shown;
  arch* master;
  arch* focus;

public:
	wheel ();
	virtual ~wheel ();
	void rotate(int dir); // сдвигает все окна
	wheel* operator+=(filler* obj); // добавляет объект в колесо
	void operator-(int); //  вычитает число свежесвёрнутых окон 
	void operator+(int); // добавляет число свежесвёрнутых окон 
	filler* operator-(); // достаёт объект фокуса из колеса
	
	void operator++(); //фокусирует дугу справа
	void operator--(); //фокусирует дугу слева
	filler* operator[](unsigned int i); // фокусирует конкретную дугу, считая от мастера
	filler& operator()(); // доступ к объекту фокуса
	operator int(); //возвращает номер фокуса
	
	void operator++(int); //меняет местами фокус и правую дугу
	void operator--(int); //меняет местами фокус и левую дугу

	void swap(unsigned int first, unsigned int second);//меняет местами две дуги
	void tile(Display* display, int layout, geom coord); 
	//void checktree(Window* row, int n);

};

class window : public filler 
{
  Window* w;
	Display* display;
	char *name;
	bool is_shown;

public:
	window (Display* disp, Window* win);
	~window ();
	
	void make_me_your_master(wheel* please);
	friend void wheel::tile(Display* display, int layout, geom coord); 

	void show();
	void hide();

	virtual void tile(int layout, geom coord); 

private:
	window() {};
	virtual wheel* windows() {}; 
};

class group : public window
{
	bool is_shown;
	wheel* wheel_of_windows;
public:
 	group ();
	~group ();
	virtual wheel* windows() {return wheel_of_windows;};
	void make_me_your_master(wheel* please);

	void show() {};
	void hide() {};
	void tile(Display* display, int layout, geom coord); 
};

class workspace : public filler
{
	char* name;
  wheel* wheel_of_windows;	
public:
	workspace ();
	~workspace ();
	
	void make_me_your_master(wheel* please);
	virtual wheel* windows() {return wheel_of_windows;};
	void tile(Display* display, int layout, geom coord);

private:
	void show() {};
	void hide() {};
};
