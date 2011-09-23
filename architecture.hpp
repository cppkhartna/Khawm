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
	virtual void update_focus() = 0;	
	virtual void suicide() = 0;
	virtual bool find(Window win) = 0;

	virtual Window get() = 0;
	virtual int layout(int flag = -1) = 0;
};

class wheel : public filler 
{
	struct arch
	{
		arch* next;
		arch* prev;
		filler* object;
	  bool found;
		arch(filler* obj) 
		{
			next = this;
			prev = this;
			object = obj;			
			found = true;
		};
	};
    
	void move(int dir);
				
	int count;
  arch* master;
  arch* focus;

public:
	wheel ();
	virtual ~wheel ();
	void rotate(int dir); // сдвигает все окна
	wheel* operator+=(filler* obj); // добавляет объект в колесо
	filler* operator-(); // достаёт объект фокуса из колеса
	
	void operator++(); //фокусирует дугу справа
	void operator--(); //фокусирует дугу слева
	filler* operator[](unsigned int i); // фокусирует конкретную дугу, считая от мастера
	filler* me(); // доступ к объекту фокуса
	operator int(); //возвращает номер фокуса
	
	void operator++(int); //меняет местами фокус и правую дугу
	void operator--(int); //меняет местами фокус и левую дугу

	void swap(unsigned int first, unsigned int second);//меняет местами две дуги
	void tile(Display* display, int layout, geom coord); 

	void suicide();

	bool find(Window win);
	void clean();
	void fake();

	void show();
	void hide();
	filler* be(int i);

	void node();

private:
	virtual wheel* windows(){return 0;};
	virtual void update_focus(){};	
	Window get(){return 0;};
	int layout(int flag = -1){return 0;};
};

class window : public filler 
{
  Window w;
	Display* display;
	char *name;

public:

	window (Display* disp, Window win);
	~window ();
	
	void make_me_your_master(wheel* please);
	friend void wheel::tile(Display* display, int layout, geom coord); 

	void show();
	void hide();

	virtual void tile(Display* display, int layout, geom coord); 
	void suicide();
	void update_focus();	
	bool find(Window win);

	Window get();

private:
	window() {};
	virtual wheel* windows() {return 0;}; 
	int layout(int flag = -1){return 0;};
};

class workspace : public filler
{
	char* name;
	wheel* wheel_of_windows;
	int def_layout;
public:
	workspace (const char* d_name, int d_layout);
	~workspace ();

  wheel* windows();	
	
	void make_me_your_master(wheel* please);
	int layout(int flag = -1);

private:
  void tile(Display* display, int layout, geom coord){};
	void show() {};
	void hide() {};
	void update_focus() {};	
	void suicide() {};
	bool find(Window win) {return 0;};
	Window get() {return 0;};
};
