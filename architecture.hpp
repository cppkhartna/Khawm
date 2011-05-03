//Khartikova

struct geom
{
	geom(unsigned v_x, unsigned v_y, unsigned v_w, unsigned v_h)
	{
		x1 = v_x;
		y1 = v_y;
		x2 = v_w;
		y2 = v_h;
	}
	unsigned int x1;
	unsigned int y1;
	unsigned int x2;
	unsigned int y2;
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
	bool is_shown;
	virtual void update_focus() = 0;	
	virtual void suicide() = 0;
	virtual bool find(Window* win) = 0;
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
	filler* me(); // доступ к объекту фокуса
	operator int(); //возвращает номер фокуса
	
	void operator++(int); //меняет местами фокус и правую дугу
	void operator--(int); //меняет местами фокус и левую дугу

	void swap(unsigned int first, unsigned int second);//меняет местами две дуги
	void tile(Display* display, int layout, geom coord); 
	//void checktree(Window* row, int n);
	void suicide();
	bool find(Window* win);

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

	virtual void tile(Display* display, int layout, geom coord); 
	void suicide();
	void update_focus();	
	bool find(Window* win);

private:
	window() {};
	virtual wheel* windows() {return 0;}; 
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
	void suicide();
	void update_focus();	
	bool find(Window* win);
};

class workspace : public filler
{
	char* name;
  wheel* wheel_of_windows;	
public:
	workspace ();
	~workspace ();
	
	void make_me_your_master(wheel* please);
	virtual wheel* windows();

private:
	void show() {};
	void hide() {};
	void suicide() {};
	void update_focus() {};
	bool find(Window* win) {return 0;};
	void tile(Display* display, int layout, geom coord) {};
};
